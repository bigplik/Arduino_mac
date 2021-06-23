void setup() {
    pinMode(2, INPUT_ANALOG);
    pinMode(33, PWM);
}

void loop() {
    int sensorValue = analogRead(2);
    //map function below (0-4095 analog In bit resolution)
    //(0-65535 pwm analogWrite bit resolution)
    int ledFadeValue = map(sensorValue, 0, 4095, 0, 65535);
    pwmWrite(33, ledFadeValue);
}
