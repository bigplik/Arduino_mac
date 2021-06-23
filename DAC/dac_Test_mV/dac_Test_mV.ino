/*
 * for Maple Mini or STM32_blue
 */

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
            voltage = 0.0113;  //16mV
            break;
        case 'b':
            voltage = 0.0123;  //17mV
            break;
        case 'c':
            voltage = 0.0133;  //18mV
            break;
        case 'd':
            voltage = 0.01436;  //19mV
            break;
        case 'e':
            voltage = 0.0153;  //20mV
            break;
        case 'f':
            voltage = 0.01636;  //21mV
            break;
        case 'g':
            voltage = 0.01736;  //22mV
            break;
        case 'h':
            voltage = 0.0183;  //23mV
            break;
        case 'i':
            voltage = 0.0193;  //24mV
            break;
        case 'j':
            voltage = 0.0203;  //25mV
            break;
        case 'k':
            voltage = 0.026;
            break;
        case 'l':
            voltage = 0.027;
            break;
        case 'm':
            voltage = 0.028;
            break;
        case 'n':
            voltage = 0.029;
            break;
        case 'o':
            voltage = 0.030;
            break;
        case 'p':
            voltage = 0.031;
            break;
        case 'r':
            voltage = 0.032;
            break;
        case 's':
            voltage = 0.033;
            break;
        case 't':
            voltage = 0.034;
            break;
        case 'u':
            voltage = 0.035;
            break;
        case 'w':
            voltage = 0.036;
            break;
        case 'v':
            voltage = 0.037;
            break;
        case 'x':
            voltage = 0.038;
            break;
        case 'y':
            voltage = 0.039;
            break;
        case 'z':
            voltage = 0.040;
            break;
        }
    }
}
