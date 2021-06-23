#define ACTIVATED LOW 
#define ACTIV2 LOW
const int buttonPin = 20;  
const int button2 = 12;
const int ledPin =  6;
const int led2 = 33;
unsigned int rozmiar = 0;

int buttonState = 0;
int buttonState2 = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  //digitalWrite(buttonPin,HIGH);
  Serial.begin(9600);
}

void loop() {
  

  
  buttonState = digitalRead(buttonPin);
  buttonState2 = digitalRead(button2);
  if (buttonState == ACTIVATED) {

    rozmiar++;
    //delay(50);
  }else if (buttonState2 == ACTIV2) {
    rozmiar--;
    //delay(50);
  }
  
  if(rozmiar > 3) { rozmiar = 0; }
    switch (rozmiar) {
    case 0:
        digitalWrite(ledPin, HIGH);
        digitalWrite(led2, LOW);
      break;
    case 1:
        digitalWrite(led2, HIGH);
        digitalWrite(ledPin, LOW);
      break;
    case 2:
        digitalWrite(ledPin, LOW);
        digitalWrite(led2, LOW);
      break;
    case 3:
        digitalWrite(ledPin, HIGH);
        digitalWrite(led2, HIGH);
      break;    
  }
  delay(1);
  
  Serial.println(rozmiar);
  delay(500);
}
