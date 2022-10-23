// demo: CAN-BUS Shield, receive data with check mode
// send data coming to fast, such as less than 10ms, you can use this way
// loovee, 2014-6-13
#include <SPI.h>
#include <SoftwareSerial.h>

SoftwareSerial esp(2, 3);//rx, tx

#define CAN_2515
// #define CAN_2518FD

// Set SPI CS Pin according to your hardware

#if defined(SEEED_WIO_TERMINAL) && defined(CAN_2518FD)
// For Wio Terminal w/ MCP2518FD RPi Hat：
// Channel 0 SPI_CS Pin: BCM 8
// Channel 1 SPI_CS Pin: BCM 7
// Interupt Pin: BCM25
const int SPI_CS_PIN  = BCM8;
const int CAN_INT_PIN = BCM25;
#else

// For Arduino MCP2515 Hat:
// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 10;
const int CAN_INT_PIN = 2;
#endif


#ifdef CAN_2518FD
#include "mcp2518fd_can.h"
mcp2518fd CAN(SPI_CS_PIN); // Set CS pin
#endif

#ifdef CAN_2515
#include "mcp2515_can.h"
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
#endif         

//CAN ID 0x0CF00500                       0x0CF00400
//                     byte parameters
//    0   system status 1               unidentified
//    1   system status 2               Driver's Torque Demand
//    2   Bus Speed                     Engine Percentage Torque (Actual)
//    3   Motor Temperature             Engine Speed
//    4   Inverter Temperature          Engine Speed
//    5   SoC Battery                   Source Adress
//    6   Battery Temperature           Unidentified
//    7   Unidentified                  Unidentified

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

int x;
int y;
int z;
int gr_mode;

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

byte Lsen;
byte Rsen;   
byte bt1;      //Gear Indicator
byte bt2;
byte bt3;
byte hnd_brk;  //Hand Brake
byte ft_brk;   //Foot Brake
byte blt;      //Sheat Belt
byte mode;


void setup() {
    //Nextion.begin(9600);

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
    CAN.init_Filt(4, 1, 0x0D000020);

    CAN.init_Mask(1, 1, 0X0DFFFFFF);
    CAN.init_Filt(5, 1, 0x0D000021);

}


