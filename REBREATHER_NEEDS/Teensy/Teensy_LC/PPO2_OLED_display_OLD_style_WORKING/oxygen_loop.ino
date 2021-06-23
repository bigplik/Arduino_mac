  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------


void OxygenLoop(){
  
  

  //adc3 = ads.readADC_SingleEnded(3);
  
    for(int a = 0 ; a < 100 ; a++)

{
  
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);

secondValue1 += adc0;                         //sumowanie kolejnych pomiarów
secondValue2 += adc1;
secondValue3 += adc2;
delay(5);                                               //opóźnienie

}

secondValue1 /=100;                                                            //liczenie wartości średniej
secondValue2 /=100;                                                            //i zapamiętanie jej
secondValue3 /=100;


SmVact = (secondValue1*0.00765995688)+0.1; //dane przeliczone do miliVolt dla S1 zazwyczaj 5.0V
SmVact2 = (secondValue2*0.00765995688)+0.1;
SmVact3 = (secondValue3*0.00765995688)+0.1;
//0.0078125
//+0.7 zamiast 0.1
delay(50);
}
