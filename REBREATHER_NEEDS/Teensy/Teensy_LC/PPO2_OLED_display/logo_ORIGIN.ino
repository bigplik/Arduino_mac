 void logo_ORIGIN(){
 
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(10,22);
  display.println("Origin");
  display.display();
    delay(2500);
    uint16_t a;
    for( a=0; a<128; a++) display.drawPixel(a, 17, 1);
    for( a=0; a<128; a++) display.drawPixel(a, 50, 1);
    display.display();
    delay(800);
    
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(44,0);
  display.println("BDS");
  display.display();
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(29,56);
  display.println("PPO2 Display");
  display.display();
    delay(3000);
  display.clearDisplay();
  
 }
