

void shortClick(){
  if(count<21) _count = count;
}

void longPress(){
   if(count>20){
        digitalWrite(11,0);
        digitalWrite(12,0);
        digitalWrite(13,1);
        _count=0;
      }
}

void restValue(){
  
}

