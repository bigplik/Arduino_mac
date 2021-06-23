/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that writes the words, presses Enter, presses a media key and then Ctrl+Alt+Delete
 */
#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

byte BTN = 35;
byte BTN2 = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  pinMode(0,INPUT_PULLUP);
  pinMode(35,INPUT_PULLUP);
  bleKeyboard.begin();
}

void loop() {
  if(bleKeyboard.isConnected()) {
    //Serial.println("Sending 'Hello world'...");
    //bleKeyboard.print("Hello world");

    //delay(1000);
    if(digitalRead(BTN)==0){
    Serial.println("Sending  key...");
    bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
    delay(200);
    }
    else if(digitalRead(BTN2)==0){
    Serial.println("Sending  key...");
    bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
    delay(200);
    }
    /*
    Serial.println("Sending Play/Pause media key...");
    bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);

    delay(1000);

    Serial.println("Sending Ctrl+Alt+Delete...");
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.press(KEY_DELETE);
    */
    delay(100);
    bleKeyboard.releaseAll();
  }

  //Serial.println("Waiting 5 seconds...");
  //delay(1000);
}
