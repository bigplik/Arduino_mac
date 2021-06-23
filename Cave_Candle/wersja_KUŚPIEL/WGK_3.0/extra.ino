

void shortClick(){
  if(count<21) _count = count;
}

void longPress(){
   if(count>20){
        analogWrite(1,200);
        _count=0;
      }
}

void calibration() {
  battery=0;
  for(int i=10;i>0;i--){
    battery +=analogRead(A1);
    delay(20);
  }

  batCount=0;
  battery /=10;
}

