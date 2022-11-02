void bus_spd1() {
 // if (canId == 0x0CF00500) {
    x = (int)buf[2],DEC / 2;      //Bus Speed
    y = (int)buf[6],DEC - 40;
    z = (int)buf[5],DEC;  //Battery SOC

    speedo = map(x, 0, 100, 20, 254);
    range = z * 1.6;
    //1st System Status
    bt1 = bitRead(buf[0], 0);      //Gear Indicator
    bt2 = bitRead(buf[0], 1);
    bt3 = bitRead(buf[0], 2);
    hnd_brk = bitRead(buf[0], 3);  //Hand Brake
    ft_brk = bitRead(buf[0], 4);   //Foot Brake
    blt = bitRead(buf[0], 6);      //Sheat Belt
    FckDoor = (bitRead(buf[0], 5));

    //GEAR

    if (bt1 == 0 & bt2 == 0 & bt3 == 0) {
      gr_mode = 14; //Parking
    }
    else if (bt1 == 0 & bt2 == 0 & bt3 == 1) {
      gr_mode = 16; //Neu
    }
    else if (bt1 == 0 & bt2 == 1 & bt3 == 0) {
      gr_mode = 17; //Drv
    }
    else if (bt1 == 0 & bt2 == 1 & bt3 == 1) {
      gr_mode = 15; //Rev
    }
    else if (bt1 == 1 & bt2 == 0 & bt3 == 0) {
      gr_mode = 16; //Neu
    }
    else if (bt1 == 1 & bt2 == 0 & bt3 == 1) {
      gr_mode = 15; //Rev
    }
    else if (bt1 == 1 & bt2 == 1 & bt3 == 0) {
      gr_mode = 15; //Rev
    }
    else if (bt1 == 1 & bt2 == 1 & bt3 == 1) {
      gr_mode = 17; //Drv

    }

    //2nd System Status
    Lsen = bitRead(buf[1], 7);
    Rsen = bitRead(buf[1], 6);
    
   /* bus_spd = String(x);
    btty = String(z) + '%';
    temper = String(y);
    rover = String(range); */

    btty = String(z) + '%';
  }

//}

void rpm_spd(){
 // if (canId == 0x0CF00400) {     //Still broadcast this DATA
   pm1 = buf[3];
   pm2 = buf[4];

    word engi_rpm = (word(pm1, pm2));
 /* volatile int pmc = (uint8_t pm1, uint8_t pm2){
    volatile uint16_t Vpmc = (uint16_t)((pm1*256) + pm2); */
    rpm = map(engi_rpm, 0, 64255, 0, 8191);
    //rpm2 = rpm2 / 8;
  //}
}

void bat_temper(){
//  if (canId == 0x18F104F3) {
    word batcar = word(buf[0], buf[1]);
    
    bat_num = (int)batcar - 40;
    //bat_num = bat2;

    if (bat_num >= 0, bat_num <= 33) {
      bar = 24;
    }
    else if (bat_num > 33, bat_num <= 66) {
      bar = 42;
    }
    else if (bat_num > 66, bat_num <= 99) {
      bar = 60;
    }
    else if (bat_num > 99, bat_num <= 132) {
      bar = 75;
    }

    else if (bat_num > 108) {
      bar = 100;
    }

  }
//}

void Light_Belts() {
 // if (canId == 0x0D000020) {                           //CAN Master
    Hbem = bitRead(buf[0], 7);
    Lbem = bitRead(buf[0], 5);
    belt = bitRead(buf[1], 0);         //Safety Belt
 // }
}

void Pbar() {
//  if (canId == 0x0D000023) {                      //CAN Master
    bar0 = buf[2];
    bar1 = buf[3];

   int Pbar2 = word(bar0, bar1);
   Pb2 = map(Pbar2, 0, 32767, 0, 14);

   //Serial.println(Pbar2);
   //Serial.println(String(Pb2));

   Serial.print("p1.txt=\"");          //1st Pressure Bar
  Serial.print(String(Pb2));
  Serial.print("\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
   
  /* volatile int pb2 = (uint8_t bar0, uint8_t bar1){
    volatile uint16_t Vpb2 = (uint16_t)((bar0*256) + bar1);*/
   }
//  }
//}

void bat_accu() {

 // if (canId == 0x0D000022) {                      //CAN Master
    accu1 = buf[0];
    accu2 = buf[1];

   akcu = word(accu1, accu2);
   // ak = ((akcu * 6.45) / 32767) * 4.652 + 1.4; //Ngitung Ulang Aki

  /* volatile int akcu = (uint8_t accu1, uint8_accu2){
    volatile uint16_t Vakcu = (uint16_t)((accu1*256) + accu2);    */
   
  ak = (((akcu * 6.45) / 32767) * 4.652 + 1.4)* 10; //Ngitung Ulang Aki
    //akcu = 24;
 // }

}
