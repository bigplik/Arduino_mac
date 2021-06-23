const int  buttonPin = 2;    // the pin that the pushbutton is attached to
int ocena1 = 1;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;

void setup(){
  
 Serial.begin(9600);
 pinMode(buttonPin, INPUT);
 
 
}

void loop(){
  
  buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
  if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      ocena1++;
      Serial.println("on");
      //Serial.print("number of button pushes:  ");
      Serial.println(ocena1);
    } 
    else {}
  }
 
  lastButtonState = buttonState;

  
    
    //int menu;
   // menu = buttonPushCounter;
    int ocena = ocena1;
    
    int cena;
     
  
   /*

    if(menu == 1){
        ocena = 1;
    }else if(menu == 2){
        ocena = 2;
    }else if(menu == 3){
        ocena = 3;
    }else if(menu == 4){
        ocena = 4;
    }else if(menu == 5){
        ocena = 5;
    }else if(menu == 6){
        ocena = 6;
    }else if(menu == 7){
        ocena = 7;
    */
    if(ocena1 > 7){
        ocena = 1;
        ocena1 =1;
        
    }
    

    else if(ocena == 3){
        cena = 'A';
    }else if(ocena == 4){
        ocena = 3;
        cena = 'B';
    }

    switch(ocena){
        case 1:
            Serial.println("SWITCH: Jedynka\n");
            break;
        case 2:
            Serial.println("SWITCH: Dwójka\n");
            break;
        case 3:
            switch(cena){
                case 'A':
                    Serial.println("SWITCH: A");
                    break;
                case 'B':
                    Serial.println("SWITCH: B");
                    break;
                default:
                Serial.println("SWITCH: Nieznana ocena\n");
            }
            break;
        case 5:
            Serial.println("SWITCH: Czwórka\n");
            break;
        case 6:
            Serial.println("SWITCH: Piątka\n");
            break;
        case 7:
            Serial.println("SWITCH: Szóstka\n");
            break;
        default:
            ocena = 1;
    }
    
    delay(500);
}
