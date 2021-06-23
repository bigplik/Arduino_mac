void warning(){            
  if ( PPO2 <= 0.40 || PPO22 <0.40 || PPO23 <0.40){
    display.setTextSize(2.9);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(74,47);
    display.print("LOW!");
    display.display();
    delay(500);
    display.setCursor(74,47);
    display.print("     ");
    display.display();
    delay(50);
    
  }else if ( PPO2 >= 1.40 || PPO22 >= 1.40 || PPO23 >= 1.40){
    display.setTextSize(2.9);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(68,47);
    display.print("HIGH!");
    display.display();
    delay(500);
    display.setCursor(68,47);
    display.print("     ");
    display.display();
    delay(50);
    
  }else{
     display.setTextSize(2.9);
     display.setTextColor(WHITE, BLACK);
     display.setCursor(65,47);
     display.print("     ");
     display.display();     
     
  }
}
