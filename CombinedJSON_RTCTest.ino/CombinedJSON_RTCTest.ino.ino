//libraries that make this code work
#include <dht.h>
#include "dht.h"
#include <ArduinoJson.h>
#include <RTClib.h>
#define dht_apin A0

//object declarations
dht DHT;
RTC_DS1307 rtc;
StaticJsonDocument<200> doc;

//global variables used throughout the program
int moisturePin = 1;
float temperatureVal, humidityVal, currentTemp, currentHumidity;
int moistureLevel, currentVal;
bool runOnce = false;
char daysOfTheWeek[7][12] = {
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday"
};

//initial setup declarations
void setup() {
  Serial.begin(9600);
  while (!Serial) continue;
  delay(1500);
  pinMode(moisturePin, INPUT);
  //initialize real time clock to PC's date and time
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  DHT.read11(dht_apin);
  temperatureVal = DHT.temperature;
  humidityVal = DHT.humidity;
  moistureLevel = analogRead(moisturePin);

  while (!runOnce) {
    currentTemp = temperatureVal;
    currentHumidity = humidityVal;
    currentVal = moistureLevel;
    runOnce = true;
  }

  if (humidityVal >= currentHumidity + 5 || humidityVal <= currentHumidity - 5) {
    //All printing needs to be output as JSON or BSON format
    temperatureVal = DHT.temperature;
    doc["temp"] = temperatureVal;
    humidityVal = DHT.humidity;
    doc["humidity"] = humidityVal;
    currentVal = moistureLevel;
    doc["moisture"] = moistureLevel;
    serializeJson(doc, Serial);
    Serial.println();
  }

  else if (temperatureVal >= currentTemp + 2 || temperatureVal <= currentTemp - 2) {
    //All printing needs to be output as JSON or BSON format
    temperatureVal = DHT.temperature;
    doc["temp"] = temperatureVal;
    humidityVal = DHT.humidity;
    doc["humidity"] = humidityVal;
    currentVal = moistureLevel;
    doc["moisture"] = moistureLevel;
    serializeJson(doc, Serial);
    Serial.println();
  }
  else if (moistureLevel >= currentVal + 20 || moistureLevel <= currentVal - 20) {
    //All printing needs to be output as JSON or BSON format
    temperatureVal = DHT.temperature;
    doc["temp"] = temperatureVal;
    humidityVal = DHT.humidity;
    doc["humidity"] = humidityVal;
    currentVal = moistureLevel;
    doc["moisture"] = moistureLevel;
    serializeJson(doc, Serial);
    Serial.println();
  }
  //ensuring the data comes through correctly
  
  DateTime now = rtc.now();
  Serial.print("Date & Time: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);
  delay(5000);
}
