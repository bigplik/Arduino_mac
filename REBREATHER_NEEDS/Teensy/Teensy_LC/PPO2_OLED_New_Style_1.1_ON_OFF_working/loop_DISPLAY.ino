

void loopDISPLAY(){


    display.setTextSize(2);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(0,0); display.print(PPO2);
    display.setCursor(0,20); display.print(PPO22);
    display.setCursor(0,40); display.print(PPO23);

    display.setCursor(98,2); display.print("99");
    display.setCursor(98,40); display.print("70");
    display.setTextSize(1);
    display.setCursor(121,2); display.print("%");
    display.setCursor(121,40); display.print("C");
    display.setCursor(99,25); display.print("3.7V");

    display.fillRoundRect(51, 0, 39, 57, 5, WHITE);
    display.setTextSize(1);
    display.setTextColor(BLACK,WHITE);
    display.setCursor(53,5); display.print(SmVact+0.2);
    //display.setCursor(75,5); display.print("mV");
    display.setCursor(53,24); display.print(SmVact2+0.2);
    //display.setCursor(75,24); display.print("mV");
    display.setCursor(53,43); display.print(SmVact3+0.2);
    //display.setCursor(75,43); display.print("mV");

    display.drawRoundRect(94, 0, 34, 19, 5, WHITE);
    display.drawRoundRect(94, 38, 34, 19, 5, WHITE); 
    //x start position,y start position, szer, wys, zaokraglenie
                
    display.display();
  
}

