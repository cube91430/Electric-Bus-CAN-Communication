// demo: CAN-BUS Shield, receive data with check mode
// send data coming to fast, such as less than 10ms, you can use this way
// loovee, 2014-6-13
#include <SPI.h>
#include <SoftwareSerial.h>

SoftwareSerial Nextion(0,1); //rx, tx

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
int sp;
int mtr;
int soc;

int x;

const uint32_t myMask   = 0x0CFFFFFF;
const uint32_t myFilter = 0x0CF00500;


void setup() {
    //Nextion.begin(9600);

    Serial.begin(115200);
    
    while (CAN_OK != CAN.begin(CAN_250KBPS)) {             // init can bus : baudrate = 500k
        Serial.println("CAN init fail, retry...");
        delay(100);
    }

   
   pinMode(CAN_INT_PIN, INPUT);
   Serial.println("CAN init ok!");

    CAN.init_Mask(0, 1, myMask);
    CAN.init_Filt(0, 1, 0x0CF00500);

    CAN.init_Mask(1, 1, myMask);
    CAN.init_Filt(1, 1, 0x0CF00400);

}


void loop() {
    unsigned char len = 0;
    unsigned char buf[8];

    if (CAN_MSGAVAIL == CAN.checkReceive()) {         // check if data coming
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

        unsigned long canId = CAN.getCanId();

    Serial.println("Masuk2");

      if (canId == 0x0CF00500){
   //       Serial.print(canId, HEX);
   //       Serial.print(",");

     
      
   //   Serial.print(buf[3], DEC); //Motor Temp
   //   Serial.print(",");
   //   Serial.print(buf[5], DEC); //Battery SoC
   //   Serial.print(","); 
   //  Serial.print(buf[2], DEC); //Bus Speed
   //  Serial.print(",");

      //Change to Decimals by int

      sp = buf[2], DEC;
      mtr = buf[3], DEC;
      soc = buf[5], DEC;

      x = (int)sp; 
      int y = (int)mtr;
      int z = (int)soc;

      //Convert to Strings for some of the variables      
      String bus_spd = String(x);

          //NEXTION
          
     // Nextion.print("pTemp.val=");
     // Nextion.print(y);
     // Nextion.write(0xff);
     // Nextion.write(0xff);
     // Nextion.write(0xff);

    //  Nextion.print("pBatt.val=");
    //  Nextion.print(z);
    //  Nextion.write(0xff);
    //  Nextion.write(0xff);
    //  Nextion.write(0xff);

    //  Nextion.print("tSpeed.txt=");
    //  Nextion.print("\"");
    //  Nextion.print(bus_spd);
    //  Nextion.print("\"");
    //  Nextion.write(0xff);
    //  Nextion.write(0xff);
    //  Nextion.write(0xff);

      //Serial.print("pTemp.val=");
      //Serial.print(y);
      //Serial.write(0xff);
      //Serial.write(0xff);
      //Serial.write(0xff);

      //Serial.print("pBatt.val=");
      //Serial.print(z);
      //Serial.write(0xff);
      //Serial.write(0xff);
      //Serial.write(0xff);

      //Serial.print("tSpeed.txt=");
      //Serial.print("\"");
      //Serial.print(bus_spd);
      //Serial.print("\"");
      //Serial.write(0xff);
      //Serial.write(0xff);
      //Serial.write(0xff);

      //Print ALL the CAN ID, DLC, and DATA
          
      //SERIAL_PORT_MONITOR.print(engine); 
      //SERIAL_PORT_MONITOR.print(",");
      //SERIAL_PORT_MONITOR.print(battery);
      //SERIAL_PORT_MONITOR.print(",");
      //SERIAL_PORT_MONITOR.print(temp);
          
          
         // SERIAL_PORT_MONITOR.print(buf[2], DEC);  //Bus Speed
         // SERIAL_PORT_MONITOR.print(",");
         // SERIAL_PORT_MONITOR.print(buf[5], DEC);  //Battery SoC
         // SERIAL_PORT_MONITOR.print(",");
         // SERIAL_PORT_MONITOR.print(buf[3], DEC);  //Motor Temperature
         // SERIAL_PORT_MONITOR.print("\t");
         }
         Serial.println();
      

      // if (canId == 0x0CF00400){
         // Serial.print(canId, HEX);
         // Serial.print(",");
            
         // Serial.println();
     // }
      

        Serial.println("-----------------------------");
        Serial.print("Get data from ID: 0x");
        Serial.println(canId, HEX);

        for (int i = 0; i < len; i++) { // print the data
            Serial.print(buf[i], HEX);
            Serial.print("\t");
        }
        Serial.println();

        
    }

}



/*********************************************************************************************************
    END FILE
*********************************************************************************************************/
