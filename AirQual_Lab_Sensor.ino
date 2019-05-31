
// Include Libraries
#include "Arduino.h"
#include "LiquidCrystal_PCF8574.h"
#include "MQ135.h"
#include "DHT.h"
// Pin Definitions



// Global variables and defines
// There are several different versions of the LCD I2C adapter, each might have a different address.
// Try the given addresses by Un/commenting the following rows until LCD works follow the serial monitor prints.
// To find your LCD address go to: http://playground.arduino.cc/Main/I2cScanner and run example.
//define LCD_ADDRESS 0x3F
#define LCD_ADDRESS 0x27
// Define LCD characteristics
#define LCD_ROWS 2
#define LCD_COLUMNS 16
#define SCROLL_DELAY 150
#define BACKLIGHT 255
#define DHTPIN 8     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
// object initialization
LiquidCrystal_PCF8574 lcdI2C;

// MQ135 gas sensor
//
// Datasheet can be found here: https://www.olimex.com/Products/Components/Sensors/SNS-MQ135/resources/SNS-MQ135.pdf
//
// Application
// They are used in air quality control equipments for buildings/offices, are suitable for detecting of NH3, NOx, alcohol, Benzene, smoke, CO2, etc
//
// Original creator of this library: https://github.com/GeorgK/MQ135

#define PIN_MQ135 A2
MQ135 mq135_sensor = MQ135(PIN_MQ135);
DHT dht(DHTPIN, DHTTYPE);
// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  
void setup() {
  Serial.begin(9600);
  while (!Serial) ; // wait for serial port to connect. Needed for native USB
  Serial.println("start");
  dht.begin();
  

  // initialize the lcd
  lcdI2C.begin(LCD_COLUMNS, LCD_ROWS, LCD_ADDRESS, BACKLIGHT);
}


// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.



void loop()
{
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();


  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  
  float rzero = mq135_sensor.getRZero();
  float correctedRZero = mq135_sensor.getCorrectedRZero(t, h);
  float resistance = mq135_sensor.getResistance();
  float ppm = mq135_sensor.getPPM();
  float correctedPPM = mq135_sensor.getCorrectedPPM(t, h);

  Serial.print("MQ135 RZero: ");
  Serial.print(rzero);
  Serial.print("\t Corrected RZero: ");
  Serial.print(correctedRZero);
  Serial.print("\t Resistance: ");
  Serial.print(resistance);
  Serial.print("\t PPM: ");
  Serial.print(ppm);
  Serial.print("\t Corrected PPM: ");
  Serial.print(correctedPPM);
  Serial.println("ppm CO2");
  lcdI2C.clear();                          // Clear LCD screen.
  //lcdI2C.print("");                   // Print print String to LCD on first line
  //lcdI2C.print(dht.readHumidity("%"));
  //lcdI2C.selectLine(2);                    // Set cursor at the begining of line 2
  //lcdI2C.print(F("°C "));
  //lcdI2C.print(correctedPPM);                   // Print print String to LCD on second line
  //lcdI2C.print("ppm");
  lcdI2C.print(F("H: "));
  lcdI2C.print((float)(h),0);
  lcdI2C.print(F("% T: "));
  lcdI2C.print((float)(t),1);
  lcdI2C.print(F("\337C"));
  lcdI2C.selectLine(2);
  lcdI2C.print("Gas: ");
  lcdI2C.print((float)(correctedPPM),0);                   // Print print String to LCD on second line
  lcdI2C.print(" ppm");
  if (correctedPPM > 5000)
  lcdI2C.print(" :(");
  else if (correctedPPM > 2000) // Else if puede ser problematico cuando anidan mas condiciones, usar solo if en caso de amentar
  lcdI2C.print(" :/");
  else
  lcdI2C.print(" :)");
  delay(10000);

}
