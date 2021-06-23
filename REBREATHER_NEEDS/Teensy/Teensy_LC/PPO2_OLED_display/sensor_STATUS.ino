 void sensor_STATUS(){
 
 //*********************status sensorów
  uint16_t b;
    for( b=0; b<128; b++) display.drawPixel(b, 16, 1);
    
    for( b=0; b<128; b++) display.drawPixel(b, 32, 1);
    
    for( b=0; b<128; b++) display.drawPixel(b, 48, 1);
    
    for( b=17; b<64; b++) display.drawPixel(20, b, 1); // oś pionowa
    for( b=17; b<64; b++) display.drawPixel(75, b, 1);

  display.display();
  
  //************************************************
  //***********opis danych do sensorów w tabeli
  
  //************nagłówek tabeli
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(4,6);
  display.println("#     mV     Status");
  
   //**********************numery sensorów
  display.setCursor(2,20);
  display.println("1");
  display.setCursor(2,36);
  display.println("2");
  display.setCursor(2,52);
  display.println("3");
  
  //***************wartości sensorów w miliVoltach
  //* 0.039906103 correction factor to get real mV value
  display.setCursor(35,20);
  display.println(SmV* 0.039906103);
  display.setCursor(35,36);
  display.println(S2mV* 0.039906103);
  display.setCursor(35,52);
  display.println(S3mV* 0.039906103);
  display.display();
  
  //*********************sensor ok lub old lub Err
  if(SmV >= 9.00 && SmV <= 13.00){
    display.setCursor(92,20);
    display.println("OK");
    display.display();
  }
  else if(SmV <=8.99 && SmV >=8.00){
    display.setCursor(92,20);
    display.println("OLD");
    display.display();
  }else{
    display.setCursor(92,20);
    display.println("Err");
    display.display();
  }
  
  if(S2mV >= 9.00 && S2mV <= 13.00){   // 2 sensor
    display.setCursor(92,36);
    display.println("OK");
    display.display();
  }
  else if(S2mV <=8.99 && S2mV >=8.00){
    display.setCursor(92,36);
    display.println("OLD");
    display.display();
  }else{
    display.setCursor(92,36);
    display.println("Err");
    display.display();
  }
  
  if(S3mV >= 9.00 && S3mV <= 13.00){      // 3 sensor
    display.setCursor(92,52);
    display.println("OK");
    display.display();
  }
  else if(S3mV <=8.99 && S3mV >=8.00){
    display.setCursor(92,52);
    display.println("OLD");
    display.display();
  }else{
    display.setCursor(92,52);
    display.println("Err");
    display.display();
  }
  
  delay(5000);

  // Clear the buffer.
  display.clearDisplay();
  
 }
