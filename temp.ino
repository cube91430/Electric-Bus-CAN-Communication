void Serialcom() {
/*  Serial.print("pt.val=");        //TempLevel Battery
  Serial.print(bat_num);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  Serial.print("tt.txt=\"");     //Temp Level (String) Battery
  Serial.print(String(bat_num));
  Serial.print("\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  Serial.print("et.val=");        //TempLevel Motor
  Serial.print(y);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  Serial.print("pb.val=");  //Battery Level (String)
  Serial.print(z);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  Serial.print("tb.txt=");  //Battery Level (String)
  Serial.print("\"");
  Serial.print(btty);
  Serial.print("\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  Serial.print("sp.txt=\"");  //Speed
  Serial.print(String(x));
  Serial.print("\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  Serial.print("ps.pic=");  //Speedometer
  Serial.print(speedo);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  Serial.print("tr.txt=\"");  //Battery Range
  Serial.print("Range ");
  Serial.print(String(range));
  Serial.print(" km");
  Serial.print("\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  //HAND - BRAKE
  if (hnd_brk == 0) {
    Serial.print("vis br,0") + f;   //Hand brake
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

    Serial.print("pg.pic=");  //Gear Indicator
    Serial.print(gr_mode);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }

  else if (hnd_brk == 1) {    
    Serial.print("vis br,1") + f;     //Hand Brake
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

    Serial.print("pg.pic=");  //Gear Indicator
    Serial.print(park);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

  }

  if (ft_brk == 0) {

    Serial.print("vis br,0") + f;     //Foot Brake
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }

  else if (ft_brk == 1) {
    Serial.print("vis br,1") + f;   //Foot Brake
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }

  Serial.print("ts.txt=\"");        //RPM
  Serial.print(String(rpm));
  Serial.print("\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  if (rpm2 == 0) {
    Serial.print("st.txt=\"");      //Status "IDLE" at the RPM below 0
    Serial.print("IDLE");
    Serial.print("\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }

  else if (rpm2 > 0) {
    Serial.print("st.txt=\"");      //Status "START" at the RPM above 0
    Serial.print("START");
    Serial.print("\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }
  if (Lsen == 1) {                  //LEFT Sign

    Serial.print("vis ls,1") + f;
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }
  else if (Lsen == 0) {
    Serial.print("vis ls,0") + f;
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }

  if (Rsen == 1) {                  //RIGHT Sign
    Serial.print("vis rs,1");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }
  else {
    Serial.print("vis rs,0");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }

  Serial.print("p1.txt=\"");          //1st Pressure Bar
  Serial.print(String(Pb2));
  Serial.print("\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  Serial.print("p2.txt=\"");          ///2nd Pressure Bar
  Serial.print(String(Pb2));
  Serial.print("\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  if (aki < 20) {
    Serial.print("vis bl,1") + f;     //Low Battery
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

    Serial.print("vis bn,0") + f;     //Normal Battery
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

    Serial.print("vis wn,1") + f;     //Warning Indicator
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }

  else if (aki >= 20) {
    Serial.print("vis bl,0") + f;     //Low Battery
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

    Serial.print("vis bn,1") + f;     //Normal Battery
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

    Serial.print("vis wn,0") + f;     //Warning Indicator
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }

  Serial.print("tv.txt=\"");
  Serial.print(String(ak));           //Car Battery
  Serial.print("\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);


  if (Fdoor == 0 & Ldoor == 0 ) {     //Door
    Serial.print("vis ds,1") + f;
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

  }

  else if (Fdoor == 1 & Ldoor == 1 ) {
    Serial.print("vis ds,0") + f;
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }
  if (Fdoor == 0 & Ldoor == 1 ) {     //Door
    Serial.print("vis ds,0") + f;
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

  }

  else if (Fdoor == 1 & Ldoor == 0 ) {    //Door
    Serial.print("vis ds,0") + f;
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }

  if (belt == 1) {                      //Safety Belt
    Serial.print("vis sb,0") + f;
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

  }

  else if (belt == 0) {                 //Safety Belt
    Serial.print("vis sb,1") + f;
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }


  if (Hbem == 1) {                      //HIGH Beam
    Serial.print("vis hb,1") + f;
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

  }
  else if (Hbem == 0) {

    Serial.print("vis hb,0") + f;
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }

  if (Lbem == 1) {                      //LOW Beam
    Serial.print("vis lb,1") + f;
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

  }

  else if (Lbem == 0) {           
    Serial.print("vis lb,0") + f;
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }

  Serial.println(); */
}