void loop() {
  
    unsigned char len = 0;
    unsigned char buf[8];

    if (CAN_MSGAVAIL == CAN.checkReceive()) {         // check if data coming
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

        unsigned long canId = CAN.getCanId();

      if (canId == 0x0CF00500){
       //Change to Decimals by int

      sp = buf[2], DEC;
      mtr = buf[3], DEC;
      soc = buf[5], DEC;
      
      x = (int)sp;        //Bus Speed 
      //x = (int)sp/2
      //x = (int)sp - 10;
      //x = 80;
      
      y = (int)mtr;    // Motor Temp
      //y = (int)50
      z = map((int)soc, 0, 20261, 0, 100);         //Battery SOC
      //z = (int)soc;
      //z = 50;
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
      }
      
      if (mode == 1){
        gr_mode = 16;  //Neutral
      }
      
      if (mode == 2){
        gr_mode = 17;  //Drive
      }

       if (mode == 3){
        gr_mode = 15;  //Reverse
      }


      //HAND - BRAKE
      if (hnd_brk == 0){
        Serial.print("Brake OFF");
        Serial.print(" , ");
      }

      if (hnd_brk == 1){
        Serial.print("Brake ON");
        gr_mode = 14;
        Serial.print(" , ");
      }

      //FOOT - BRAKE
      if (ft_brk == 0){
        Serial.print("Brake OFF");
        Serial.print(" , ");
      }

      if (ft_brk == 1){
        Serial.print("Brake ON");
        Serial.print(" , ");
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
    
     Serial.println();
         }
      

      if (canId == 0x0CF00400){      //Still broadcast this DATA
         //int socbat = buf[7], DEC; //Battery Remaining
         int engi_rpm = word(buf[4], buf[3]);
          
         //rem = (int)socbat;
         //Serial.print(" Battery: ");
         //Serial.print(rem);
         //Serial.print(" , ");
         //Serial.print(engi_rpm);
         //Serial.print(" , ");

          Serial.print("tOdo.txt=");
          Serial.print(String(engi_rpm));
          Serial.write(0xff);
          Serial.write(0xff);
          Serial.write(0xff); 
            
         // Serial.println();
      }
     if (canId == 0x0D000010){                            //CAN Master
         bem = buf[0];  //High Beam
         

        Hbem = bitRead(bem, 7);
        Lbem = bitRead(bem, 5);
        //int Lbem = bitRead(bem, 6);

      //Nextion Display

     /* if (bem == A0){
        Serial.print("Hbem ON! Lbem ON!")
      }

      if (bem == B){
        Serial.println("Hbem OFF! Lbem OFF!");
      } */
         
      if (Hbem == 1){      //HIGH Beam
           /*  Serial.print("Hbem ON: ");
             Serial.print(Hbem);
             Serial.print(" , "); */
             
             Serial.print("vis Hbeam,1") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
             
            }
      if(Hbem == 0){
           /*    Serial.print("Hbem OFF: ");
             Serial.print(Hbem);
             Serial.print(" , ");
             delay(500);  */
             
             Serial.print("vis Hbeam,0");
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
            }

      if (Lbem == 1){      //LOW Beam
          /*   Serial.print("Lbem ON: ");
             Serial.println(Lbem);
             Serial.print(" , "); */
             
             Serial.print("vis Lbeam,1") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
             
            }
      if(Lbem == 0){
           /*Serial.print("Lbem OFF: ");
             Serial.print(Lbem);
             Serial.println(" , "); */
             
             Serial.print("vis Lbeam,0");
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
            }
     
     }      

     if (canId == 0x0D000020){                            //CAN Slave
         bem = buf[0];  //High Beam
         

        Hbem = bitRead(bem, 7);
        Lbem = bitRead(bem, 5);
        //int Lbem = bitRead(bem, 6);
         
      if (Hbem == 1){      //HIGH Beam
           /* Serial.print("Hbem ON: ");
             Serial.print(Hbem);
             Serial.print(" , "); */
             
             Serial.print("vis Hbeam,1") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
             
            }
      if(Hbem == 0){
           /*Serial.print("Hbem OFF: ");
             Serial.print(Hbem);
             Serial.print(" , "); */
             
             Serial.print("vis Hbeam,0") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
            }

      if (Lbem == 1){      //LOW Beam
          /* Serial.print("Lbem ON: ");
             Serial.println(Lbem);
             Serial.print(" , "); */
             
             Serial.print("vis Lbeam,1") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
             
            }
      if(Lbem == 0){
           /*  Serial.print("Lbem OFF: ");
             Serial.print(Lbem);
             Serial.println(" , "); */
             
             Serial.print("vis Lbeam,0") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
            }
     
     } 

    if (canId == 0x0D000023){                       //CAN Slave
        Pbar1 = word(buf[3], buf[2]);       //Air Pressure Bar 1
        Pbar2 = word(buf[5], buf[4]);       //Air Pressure Bar 2

    /*    Serial.print("Pressure Bar 1: ");
        Serial.print(Pbar1);
        Serial.print(" , ");
          
        Serial.print("Pressure Bar 2: ");
        Serial.print(Pbar2);
        Serial.print(" , ");  */
        
         }
    
    if (canId == 0x0D000013){                       //CAN Master
        Pbar1 = word(buf[3], buf[2]);
        Pbar2 = word(buf[5], buf[4]);

      /*Serial.print("Pressure Bar 1: ");
        Serial.print(Pbar1);
        Serial.print(" , ");  
          
        Serial.print("Pressure Bar 2: ");
        Serial.print(Pbar2);
        Serial.print(" , ");;  */
        
         }

      if (canId == 0x0D000022){                       //CAN Master
        accu1 = highByte(buf[0]);
        accu2 = lowByte(buf[1]);

        int aki = word(buf[0], buf[1]);
        int aki_ki = map(aki, 0, 32767, 0, 30);

      /*Serial.print("Pressure Bar 1: ");
        Serial.print(Pbar1);
        Serial.print(" , ");  
          
        Serial.print("Pressure Bar 2: ");
        Serial.print(Pbar2);
        Serial.print(" , ");;  */
        
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
      
      //Serial.print(" , ");
     
      Serial.print("pBatt.val=");  //Battery Level
      Serial.print(z - 30);
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      
      //Serial.print("Battery: ");
      //Serial.print(" , ");

      Serial.print("tBatt.txt=");  //Battery Level (String)
      Serial.print("\"");
      Serial.print(btty);
      Serial.print("\"");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      
      //Serial.print(" , ");
      //Serial.print("Speed: ");
      
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

      Serial.print("tHeader.txt=\"");
      Serial.print(String("23 Oktober 2022 Sabtu | 10:17 PM | Tayo"));
      Serial.print("\"");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff); 
  
      Serial.print("tOdo.txt=\"");
      Serial.print(String("12345678"));
      Serial.print("\"");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff); 

     if (Lsen == 1){     //LEFT Sign
          //Serial.print(" Left ON: ");
          //Serial.print(Lsen);
          //Serial.print(" , ");
             //delay(500);
             
             Serial.print("vis left,1") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
      }
     if (Lsen == 0) {
        //Serial.print("Left OFF: ");
        //Serial.print(Lsen);
        //Serial.print(" , ");
        //delay(500);
        
             Serial.print("vis left,0") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
      }

     if (Rsen == 1){     //RIGHT Sign
          //Serial.print("Right ON: ");
          //Serial.print(Rsen);
          // Serial.print(" , ");
          //delay(500);
          
             Serial.print("vis right,1") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
      }
      if (Rsen == 0) {
        //Serial.print("Right OFF: ");
        //Serial.print(Rsen);
        //Serial.print(" , ");
        //delay(500);
        
             Serial.print("vis right,0") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
      }
    
    
    }

}



/*********************************************************************************************************
    END FILE
*********************************************************************************************************/
