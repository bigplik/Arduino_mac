

void shortClick(){
  if(count<21) _count = count;
}

void longPress(){
   if(count>20){
        analogWrite(1,200);
        _count=0;
      }
}
