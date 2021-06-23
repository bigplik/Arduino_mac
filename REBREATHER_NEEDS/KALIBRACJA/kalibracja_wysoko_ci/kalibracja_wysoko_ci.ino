

void altCal(){
  
  switch(altLevel){
    case 0:
      //sea level
      Serial.println("0-300m");
      break;
    case 1:
      //301-600m
      Serial.println("301-600m");
      break;
      
    case 2:
      //>600m
      Serial.println("> 600m");
      break;
    }
    delay(1);
    
    //warunki dla wyświetlania PPO2
    
    if(altLevel == 0){   //sea level
      Alt_adjPPO2 = PPO2;
      Alt_adjPPO22 = PPO22;
      Alt_adjPPO23 = PPO23;      
      
    }else                //300m level x 0.965ATM
    if(altLevel == 1){
      Alt_adjPPO2 = PPO2 * 0.965;
      Alt_adjPPO22 = PPO22 * 0.965;
      Alt_adjPPO23 = PPO23 * 0.965;      
    
    }else               // > 600m level x 0.931ATM
    if(altLevel == 2){
      Alt_adjPPO2 = PPO2 * 0.931;
      Alt_adjPPO22 = PPO22 * 0.931;
      Alt_adjPPO23 = PPO23 * 0.931;      
    
    }else
    if(altLevel > 2){
      altLevel = 0;
      
    }
