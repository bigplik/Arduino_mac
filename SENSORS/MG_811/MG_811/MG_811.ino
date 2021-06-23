#define R 11 //led RED
#define L 12 //led YELLOW 1
#define G 13 //led GREEN
#define K 10 //led YELLOW 2
#define PIN 0 //analog PIN wired to co2 sensor
#define SOGLIA 1000 // 1000ppm OK value

unsigned int lettura = 0; //actual read value
unsigned int letturaOld = 0; //old read value
unsigned long time;

void reading(){ //led blinking while reading
 digitalWrite(R, LOW);
 digitalWrite(K, LOW);
 digitalWrite(G, LOW);
 int cont = 0;
 while (cont < 15){
   digitalWrite(L, HIGH);
   delay(500);
   digitalWrite(L, LOW);
   delay(500);
   cont++;
 } 
}

void victory(){ //led blinking when SOGLIA read
 digitalWrite(R, LOW);
 digitalWrite(G, HIGH);
 int cont = 0;
 while (cont < 15){
   digitalWrite(L, HIGH);
   digitalWrite(K, LOW);
   delay(500);
   digitalWrite(L, LOW);
   digitalWrite(K, HIGH);
   delay(500);
   cont++;
 } 
}

void rightWay(){ //led blinking when lettura < letturaOld
 digitalWrite(R, LOW);
 digitalWrite(K, LOW);
 digitalWrite(G, HIGH);
 int cont = 0;
 while (cont < 15){
   digitalWrite(L, HIGH);
   delay(500);
   digitalWrite(L, LOW);
   delay(500);
   cont++;
 } 
}

void wrongWay(){ //led blinking when lettura > letturaOld
 digitalWrite(R, HIGH);
 digitalWrite(K, LOW);
 digitalWrite(G, LOW);
 int cont = 0;
 while (cont < 15){
   digitalWrite(L, HIGH);
   delay(500);
   digitalWrite(L, LOW);
   delay(500);
   cont++;
 } 
}

void setup(){
  pinMode(PIN, INPUT);
  pinMode(R, OUTPUT);
  pinMode(L, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(K, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  time = millis();
  if ( time <= 300000) {  //5 minutes heating time
    digitalWrite(R, HIGH);
    digitalWrite(L, HIGH);
    digitalWrite(K, HIGH);
    digitalWrite(G, HIGH);
    letturaOld = analogRead(PIN); //keeps on reading
    //optional to change line below to
    //letturaOld = map(letturaOld,0,400,350,10000);
    letturaOld = map(letturaOld,0,1023,350,10000);
    Serial.print(time/1000);
    Serial.println(" seconds elapsed. Heating in progress...");
    delay(10000);
  }
  else if ( time > 300000 && time < 305000 ) { // leds off
   digitalWrite(R, LOW);
   digitalWrite(L, LOW);
   digitalWrite(K, LOW);
   digitalWrite(G, LOW);
  }
  else{
    //blinking YELLOW led while reading
    reading();
    delay(1500);
    lettura = analogRead(PIN);
    lettura = map(lettura,0,1023,350,10000);
    Serial.print("Old Value: "); //old reading
    Serial.print(letturaOld);
    Serial.print(" | New Value: "); //new reading
    Serial.println(lettura);
    if ( lettura < SOGLIA ){
      victory(); //we're done! ding ding ding!
      delay(1500);
    }
    else{
      if (lettura < letturaOld) 
        rightWay();
      else  
        wrongWay();
    }
    letturaOld = lettura;
    lettura = 0;
    delay(1500);
  }
}

