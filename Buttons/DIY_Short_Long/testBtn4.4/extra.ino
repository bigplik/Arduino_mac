

void shortClick(){
  if(count<21) _count = count;
}

void longPress(){
   if(count>20){
        digitalWrite(1,0);
        digitalWrite(3,0);
        digitalWrite(4,1);
        _count=0;
      }
}
