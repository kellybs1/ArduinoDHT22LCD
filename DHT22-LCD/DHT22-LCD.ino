//using Adafruit DHT sensor library
//https://github.com/adafruit/DHT-sensor-library
#include <DHT.h>
#include <DHT_U.h>

#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);


//set the data pin
#define DHTPIN 8

//set the DHT type 
#define DHTTYPE DHT22 

//set up variables
float humidity;
float tempC;
int msUpdateDelay = 2000; //millisecond delay between updates

//instantiate dht
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  //starting:
    //serial
  Serial.begin(9600);
    //LCD
  lcd.begin(16, 2);
  lcd.clear();
    //humidity/temp sensor
  dht.begin();
}


void loop()
{
  readSensor();
  outPutSerial();
  outPutLCD();
  delay(msUpdateDelay);
}

//gets values from sensor
void readSensor()
{
  //save current values values before updating, for later use
  float prevHumidity = humidity;
  float prevTempC = tempC;
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  tempC = dht.readTemperature();
  // if reading fails set to previous readings
  if (isnan(humidity) || isnan(tempC)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    humidity = prevHumidity;
    tempC = prevTempC;
  }
}

//write values to lcd
void outPutLCD()
{
  //top line (note the set cursor values) - humidity
  lcd.setCursor(0,0); 
  lcd.print("Humid (%): ");
  lcd.print(humidity);
  //botom line - temperature
  lcd.setCursor(0,1);
  lcd.print("Temp  (C): ");
  lcd.print(tempC);
}

//writes values to serial for debugging
void outPutSerial()
{
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.println("C");
}
