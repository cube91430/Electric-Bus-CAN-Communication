#include <TimerOne.h>
#include <SPI.h>
#define CAN_2515

const int SPI_CS_PIN = 10;
const int CAN_INT_PIN = 2;
#ifdef CAN_2515
#include "mcp2515_can.h"
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
#endif

//Int Variable
volatile int sp;  //Speed
volatile int mtr; //RPM
volatile int soc; //Battery SoC

int Hb;  //High Beam
int Lb;  //Low Beam

volatile bool FDoor; //Front Door
volatile bool LRear; //Left Rear Door
volatile bool RRear; //Right Rear Door

volatile bool RvLamp; //Reverse Lamp
volatile bool BrLamp; //Brake Lamp

volatile bool gear; //Gear

int Pbar1; //Pressure Bar 1
int Pbar2; //Pressure Bar 2

int speedo;
int range;
int accu1;
int accu2;

int i = 2;
int rpm;
int rpm2;
int bar2;

int x;
int y;
int z;
int gr_mode;

//int odo;
int akcu;
//int sim;
int ak;
int Pb2;

unsigned char pm1;
unsigned char pm2;
int bat2;

bool belt;

bool gr;
bool sign;
bool bem;
bool Hbem;
bool Lbem;

String f;
String btty;
String bus_spd;
String temper;
String rover;
String akbat;
String pb;
String bat_temp;
String rpm_avg;

bool Lsen;
bool Rsen;
bool bt1;      //Gear Indicator
bool bt2;
bool bt3;
bool hnd_brk;  //Hand Brake
bool ft_brk;   //Foot Brake
bool blt;      //Sheat Belt
bool mode;
bool FckDoor;

bool Fdoor;
bool Ldoor;

int bar;
int aki;
double sim;
int odo = 0;
int bar0;
int bar1;

int park = 14;

int bat_num;

unsigned char len = 0;
unsigned char buf[8];

unsigned long  canId;

double tampungodo;

void setup() {
  Serial.begin(115200);

  while (CAN_OK != CAN.begin(CAN_250KBPS)) {             // init can bus : baudrate = 500k
    Serial.println("CAN init fail, retry...");
    delay(100);
  }
  pinMode(CAN_INT_PIN, INPUT);
  Serial.println("CAN init ok!");

  mask_filt();
}

void loop() {
  while (odo < 9999999) {
    if (CAN_MSGAVAIL == CAN.checkReceive()) {         // check if data coming
      CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

      canId = CAN.getCanId();

      switch (canId) {
          case 0x0CF00500:   //Engine Speed, Motor Temp, ETC
            bus_spd1();
          break;

           case 0x0CF00400:   //Engine RPM
            rpm_spd();
          break;

           case 0x18F104F3:   //Battery Temperature
            bat_temper();
          break;

          case 0x0D000020:   //Engine RPM
            Light_Belts();
          break;

          case 0x0D000022:   //Engine RPM
            bat_accu();
          break;

          case 0x0D000023:   //Engine RPM
            Pbar();
          break;
      }
       
       Serialcom();

 
      
     sim = (x*0.000278) + tampungodo;
     //sim = (4.3/x);
     
      
      Serial.print("od.txt=\"");
      Serial.print(sim);
      Serial.print("\"");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);

      tampungodo = sim;

    }
  }
}
