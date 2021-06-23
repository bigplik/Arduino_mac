unsigned long lastPass = 0;
int state = 0;
void setup() {
    pinMode(11, OUTPUT);
}
void loop() {
    if (millis() > lastPass) {
      digitalWrite(11, (state) ? HIGH : LOW);
      state = !state;
      lastPass = millis() + 5000UL;
    }
}
