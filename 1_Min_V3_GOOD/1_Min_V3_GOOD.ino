//libraries that make this code work
#include <dht.h>
#include "dht.h"
#include <ArduinoJson.h>
#include <RTClib.h>
#define dht_apin A0
#include <Math.h>
float temperatureVal, humidityVal, currentTemp, currentHumidity, moistPercentFloat;
int moistureLevel, currentMoisture, moistPercentInt;

//object declarations
dht DHT;
RTC_DS1307 rtc;
StaticJsonDocument<200> doc;

//global variables used throughout the program
int moisturePin = 1;
bool runOnce = false;
String tempAlert = "tempHigh";
String waterAlert = "waterLow";
String dayOfWeek = "";
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
  
  //Clock Functions
  DateTime now = rtc.now();
  char buf2[] = "YYMMDD-hh:mm:ss";
  char yearBuf[] = "YY";
  char monthBuf[] = "MM";
  char dayBuf[] = "DD";
  char hourBuf[] = "hh";
  char minBuf[] = "mm";
  char secBuf[] = "ss";
  
  //Convert analog input to relative %
  moistPercentFloat = (moistureLevel / 400.0) * 100.0;
  moistPercentFloat = floor(moistPercentFloat);
  
  //check if the moisture is too low, and populate an alert if it is
  if (moistPercentFloat < 20) {
    temperatureVal = DHT.temperature;
    doc["temp"] = temperatureVal;
    humidityVal = DHT.humidity;
    doc["humidity"] = humidityVal;
    doc["moisture"] = moistPercentFloat;
    doc["year"] = (now.toString(yearBuf));
    doc["month"] = (now.toString(monthBuf));
    doc["day"] = (now.toString(dayBuf));
    doc["hour"] = (now.toString(hourBuf));
    doc["minutes"] = (now.toString(minBuf));
    doc["seconds"] = (now.toString(secBuf));
    doc["alert"] = waterAlert;
    doc["email"] = userEmail;

    serializeJson(doc, Serial);
    Serial.println();
  }
  //check if the temp is too high, and alert if it is
  else if (temperatureVal > 40) {
    temperatureVal = DHT.temperature;
    doc["temp"] = temperatureVal;
    humidityVal = DHT.humidity;
    doc["humidity"] = humidityVal;
    doc["moisture"] = moistPercentFloat;
    doc["year"] = (now.toString(yearBuf));
    doc["month"] = (now.toString(monthBuf));
    doc["day"] = (now.toString(dayBuf));
    doc["hour"] = (now.toString(hourBuf));
    doc["minutes"] = (now.toString(minBuf));
    doc["seconds"] = (now.toString(secBuf));
    doc["alert"] = tempAlert;
    doc["email"] = userEmail;

    serializeJson(doc, Serial);
    Serial.println();
  }
  //print values with no alerts
  else {
    temperatureVal = DHT.temperature;
    doc["temp"] = temperatureVal;
    humidityVal = DHT.humidity;
    doc["humidity"] = humidityVal;
    doc["moisture"] = moistPercentFloat;
    doc["year"] = (now.toString(yearBuf));
    doc["month"] = (now.toString(monthBuf));
    doc["day"] = (now.toString(dayBuf));
    doc["hour"] = (now.toString(hourBuf));
    doc["minutes"] = (now.toString(minBuf));
    doc["seconds"] = (now.toString(secBuf));
    doc["email"] = userEmail;

    serializeJson(doc, Serial);
    Serial.println();
  }

  //wait one min before running again
  delay(60000);
}
