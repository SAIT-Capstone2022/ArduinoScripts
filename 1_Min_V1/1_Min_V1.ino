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
float temperatureVal, humidityVal, currentTemp, currentHumidity, moistPercentFloat;
int moistureLevel, currentMoisture;
bool runOnce = false;
String tempAlert = "tempHigh";
String waterAlert = "waterLow";
//needs to be changed for each user 
String userEmail = "email";
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

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1);
  }
  //initialize real time clock to PC's date and time
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  //gather initial values
  DHT.read11(dht_apin);
  temperatureVal = DHT.temperature;
  humidityVal = DHT.humidity;
  moistureLevel = analogRead(moisturePin);
  DateTime now = rtc.now();
  moistPercentFloat = (moistureLevel / 400) * 100;
  moistPercentInt = round(moistPercentFloat);

  //store readings for comparison
  while (!runOnce) {
    currentTemp = temperatureVal;
    currentHumidity = humidityVal;
    currentMoisture = (moistureLevel / 400) * 100;
    runOnce = true;
  }
  //check if the moisture is too low, and populate an alert if it is
  if(moistPercentFloat < 20){
  temperatureVal = DHT.temperature;
  doc["temp"] = temperatureVal;
  humidityVal = DHT.humidity;
  doc["humidity"] = humidityVal;
  currentMoisture = moistureLevel;
  doc["moisture"] = moistureLevel;
  doc["day"] = (now.day(), DEC);
  doc["hour"] = (now.hour(), DEC);
  doc["alert"] = waterAlert;
  doc["email"] = userEmail;
  
  serializeJson(doc, Serial);
  }
  //check if the temp is too high, and alert if it is
  if(temperatureVal > 40){
  temperatureVal = DHT.temperature;
  doc["temp"] = temperatureVal;
  humidityVal = DHT.humidity;
  doc["humidity"] = humidityVal;
  currentMoisture = moistureLevel;
  doc["moisture"] = moistureLevel;
  doc["day"] = (now.day(), DEC);
  doc["hour"] = (now.hour(), DEC);
  doc["alert"] = tempAlert;
  doc["email"] = userEmail;
  
  serializeJson(doc, Serial);
  }
  //print values with no alerts
  temperatureVal = DHT.temperature;
  doc["temp"] = temperatureVal;
  humidityVal = DHT.humidity;
  doc["humidity"] = humidityVal;
  currentMoisture = moistureLevel;
  doc["moisture"] = moistureLevel;
  doc["day"] = (now.day(), DEC);
  doc["hour"] = (now.hour(), DEC);
  doc["email"] = userEmail;
  serializeJson(doc, Serial);

  //wait one min before running again
  delay(60000);
}
