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
int moistureLevel, currentMoisture, moistPercentInt;
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
  //DateTime now = rtc.now();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  //gather initial values
  DHT.read11(dht_apin);
  temperatureVal = DHT.temperature;
  humidityVal = DHT.humidity;
  moistureLevel = analogRead(moisturePin);
  DateTime now = rtc.now();
  char buf2[] = "YYMMDD-hh:mm:ss";
  char yearBuf[] = "YY";
  char monthBuf[] = "MM";
  char dayBuf[] = "DD";
  char hourBuf[] = "hh";
  char minBuf[] = "mm";
  char secBuf[] = "ss";
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
  if (moistPercentInt < 20) {
    temperatureVal = DHT.temperature;
    doc["temp"] = temperatureVal;
    humidityVal = DHT.humidity;
    doc["humidity"] = humidityVal;
    moistureLevel = analogRead(moisturePin);
    moistPercentFloat = (moistureLevel / 400) * 100;
    moistPercentInt = round(moistPercentFloat);
    doc["moisture"] = moistPercentInt;
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
    Serial.println(now.toString(buf2));
    //Serial.println(now.year(), DEC);
    //Serial.println(now.day(), DEC);
    //Serial.println(now.hour(), DEC);
    //Serial.println(now.second(), DEC);
  }
  //check if the temp is too high, and alert if it is
  else if (temperatureVal > 40) {
    temperatureVal = DHT.temperature;
    doc["temp"] = temperatureVal;
    humidityVal = DHT.humidity;
    doc["humidity"] = humidityVal;
    currentMoisture = moistureLevel;
    doc["moisture"] = moistPercentInt;
    //DateTime now = rtc.now();
    doc["year"] = (now.year(), DEC);
    doc["day"] = (now.day(), DEC);
    doc["hour"] = (now.hour(), DEC);
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
    currentMoisture = moistureLevel;
    doc["moisture"] = moistPercentInt;
    //DateTime now = rtc.now();
    doc["year"] = (now.year(), DEC);
    doc["day"] = (now.day(), DEC);
    doc["hour"] = (now.hour(), DEC);
    doc["email"] = userEmail;
    serializeJson(doc, Serial);
    Serial.println();
  }

  //wait one min before running again
  delay(10000);
}
