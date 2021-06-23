

void battery(){

  for(int i=0;i<10;i++){
  batteryLevel += analogRead(A1);
  }
  batteryLevel /=10;
}

