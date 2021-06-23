int LED = 13;

const int  buttonPin = 2;    // the pin that the pushbutton is attached to
const int  buttonPin2 = 4;
int ocena1 = 1;   // counter for the number of button presses
int ocena2 = 0;
int buttonState = 0;         // current state of the button
int buttonState2 = 0;
int buttonState3 = 0;
int lastButtonState = 0;
int lastButtonState2 = 0;
int alt_case = 0;


void setup(){
  
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
 pinMode(buttonPin, INPUT);
 pinMode(buttonPin2, INPUT);
  
}




void loop(){
  
    lista();
  /*
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
  
  */
  
}


void lista(){
  
    int lista = ocena1;
    int cena;
    int kal_level;
   
  buttonState = digitalRead(buttonPin);
  buttonState2 = digitalRead(buttonPin2);
 
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
  
  
  //***********SECOND BUTTON****************8
  
 if(lista == 2){
   if (buttonState2 != lastButtonState2) {
    // if the state has changed, increment the counter
   if (buttonState2 == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      alt_case++;
      Serial.println("on");
      //Serial.print("number of button pushes:  ");
      Serial.println(alt_case);
    } 
    else {}
  }
 
  lastButtonState2 = buttonState3;
  
   if(alt_case > 2){
       
       alt_case = 0
       ;
    }
  
 }
 
 if(lista != 2){
 if (buttonState2 != lastButtonState2) {
    // if the state has changed, increment the counter
   if (buttonState2 == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      ocena2++;
      Serial.println("on");
      //Serial.print("number of button pushes:  ");
      Serial.println(ocena2);
    } 
    else {}
  }
 
  lastButtonState2 = buttonState2;
  
 }
  
  //***************main menu count settings*****************
  /*
    int ocena = ocena1;
    int cena;
    int kal_level;
    */  
    if(ocena1 > 7){
        lista = 1;
        ocena1 =1;
    }
    
    
    
    if(ocena2 > 1){
       
       ocena2  = 0;
    }
    
    
    
    //****************  ta funkcja nie działa poprawnie, zmienia watości
    //pomiedzy A i B jednak kiedy zrobi to w "kalibracji" to potem zmienia
    //też w "solenoidzie"
   
  if(lista == 2 && alt_case == 0){
        kal_level = 'A';
    }
    else if(lista == 2 && alt_case == 1){
        kal_level = 'B';
    }
    else if(lista == 2 && alt_case == 2){
        kal_level = 'C';
    }
   
    //****************
    
    else if(lista == 3){
        cena = 'A';
    }else if(lista == 4){
        lista = 3;
        cena = 'B';
    }
    
    
    //***************select button counter*****************
   
   // stan;
   
   
   
   
   if(lista == 3 && cena == 'A' && ocena2 == 0){
       Serial.println("Solenoid OFF");
       delay(200);
       digitalWrite(LED, LOW);
   }
   else if(lista == 3 && cena == 'A' && ocena2 == 1){
       Serial.println("Solenoid ON");
       delay(200);
       digitalWrite(LED, HIGH);
   }
   
    

    switch(lista){
        case 1:
            Serial.println("SWITCH: Jedynka\n");
            break;
        case 2:
            switch(kal_level){
                case 'A':
                    Serial.println("Kalibracja 0-300");
                    break;
                case 'B':
                    Serial.println("Kalibracja 300-600");
                    break;
                case 'C':
                    Serial.println("Klibracja >600");
                    break;
                default:
                Serial.println("back");
            }
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
            lista = 1;
    }
    
    delay(500);
  
}
