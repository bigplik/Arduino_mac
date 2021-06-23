void calibration() {
  capacity=0;
  for(int i=10;i>0;i--){
    capacity +=analogRead(A2);
    delay(20);
  }

  batCount=0;
  capacity /=10;
}
