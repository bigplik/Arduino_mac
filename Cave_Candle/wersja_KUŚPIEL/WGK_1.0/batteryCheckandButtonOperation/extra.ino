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

void case0(){
  if(!button){
      delay(20);
      count++;
      longPress();
      shortClick();

    }
    else if(button){
      count = 0;
      _count0 = 0;
      digitalWrite(11,0);
      digitalWrite(12,0);
      digitalWrite(13,0);
      if(SP){
        delay(200);
        _count=0;
        tryb=1;
      }
    }
}

void case1(){
      if(!button){
      delay(20);
      count++;
      longPress();
      shortClick();

    }
    else if(button){
      count = 0;
      _count0 = 0;
      digitalWrite(11,0);
      digitalWrite(12,1);
      digitalWrite(13,0);
      if(SP){
        delay(200);
        _count=0;
        tryb = 2;
      }
    }
}

void case2(){
      if(!button){
      digitalWrite(12,0);
      delay(20);
      count++;
      longPress();
      shortClick();

    }
    else if(button){
      count = 0;
      _count0 = 0;
      digitalWrite(11,1);
      digitalWrite(12,0);
      digitalWrite(13,0);
      if(SP){
        delay(200);
        _count=0;
        tryb = 0;
      }
    }
}

void case3(){
  
}

