double voltage, voltageOut;
int sendValue;

void setup() {
  Serial.begin(115200); // Ignored by Maple. But needed by boards using hardware serial via a USB to Serial adaptor

  pinMode(4,PWM);

  
}

void loop() {
    // Read the sensor:
   voltageOut = voltage * 19859.0909090909;
   pwmWrite(4,voltageOut);
    //
    if (Serial.available() > 0) {
        char inByte = Serial.read();

        switch (inByte) {
        case 'a':
            voltage = 0;
            break;
        case 'b':
            voltage = 1;
            break;
        case 'c':
            voltage = 2;
            break;
        case 'd':
            voltage = 2.5;
            break;
        case 'e':
            voltage = 3.3;
            break;
        }
    }
}
