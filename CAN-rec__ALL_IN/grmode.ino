void throttle(){
            if (mode == 0){
               Serial.print("pGear.pic=");  //Gear Indicator
                Serial.print(16);
                Serial.write(0xff);
                Serial.write(0xff);
                Serial.write(0xff);
            }
            
            else if (mode == 1){
            //  gr_mode = 16;     //Neutral 
                Serial.print("pGear.pic=");  //Gear Indicator
                Serial.print(16);
                Serial.write(0xff);
                Serial.write(0xff);
                Serial.write(0xff);
           
            }
            
            else if (mode == 2){
             // gr_mode = 17;  //Drive
              Serial.print("pGear.pic=");  //Gear Indicator
                Serial.print(15);
                Serial.write(0xff);
                Serial.write(0xff);
                Serial.write(0xff);
            }
      
            else if (mode == 3){
             // gr_mode = 15;  //Reverse
              Serial.print("pGear.pic=");  //Gear Indicator
                Serial.print(15);
                Serial.write(0xff);
                Serial.write(0xff);
                Serial.write(0xff);
            }     
        
}

/* void sen(){
  if (Lsen == 1){     //LEFT Sign
             
             Serial.print("vis left,1") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
      }
     else if (Lsen == 0) {
             Serial.print("vis left,0") + f;
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
      }

     if (Rsen == 1){     //RIGHT Sign
             Serial.print("vis right,1");
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
      }
     else {
             Serial.print("vis right,0");
             Serial.write(0xff);
             Serial.write(0xff);
             Serial.write(0xff);
      } 
} */
