#define DIN 2

int Co2MIN = 150;
int Co2MAX = 0;

boolean DSTAT = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(DIN,INPUT);
}

void loop() {
  

DSTAT = digitalRead(DIN);
  // put your main code here, to run repeatedly:
int sensor = analogRead(A0);
Serial.println(sensor);
Serial.println(DSTAT);
Serial.print("Co2MIN "); Serial.println(Co2MIN);
Serial.print("Co2MAX "); Serial.println(Co2MAX);
if(Co2MIN > sensor) { Co2MIN = sensor; }
if(Co2MAX < sensor) { Co2MAX = sensor; }

delay(1000);
}
