//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ARDUINO BATTERY CAPACITY TESTER
//Version-1.0
//by deba168,INDIA
//Dated : 04/09/2016
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#define MOSFET_Pin 3
#define Bat_Pin A3
#define Res_Pin A1
#define Buzzer_Pin 9
  
float Capacity = 0.0; // Capacity in mAh
float Res_Value = 10.0;  // Resistor Value in Ohm
float Vcc = 4.51; // Voltage of Arduino 5V pin ( Mesured by Multimeter )
float Current = 0.0; // Current in Amp
float mA=0;         // Current in mA
float Bat_Volt = 0.0;  // Battery Voltage 
float Res_Volt = 0.0;  // Voltage at lower end of the Resistor 
float Bat_High = 4.3; // Battery High Voltage
float Bat_Low = 2.9; // Discharge Cut Off Voltage
unsigned long previousMillis = 0; // Previous time in ms
unsigned long millisPassed = 0;  // Current time in ms
float sample1 =0;
float sample2= 0;
int x = 0;
int row = 0;


//******************************Buzzer Beep Function *********************************************************

  void beep(unsigned char delay_time){
  analogWrite(9, 20);      // PWM signal to generate beep tone
  delay(delay_time);          // wait for a delayms ms
  analogWrite(Buzzer_Pin, 0);  // 0 turns it off
  delay(delay_time);          // wait for a delayms ms  

}  

//*******************************Setup Function ***************************************************************
  
  void setup() {
   Serial.begin(9600);
   pinMode(2,OUTPUT);
   pinMode(13,OUTPUT);
   pinMode(MOSFET_Pin, OUTPUT);
   pinMode(Buzzer_Pin, OUTPUT);
   digitalWrite(MOSFET_Pin, LOW);  // MOSFET is off during the start
   Serial.println("CLEARDATA");
   Serial.println("LABEL,Time,Bat_Volt,capacity");
     for(int i=0;i< 100;i++)
  {
   sample1=sample1+analogRead(Bat_Pin); //read the voltage from the divider circuit
   delay (2);
  }
  sample1=sample1/100; 
  Bat_Volt = sample1 *Vcc/ 1024.0; 
   Serial.println(Bat_Volt);
   
   //Serial.println("Arduino Battery Capacity Tester v1.0");
   //Serial.println("BattVolt Current mAh");
  }
  //********************************Main Loop Function***********************************************************
  void loop() {
 // Vcc = readVcc()/1000.0; // Conevrrt mV to Volt

  
  // Voltage devider Out = Bat_Volt * R2/(R1+R2 ) // R1 =10K and R2 =10K 
  
  //************ Measuring Battery Voltage ***********

  static int statusWork = 0;

  switch (statusWork) {

    case 0:    // your hand is on the sensor

          for(int i=0;i< 100;i++)
          {
           sample1=sample1+analogRead(Bat_Pin); //read the voltage from the divider circuit
           delay (2);
          }
          sample1=sample1/100; 
          Bat_Volt = sample1 *Vcc/ 1024.0; 
        
          // *********  Measuring Resistor Voltage ***********
        
           for(int i=0;i< 100;i++)
          {
           sample2=sample2+analogRead(Res_Pin); //read the voltage from the divider circuit
           delay (2);
          }
          sample2=sample2/100;
          Res_Volt = sample2 * Vcc/ 1024.0;
        
          //********************* Checking the different conditions *************
          
          if ( Bat_Volt > Bat_High){
            digitalWrite(MOSFET_Pin, LOW); // Turned Off the MOSFET // No discharge 
            beep(200);
            Serial.println( "Warning High-V! ");
            delay(5000);
            statusWork=1;
           }
           
           else if(Bat_Volt < Bat_Low){
              digitalWrite(MOSFET_Pin, LOW);
              beep(200);
              Serial.println( "Warning Low-V! ");
              delay(5000);
              statusWork=1;
          }
          else if(Bat_Volt > Bat_Low && Bat_Volt < Bat_High  ) { // Check if the battery voltage is within the safe limit
              digitalWrite(MOSFET_Pin, HIGH);
              millisPassed = millis() - previousMillis;
              Current = (Bat_Volt - Res_Volt) / Res_Value;
              mA = Current * 1000.0 ;
              Capacity = Capacity + mA * (millisPassed / 3600000.0); // 1 Hour = 3600000ms
              previousMillis = millis();
              Serial.println("DATA,TIME,"); Serial.print("V ");Serial.println(Bat_Volt); 
              Serial.print("mA "); Serial.println(Capacity,1);
              Serial.print("I "); Serial.println(mA);
              Serial.println("");
              row++;
              x++;
              delay(4000); 
         
             }
      break;
      
    case 1:    // your hand is close to the sensor
        static int count = 0;
              Serial.println("Fihished DATA,"); Serial.print("V ");Serial.println(Bat_Volt); 
              Serial.print("mA "); Serial.println(Capacity,1);
              Serial.print("I "); Serial.println(mA);
              Serial.println("");
              digitalWrite(2,1);
              delay(1000);
              digitalWrite(2,0);
              delay(5000);
              count++;
              if(count >=3){
              digitalWrite(2,0);
              digitalWrite(13,1);
              statusWork=2;
              }
              
      break;

    case 2:
              Serial.println("Fihished DATA,"); Serial.print("V ");Serial.println(Bat_Volt); 
              Serial.print("mA "); Serial.println(Capacity,1);
              Serial.print("I "); Serial.println(mA);
              Serial.println("");
              delay(5000);
      break;
  }
   //**************************************************

 }    
