#include <EEPROM.h>
#include <SPI.h>
//#include <avr/wdt.h>

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

volatile int Hb;  //High Beam
volatile int Lb;  //Low Beam

bool FDoor; //Front Door
bool LRear; //Left Rear Door
bool RRear; //Right Rear Door

bool RvLamp; //Reverse Lamp
bool BrLamp; //Brake Lamp

bool gear; //Gear

volatile int Pbar1; //Pressure Bar 1
volatile int Pbar2; //Pressure Bar 2

volatile int speedo;
volatile int range;
volatile int accu1;
volatile int accu2;

int i = 2;
int rpm;
int rpm2;
int bar2;
int speed_val;

volatile int x;
volatile int y;
volatile int z;
volatile int gr_mode;
volatile int cool;

int motor_temp;
int cool_temp;

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

int gu;
int counter;

int bar;
int aki;
double sim;
//int sim;

unsigned int odo;

int bar0;
int bar1;
int batcar;

int park = 14;

int bat_num;

int er_bat;
int er_hard;
int er_oth;

//Battery Fault code
int erby1;
int erby2;
int erby3;
int erby4;

//Hardware Fault code;
int erby5;
int erby6;

//Other Fault Code
int erby7;

byte counH;
byte counL;

byte odoH;
byte odoL;

unsigned char len = 0;
unsigned char buf[8];

unsigned long  canId;

double tampungodo;
//int tampungodo;

int s;

unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 1000;

void setup() {
  Serial.begin(250000);

  while (CAN_OK != CAN.begin(CAN_250KBPS)) {             // init can bus : baudrate = 500k
    Serial.println("CAN init fail, retry...");
    delay(100);
  }
  pinMode(CAN_INT_PIN, INPUT);
  Serial.println("CAN init ok!");

  //mask_filt();

  odoH = EEPROM.read(0);
  odoL = EEPROM.read(1);

  tampungodo = word(odoH, odoL);

  startMillis = millis();

  //wdt_enable(WDTO_2S);
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

        case 0x0D000020:   //High and Low Beam, Safety Belt
          Light_Belts();
          break;

        case 0x0D000022:   //Car Battery
          bat_accu();
          break;

        case 0x0D000023:   //Pressure Bar
          Pbar();
          break;

        case 0x18F108F3:   //Error Code
          error();
          break;
      }

      Serialcom();

      /* currentMillis = millis();
        if (currentMillis - startMillis >= period){
         // sim = (x*0.000278) + tampungodo;
         //sim = (4.3/x);
         // sim = (x*3600) + tampungodo;
         //sim = ((x*0.00013889)*0.0083) + tampungodo;
         sim = ((x*0.00027778)*0.02333) + tampungodo;
         //sim = ((x*0.00027778)*0.023334) + tampungodo;
         odo = abs(sim);

         //Calculate Milage
         s = (sim - tampungodo)/z;

        Serial.print("od.txt=\"");
            Serial.print(String(odo));
            Serial.print("\"");
            Serial.write(0xff);
            Serial.write(0xff);
            Serial.write(0xff);

            tampungodo = sim;
        } */
      /*  Serial.print(speed_val);
        Serial.print(" , ");
        //Serial.print(z);
        //Serial.print(" , ");
        Serial.print(abs(sim));
        Serial.print(" , ");
        Serial.print(abs(tampungodo));
        //Serial.print(" , ");
        //Serial.print(abs(s));
        Serial.println();   */



      //delay(4);
      //wdt_reset();
    }
  }

}
