//with MapleMini

volatile int count = 0; // must declare volatile, since it's
                          // modified within the blink() handler

void setup() {
    pinMode(5, PWM);
    pinMode(3, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    attachInterrupt(3, up, FALLING);
    attachInterrupt(4, down, FALLING);
}

void loop() {
    if(count>65535) count = 65535;
    else if(count<0) count = 0;
    pwmWrite(5, count);
}

void up() {
    if(digitalRead(4)==LOW){
          count=count+200;
    }
    else{
      count=count-200;
    }
}

void down() {
    if(digitalRead(3)==LOW){
          count=count-200;
    }
    else{
      count=count+200;
    }
}

