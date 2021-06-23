int firstValue1 = 0;
int firstValue2 = 0;
int firstValue3 = 0;
int chooseGas = 0;

float SmV;
float S2mV;
float S3mV;
float SmVact;
float SmVact2;
float SmVact3;
float PPO2;
float PPO22;
float PPO23;
float Adj_mV;
float Adj_mV2;
float Adj_mV3;
float CSmV;
float CSmV2;
float CSmV3;


void setup(){
  
  Serial.begin(9600);
      for(int j = 0 ; j < 10 ; j++)

{

firstValue1 += analogRead(A0);                          //sumowanie kolejnych pomiarów
firstValue2 += analogRead(A1);
firstValue3 += analogRead(A2);
delay(100);                                               //opóźnienie

}

firstValue1 /=10;                                                            //liczenie wartości średniej
firstValue2 /=10;                                                            //i zapamiętanie jej
firstValue3 /=10;


SmV = (firstValue1/4.9); //dane przeliczone do miliVolt dla S1
S2mV = (firstValue2/4.9); //dla S2
S3mV = (firstValue3/4.9); //dla S3
  
}


void loop(){
  
    SmVact = (analogRead(A0)/4.9);
    SmVact2 = (analogRead(A1)/4.9);
      SmVact3 = (analogRead(A2)/4.9);
           
  
   // int sensorValue = analogRead(A0);
  PPO2 = (SmVact * (0.21/SmV));
    PPO22 = (SmVact2 * (0.21/S2mV));

    PPO23 = (SmVact3 * (0.21/S3mV));
  
  gasCalibration();
  SmV_correction();
  
  Serial.println("SmV S2mV S3mV");
  Serial.println(SmV);
    Serial.println(S2mV);
      Serial.println(S3mV);

  Serial.println("SmVact SmVact2 SmVact3");
  Serial.println(SmVact);
    Serial.println(SmVact2);
      Serial.println(SmVact3);


  Serial.println("CSmV CSmV2 CSmV3");
  Serial.println(CSmV);
    Serial.println(CSmV2);
      Serial.println(CSmV3);

  Serial.println("PPO2 PPO22 PPO23 ");
  Serial.println(PPO2);
    Serial.println(PPO22);
      Serial.println(PPO23);


  Serial.println("---------------");
  delay(2000);
  
}


void SmV_correction(){  //SmV correct value at 02 at 1ATM
  
  float CSmVfact = 97/21;
  CSmV = SmV * CSmVfact;
      float CSmVfact2 = 97/21;
      CSmV2 = S2mV * CSmVfact2;
        float CSmVfact3 = 97/21;
        CSmV3 = S3mV * CSmVfact3;
}


void gasCalibration() {
  
  switch(chooseGas){
    case 0:
      //air
      Serial.println("air");
      break;
    case 1:
      //nx32
      Serial.println("nx32");
      break;
    case 2:
      //nx50
      Serial.println("nx50");
      break;
    case 3:
      //O2
      Serial.println("O2");
      break;
      
  }    
      //air calibration
      if(chooseGas == 0){
        Adj_mV = SmV;      //no adjust is neccesary as automatic
        Adj_mV2 = S2mV;    //calibration was made on beggining
        Adj_mV3 = S3mV; 
 
      }else
      //nx 32
      if(chooseGas == 1){        //adjust factor for nx32 is 1.524
        Adj_mV = SmV   *1.524;
        Adj_mV2 = S2mV *1.524;
        Adj_mV3 = S3mV *1.524;
      
      }else
      //nx 50
      if(chooseGas == 2){        //adjust factor for nx50 is 2.381
        Adj_mV = SmV   *2.381;
        Adj_mV2 = S2mV *2.381;
        Adj_mV3 = S3mV *2.381;
        
      }else
      //O2
      if(chooseGas == 3){     
        Adj_mV = SmV   *4,71;    //4,71 is factor for O2 calibration
        Adj_mV2 = S2mV *4,71;
        Adj_mV3 = S3mV *4,71;
        if(SmVact != CSmV){
          SmVact = SmVact * (SmVact/SmV);
          
        }
      }
      
      
      if(chooseGas > 3){
        chooseGas = 0;
        
      }
  
  
  
 
  } 
  
  
  
  

