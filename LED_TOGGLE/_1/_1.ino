int state = 0;
void setup() {
    pinMode(11, OUTPUT);
}
void loop() {
    digitalWrite(11, (state) ? HIGH : LOW);
    state = !state;
    delay(100);
}
