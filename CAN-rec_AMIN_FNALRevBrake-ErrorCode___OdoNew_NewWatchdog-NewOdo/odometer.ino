void bus_spd1() {
  // if (canId == 0x0CF00500) {
  x = (int)buf[2], DEC;     //Bus Speed
  y = (int)buf[3], DEC;
  cool = (int)buf[4], DEC;
  z = (int)buf[5], DEC; //Battery SOC

  speed_val = x /2;
  motor_temp = y - 40;
  cool_temp = cool - 40; 
  
  //2nd System Status
  Lsen = bitRead(buf[1], 7);
  Rsen = bitRead(buf[1], 6);
  speedo = map(speed_val, 0, 100, 20, 254);
  range = z * 1.6;
  //1st System Status
  bt1 = bitRead(buf[0], 0);      //Gear Indicator
  bt2 = bitRead(buf[0], 1);
  bt3 = bitRead(buf[0], 2);
  hnd_brk = bitRead(buf[0], 3);  //Hand Brake
  ft_brk = bitRead(buf[0], 4);   //Foot Brake
  blt = bitRead(buf[0], 6);      //Sheat Belt
  FckDoor = (bitRead(buf[0], 5));

  //Coolant TEMP BAR
  
  if (cool_temp >= 0, cool_temp <= 33) {
    bar = 24;
  }
  else if (cool_temp > 33, cool_temp <= 66) {
    bar = 42;
  }
  else if (cool_temp > 66, cool_temp <= 99) {
    bar = 60;
  }
  else if (cool_temp > 99, cool_temp <= 132) {
    bar = 75;
  }

  else if (cool_temp > 108) {
    bar = 100;
  }

  //GEAR

  if (bt1 == 0 & bt2 == 0 & bt3 == 0) {
    gr_mode = 14; //Parking
    Serial.print("st.txt=\"");      //Status "IDLE" at the RPM below 0
    Serial.print("IDLE");
    Serial.print("\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }
  else if (bt1 == 0 & bt2 == 0 & bt3 == 1) {
    gr_mode = 16; //Neu
    Serial.print("st.txt=\"");      //Status "IDLE" at the RPM below 0
    Serial.print(" ");
    Serial.print("\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }
  else if (bt1 == 0 & bt2 == 1 & bt3 == 0) {
    gr_mode = 17; //Drv
    Serial.print("st.txt=\"");      //Status "IDLE" at the RPM below 0
    Serial.print(" ");
    Serial.print("\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }
  else if (bt1 == 0 & bt2 == 1 & bt3 == 1) {
    gr_mode = 15; //Rev
    Serial.print("st.txt=\"");      //Status "IDLE" at the RPM below 0
    Serial.print(" ");
    Serial.print("\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }
  else if (bt1 == 1 & bt2 == 0 & bt3 == 0) {
    gr_mode = 16; //Neu
    Serial.print("st.txt=\"");      //Status "IDLE" at the RPM below 0
    Serial.print(" ");
    Serial.print("\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }
  else if (bt1 == 1 & bt2 == 0 & bt3 == 1) {
    gr_mode = 15; //Rev
    Serial.print("st.txt=\"");      //Status "IDLE" at the RPM below 0
    Serial.print(" ");
    Serial.print("\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }
  else if (bt1 == 1 & bt2 == 1 & bt3 == 0) {
    gr_mode = 15; //Rev
    Serial.print("st.txt=\"");      //Status "IDLE" at the RPM below 0
    Serial.print(" ");
    Serial.print("\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }
  else if (bt1 == 1 & bt2 == 1 & bt3 == 1) {
    gr_mode = 17; //Drv
    Serial.print("st.txt=\"");      //Status "IDLE" at the RPM below 0
    Serial.print(" ");
    Serial.print("\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }
        
  

  /* bus_spd = String(x);
    btty = String(z) + '%';
    temper = String(y);
    rover = String(range); */

  btty = String(z) + '%';
}

//}

void rpm_spd() {
  // if (canId == 0x0CF00400) {     //Still broadcast this DATA
  pm1 = buf[3];
  pm2 = buf[4];

  word engi_rpm = word(pm1, pm2);
  /* volatile int pmc = (uint8_t pm1, uint8_t pm2){
     volatile uint16_t Vpmc = (uint16_t)((pm1*256) + pm2); */
     
  //int cal = map(engi_rpm, 0, 64255, 0, 8191);
  rpm = map(engi_rpm, 0, 64255, 0, 8191);
  //rpm = cal*0.125;
  //rpm2 = rpm2 / 8;
  //}
}

void bat_temper() {
  //  if (canId == 0x18F104F3) {
 // int batcar = word(buf[0], buf[1]);
 batcar = (int)buf[0], DEC;

  bat_num = batcar - 40;
  //bat_num = bat2;

/*  if (bat_num >= 0, bat_num <= 33) {
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
  }   */

  /* Serial.println(batcar);
  Serial.println(bat_num);
  Serial.println(); */

}
//}

void Light_Belts() {
  // if (canId == 0x0D000020) {                           //CAN Master

  Hbem = bitRead(buf[0], 7);
  Lbem = bitRead(buf[0], 5);
  belt = bitRead(buf[1], 0);         //Safety Belt
  Fdoor = bitRead(buf[1], 4);        //Front Door
  Ldoor = bitRead(buf[1], 5);        //Left Door
  belt = bitRead(buf[1], 0);         //Safety Belt
  // }
}

void Pbar() {
  //  if (canId == 0x0D000023) {                      //CAN Master
  bar0 = buf[2];
  bar1 = buf[3];

  word Pbar2 = word(bar0, bar1);
  Pb2 = map(Pbar2, 0, 32767, 0, 14);

  /* Serial.println(Pbar2);
    Serial.println(String(Pb2));

    Serial.print("p1.txt=\"");          //1st Pressure Bar
    Serial.print(String(Pb2));
    Serial.print("\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);   */

  /* volatile int pb2 = (uint8_t bar0, uint8_t bar1){
    volatile uint16_t Vpb2 = (uint16_t)((bar0*256) + bar1);*/
}
//  }
//}

void bat_accu() {
  // if (canId == 0x0D000022) {                      //CAN Master
  akcu = word(buf[0], buf[1]);
  // ak = ((akcu * 6.45) / 32767) * 4.652 + 1.4; //Ngitung Ulang Aki

  /* volatile int akcu = (uint8_t accu1, uint8_accu2){
    volatile uint16_t Vakcu = (uint16_t)((accu1*256) + accu2);    */

  // ak = (((akcu * 6.45) / 32767) * 4.652 + 1.4) * 10; //Ngitung Ulang Aki
  ak = map(akcu, 0, 32767, 0, 30);
  //akcu = 24;
  // }

}

void error(){
  //Battery Fault code
  erby1 = buf[0];
  erby2 = buf[1];
  erby3 = buf[2];
  erby4 = buf[3];

  bool HighSOC1 = bitRead(buf[0], 0);
  bool HighSOC2 = bitRead(buf[0], 1);

  bool LowSOC1 = bitRead(buf[0], 2);
  bool LowSOC2 = bitRead(buf[0], 3);

  bool VoltHIGH1 = bitRead(buf[0], 4);
  bool VoltHIGH2 = bitRead(buf[0], 5);

  bool VoltLOW1 = bitRead(buf[0], 6);
  bool VoltLOW2 = bitRead(buf[0], 7);

  bool ChargeCuFal1 = bitRead(buf[1], 0);
  bool ChargeCuFal2 = bitRead(buf[1], 1);

  bool DisChargeCuFal1 = bitRead(buf[1], 2);
  bool DisChargeCuFal2 = bitRead(buf[1], 3);

  bool BatTempLOW1 = bitRead(buf[1], 4);
  bool BatTempLOW2 = bitRead(buf[1], 5);

  bool BatTempHIGH1 = bitRead(buf[1], 6);
  bool BatTempHIGH2 = bitRead(buf[1], 7);

  bool CellUn1 = bitRead(buf[1], 0);
  bool CellUn2 = bitRead(buf[1], 1);

  bool CellOv1 = bitRead(buf[1], 2);
  bool CellOv2 = bitRead(buf[1], 3);

  bool BatTempUn1 = bitRead(buf[1], 4);
  bool BatTempUn2 = bitRead(buf[1], 5);

  bool CellVoltUn1 = bitRead(buf[1], 6);
  bool CellVoltUn2 = bitRead(buf[1], 7);

  //Hardware Fault code;
  erby5 = buf[4];
  erby6 = buf[5];

  //Other Fault Code
  erby7 = buf[6];

}
