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
int hood;

int belt;         //Safety Belt
int Fdoor;        //Front Door
int Ldoor;        //Left Door
int Rdoor;        //Right Door

int bar1;
int bar2;
        
int Pb1;
int Pb2;

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

    slave();
    master();
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

        odo = 0;
        while (odo < 9999999){
          odo = odo + sp;
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
         hood = buf[1];

        Hbem = bitRead(bem, 7);
        Lbem = bitRead(bem, 5);
        belt = bitRead(hood, 0);         //Safety Belt
        Fdoor = bitRead(hood, 4);        //Front Door
        Ldoor = bitRead(hood, 5);        //Left Door
        Rdoor = bitRead(hood, 6);        //Right Door
 
     }      

    if (canId == 0x0D000013){                       //CAN Master
        Pbar1 = word(buf[2], buf[3]);
        Pbar2 = word(buf[4], buf[5]);

        bar1 = ((Pbar1*6.45)/32767)*2.171;
        bar2 = ((Pbar2*6.45)/32767)*2.171;
        
        Pb1 = map(bar1, 0, 14.00295, 0, 14);
        Pb2 = map(bar2, 0, 14.00295, 0, 14);
        
        }

      if (canId == 0x0D000012){                       //CAN Master
        accu1 = buf[0];
        accu2 = buf[1];

        int aki = word(buf[0], buf[1]);
        int ak = ((aki*6.45)/32767)*4.652;
        akcu = map(ak, 0, 30.0054,0, 30);
        //akcu = 30;
        akbat = String(akcu); 
    }  

    serial();

      Serial.println();
    } 
