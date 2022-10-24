#include <SPI.h>
#define CAN_2515

const int SPI_CS_PIN = 10;
const int CAN_INT_PIN = 2;
#ifdef CAN_2515
#include "mcp2515_can.h"
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
#endif         

//Int Variable
int sp;  //Speed
int mtr; //RPM
int soc; //Battery SoC

int Hb;  //High Beam
int Lb;  //Low Beam

int FDoor; //Front Door
int LRear; //Left Rear Door
int RRear; //Right Rear Door

int RvLamp; //Reverse Lamp
int BrLamp; //Brake Lamp

int gear; //Gear

int Pbar1; //Pressure Bar 1
int Pbar2; //Pressure Bar 2

int speedo;
int range;
int accu1;
int accu2;

int i = 2;
int rpm;

int x;
int y;
int z;
int gr_mode;

int odo;
int akcu;

byte gr;
byte sign;
byte bem;
byte Hbem;
byte Lbem;

const uint32_t myMask   = 0x0CFFFFFF;

String f;
String btty;
String bus_spd;
String temper;
String rover;
String akbat;

byte Lsen;
byte Rsen;   
byte bt1;      //Gear Indicator
byte bt2;
byte bt3;
byte hnd_brk;  //Hand Brake
byte ft_brk;   //Foot Brake
byte blt;      //Sheat Belt
byte mode;

unsigned char len = 0;
unsigned char buf[8];   

unsigned long  canId;

void setup() {
    Serial.begin(115200);
    
    while (CAN_OK != CAN.begin(CAN_250KBPS)) {             // init can bus : baudrate = 500k
        Serial.println("CAN init fail, retry...");
        delay(100);
    }
   pinMode(CAN_INT_PIN, INPUT);
   Serial.println("CAN init ok!");

    //Masking and Filtering

    CAN.init_Mask(0, 1, myMask);
    CAN.init_Filt(0, 1, 0x0CF00500);

    CAN.init_Mask(1, 1, myMask);
    CAN.init_Filt(1, 1, 0x0CF00400);

    CAN.init_Mask(1, 1, 0X0DFFFFFF);
    CAN.init_Filt(2, 1, 0x0D000010);

    CAN.init_Mask(1, 1, 0X0DFFFFFF);
    CAN.init_Filt(3, 1, 0x0D000011);

    CAN.init_Mask(1, 1, 0X0DFFFFFF);
    CAN.init_Filt(5, 1, 0x0D000012);

    CAN.init_Mask(1, 1, 0X0DFFFFFF);
    CAN.init_Filt(5, 1, 0x0D000013);
} 

