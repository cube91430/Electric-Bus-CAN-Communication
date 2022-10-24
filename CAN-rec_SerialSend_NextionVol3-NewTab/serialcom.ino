void serial(){
    //NEXTION-Display

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

        //HAND - BRAKE
      if (hnd_brk == 0){
        Serial.print("Brake OFF");
        Serial.print(" , ");
        Serial.print("vis temp,0") +f;
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);

        Serial.print("tStat.txt=\"");
        Serial.print("STOP");
        Serial.print("\"");
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

      Serial.print("tOdo.txt=\"");
      Serial.print(odo);
      Serial.print("\"");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      
      Serial.print("tVolt.txt=\"");
      Serial.print(akbat);
      Serial.print("\"");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);  
      
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

}
