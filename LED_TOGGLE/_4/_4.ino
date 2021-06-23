elapsedMillis  lastPass;

int state = 0;
void setup() {
    pinMode(11, OUTPUT);
}
void loop() {
    if (lastPass >= 2000L) {
      digitalWrite(11, (state) ? HIGH : LOW);
      state = !state;
      lastPass = 0;
    }
}