void loop() { 
    if (CAN_MSGAVAIL == CAN.checkReceive()) {         // check if data coming
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

        canId = CAN.getCanId();

      if (canId == 0x0CF00500){
       //Change to Decimals by int

          sp = buf[2], DEC;
          mtr = buf[3], DEC;
          soc = buf[5], DEC;
          
          x = (int)sp;        //Bus Speed 
          y = (int)mtr;    // Motor Temp
          z = map((int)soc, 0, 20261, 0, 100);  //Battery SOC
          speedo = map(x, 0, 100, 20, 254);
          range = z*1.6;
          
          //1st System Status
          gr = buf[0];
          bt1 = bitRead(gr, 0);      //Gear Indicator
          bt2 = bitRead(gr, 1);
          bt3 = bitRead(gr, 2);
          hnd_brk = bitRead(gr, 3);  //Hand Brake
          ft_brk = bitRead(gr, 3);   //Foot Brake
          blt = bitRead(gr, 6);      //Sheat Belt
    
          mode = bt1 + bt2 + bt3;

      //GEAR
            if (mode == 0){
              gr_mode = 0;  //Standby
              Serial.print("tStat.txt=\"");
              Serial.print("IDLE");
              Serial.print("\"");
              Serial.write(0xff);
              Serial.write(0xff);
              Serial.write(0xff);
            }
            
            if (mode == 1){
              gr_mode = 16;  //Neutral
              Serial.print("tStat.txt=\"");
              Serial.print("START");
              Serial.print("\"");
              Serial.write(0xff);
              Serial.write(0xff);
              Serial.write(0xff);
            }
            
            if (mode == 2){
              gr_mode = 17;  //Drive
            }
      
             if (mode == 3){
              gr_mode = 15;  //Reverse
            }

        odo = 0;
        while (odo < 9999999){
          odo = odo + sp;
           Serial.print("tOdo.txt=\"");
              Serial.print(odo);
              Serial.print("\"");
              Serial.write(0xff);
              Serial.write(0xff);
              Serial.write(0xff);
        }

      //HAND - BRAKE
      if (hnd_brk == 0){
        Serial.print("Brake OFF");
        Serial.print(" , ");
        Serial.print("vis temp,0") +f;
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
      }

      else if (hnd_brk == 1){
        Serial.print("Brake ON");
        gr_mode = 14;
        Serial.print("vis temp,1") + f;
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
             
            }
      
      }

      //2nd System Status
      sign = buf[1];
      Lsen = bitRead(sign, 7);
      Rsen = bitRead(sign, 6);
    
      //Convert to Strings for some of the variables      
      bus_spd = String(x);
      btty = String(z) + '%';
      temper = String(y);
      rover = String(range);
      
         }
      
      if (canId == 0x0CF00400){      //Still broadcast this DATA
         int engi_rpm = word(buf[3], buf[4]);
         rpm = map(engi_rpm, 0, 64255, 0, 8191);
      
      }
      
     if (canId == 0x0D000010){                            //CAN Master
         bem = buf[0];  //High Beam
     int hood = buf[1];

        Hbem = bitRead(bem, 7);
        Lbem = bitRead(bem, 5);
    int belt = bitRead(hood, 0);         //Safety Belt
    int Fdoor = bitRead(hood, 4);        //Front Door
    int Ldoor = bitRead(hood, 5);        //Left Door
    int Rdoor = bitRead(hood, 6);        //Right Door
    
      //Nextion Display
       if (belt == 1){      //HIGH Beam
             Serial.print("vis sb,1") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
             
            }
      else if(belt == 0){
             Serial.print("vis sb,0") +f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
            }

      if (Fdoor == 1){      //HIGH Beam
             Serial.print("vis door,1") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
             
            }
      else if(Fdoor == 0){
             Serial.print("vis door,0") +f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
            }

      
      if (Ldoor == 1){      //HIGH Beam
             Serial.print("vis door,1") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
             
            }
      else if(Ldoor == 0){
             Serial.print("vis door,0") +f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
            }

       if (Rdoor == 1){      //HIGH Beam
             Serial.print("vis door,1") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
             
            }
      else if(Rdoor == 0){
             Serial.print("vis door,0") +f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
            }
      
      if (Hbem == 1){      //HIGH Beam
             Serial.print("vis Hbeam,1") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
             
            }
      else if(Hbem == 0){
             
             Serial.print("vis Hbeam,0") +f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
            }

      if (Lbem == 1){      //LOW Beam
             Serial.print("vis Lbeam,1") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
             
            }
      else if(Lbem == 0){
             Serial.print("vis Lbeam,0") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
            }
      if(belt == 0){
             Serial.print("vis sb,0") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
            }
      else if(belt == 1){
             Serial.print("vis sb,1") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
            }
      if(Fdoor == 0){
             Serial.print("vis door,0") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
            }
      else if(Fdoor == 1){
             Serial.print("vis door,1") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
            }
      if (Ldoor == 0){
             Serial.print("vis door,0") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
            }
      else if(Ldoor == 1){
             Serial.print("vis door,1") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
            }
      if (Rdoor == 0){
             Serial.print("vis door,0") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
            }
      else if(Rdoor == 1){
             
             Serial.print("vis door,1") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
            }
     
     }      

    if (canId == 0x0D000013){                       //CAN Master
        Pbar1 = word(buf[2], buf[3]);
        Pbar2 = word(buf[4], buf[5]);

        int bar1 = ((Pbar1*6.45)/32767)*2.171;
        int bar2 = ((Pbar2*6.45)/32767)*2.171;
        
        int Pb1 = map(bar1, 0, 14.00295, 0, 14);
        int Pb2 = map(bar2, 0, 14.00295, 0, 14);
        
        Serial.print("tPB1.txt=\"");
        Serial.print(String(Pb1));
        Serial.print("\"");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        
        Serial.print("tPB2.txt=\"");
        Serial.print(String(Pb2));
        Serial.print("\"");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        
        }

      if (canId == 0x0D000012){                       //CAN Master
        accu1 = buf[0];
        accu2 = buf[1];

        int aki = word(buf[0], buf[1]);
        int ak = ((aki*6.45)/32767)*4.652;
        akcu = map(ak, 0, 30.0054,0, 30);
        //akcu = 30;
        String akbat = String(akcu); 

        Serial.print("tVolt.txt=\"");
        Serial.print(akbat);
        Serial.print("\"");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff); 
    }  

      //NEXTION-Display
      
      Serial.print("pTemp.val=");        //TempLevel
      Serial.print(y);
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);

      Serial.print("tTemp.txt=\"");     //Temp Level (String)
      Serial.print(temper);
      Serial.print("\"");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      
      Serial.print("pBatt.val=");  //Battery Level
      Serial.print(z);
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);

      Serial.print("tBatt.txt=");  //Battery Level (String)
      Serial.print("\"");
      Serial.print(btty);
      Serial.print("\"");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      
      Serial.print("tSpeed.txt=\"");  //Speed
      Serial.print(bus_spd);
      Serial.print("\"");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);

      Serial.print("pSpeedo.pic=");  //Gear Indicator
      Serial.print(speedo);
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);

      Serial.print("tRange.txt=\"");  //Gear Indicator
      Serial.print("Range ");
      Serial.print(rover);
      Serial.print(" km");
      Serial.print("\"");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);

      Serial.print("pGear.pic=");  //Gear Indicator
      Serial.print(gr_mode);
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);

     if (Lsen == 1){     //LEFT Sign
             
             Serial.print("vis left,1") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
      }
     if (Lsen == 0) {
             Serial.print("vis left,0") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
      }

     if (Rsen == 1){     //RIGHT Sign
             Serial.print("vis right,1") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
      }
      if (Rsen == 0) {
             Serial.print("vis right,0") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
      }
    
          Serial.print("tRpm.txt=\"");
          Serial.print(String(rpm));
          Serial.print("\"");
          Serial.write(0xff);
          Serial.write(0xff);
          Serial.write(0xff); 

        

         if (akcu < 20){
             Serial.print("vis lowbatt,1") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
           
             Serial.print("vis normalbatt,0") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);

             Serial.print("vis warn,1") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
           }
        if (akcu > 20){
             Serial.print("vis lowbatt,0") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);

             Serial.print("vis normalbatt,1") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
             
             Serial.print("vis warn,0") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
      }

      Serial.println();
    } 
