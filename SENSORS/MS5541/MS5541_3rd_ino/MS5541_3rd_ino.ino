
/*
 MS5541 Pressure Sensor demonstration sketch
 To obtain the calibration factors run the read-calwords-sketch before.
 
 Circuit:
 MS5541 sensor attached to pins 10 - 13:
 MOSI: pin 11 //in
 MISO: pin 12 //out
 SCK: pin 13
 MCLK: pin 9
CS is not in use, but might be pin 10
  
 created August 2011
 by SMStrauch based on application note AN510 from www.intersema.ch (http://www.meas-spec.com/downloads/Using_SPI_Protocol_with_Pressure_Sensor_Modules.pdf), 
 and with help of robtillaart and ulrichard. Thanks!
 */

// include librariy:
#include <SPI.h>

// generate a MCKL signal 
const int clock = 9;

//include the calibration factors according to your individual sensor; they MUST be long for internal calculation of the compensated values
//intersema.ch provides a file with expected values
const long c1 = 2723;
const long c2 = 4648;
const long c3 = 388;
const long c4 = 224;
const long c5 = 2309;
const long c6 = 54;

void resetsensor() //this function keeps the sketch a little shorter
{
  SPI.setDataMode(SPI_MODE0); 
  SPI.transfer(0x15);
  SPI.transfer(0x55);
  SPI.transfer(0x40);
}

void setup() {
  Serial.begin(9600);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV32); //divide 16 MHz to communicate on 500 kHz
  pinMode(clock, OUTPUT); //sets clockpin on output
}

void loop() 
{
  TCCR1B = (TCCR1B & 0xF8) | 1 ; //generates the MCKL signal
  analogWrite (clock, 128) ; 

  void resetsensor(); //resets the sensor, be aware SPI remains in Mode 0 afterwards!

  //Temperature:
  unsigned int tempMSB = 0; //first byte of value
  unsigned int tempLSB = 0; //last byte of value
  unsigned int D2 = 0;
  SPI.transfer(0x0F); //send first byte of command to get temperature value
  SPI.transfer(0x20); //send second byte of command to get temperature value
  delay(35); //wait for conversion end
  SPI.setDataMode(SPI_MODE1); //change mode in order to listen
  tempMSB = SPI.transfer(0x00); //send dummy byte to read first byte of value
  tempMSB = tempMSB << 8; //shift first byte
  tempLSB = SPI.transfer(0x00); //send dummy byte to read second byte of value
  D2 = tempMSB | tempLSB; //combine first and second byte of value
  Serial.print("Temperature raw =");
  Serial.println(D2); //voilá!

  void resetsensor();//resets the sensor 

  //Pressure:
  unsigned int presMSB = 0; //first byte of value
  unsigned int presLSB =0; //last byte of value
  unsigned int D1 = 0;
  SPI.transfer(0x0F); //send first byte of command to get pressure value
  SPI.transfer(0x40); //send second byte of command to get pressure value
  delay(35); //wait for conversion end
  SPI.setDataMode(SPI_MODE1); //change mode in order to listen
  presMSB = SPI.transfer(0x00); //send dummy byte to read first byte of value
  presMSB = presMSB << 8; //shift first byte
  presLSB = SPI.transfer(0x00); //send dummy byte to read second byte of value
  D1 = presMSB | presLSB; //combine first and second byte of value
  Serial.print("Pressure raw =");
  Serial.println(D1);

  //calculation of the real values by means of the calibration factors and the maths
  //in the datasheet
  const long UT1 = (c5 << 3) + 10000;
  const long dT = D2 - UT1;
  const double TEMP = 200 + ((dT * (c6 + 100)) >> 11);
  const long OFF  = c2 + (((c4 - 250) * dT) >> 12) + 10000;
  const long SENS = (c1/2) + (((c3 + 200) * dT) >> 13) + 3000;
  long PCOMP = (SENS * (D1 - OFF) >> 12) + 1000;
  double TEMPREAL = TEMP/10;
  //2nd order compensation only for T > 0°C
  const long dT2 = dT - ((dT >> 7 * dT >> 7) >> 3);
  const float TEMPCOMP = (200 + (dT2*(c6+100) >>11))/10;

  Serial.print("Real Temperature [°C]=");
  Serial.println(TEMPREAL);

  Serial.print("Compensated pressure [mbar] =");
  Serial.println(PCOMP);

  Serial.print("2nd order compensated temperature [°C] =");
  Serial.println(TEMPCOMP);  

  delay(5000);
}


