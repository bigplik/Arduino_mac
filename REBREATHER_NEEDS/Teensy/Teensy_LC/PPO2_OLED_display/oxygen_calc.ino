  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------


void OxygenCalculations(){
  
  
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  //adc3 = ads.readADC_SingleEnded(3);
  
    for(int j = 0 ; j < 10 ; j++)

{
  


firstValue1 += adc0;                         //sumowanie kolejnych pomiarów
firstValue2 += adc1;
firstValue3 += adc2;
delay(100);                                               //opóźnienie

}

firstValue1 /=10;                                                            //liczenie wartości średniej
firstValue2 /=10;                                                            //i zapamiętanie jej
firstValue3 /=10;


SmV = (firstValue1/5.0); //dane przeliczone do miliVolt dla S1
S2mV = (firstValue2/5.0);
S3mV = (firstValue3/5.0);
}
