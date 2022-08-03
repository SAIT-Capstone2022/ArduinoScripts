#include <dht.h>
#include "dht.h"
#include <ArduinoJson.h>
#define dht_apin A0
#include <Math.h>
float temperatureVal, humidityVal, currentTemp, currentHumidity, moistPercentFloat;
int moistureLevel, currentMoisture, moistPercentInt;

//object declarations
dht DHT;
StaticJsonDocument<200> doc;

//global variables used throughout the program
int moisturePin = 1;
bool runOnce = false;

//needs to be changed for each user

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) continue;
  delay(1000);
  pinMode(moisturePin, INPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  DHT.read11(dht_apin);
  temperatureVal = DHT.temperature;
  humidityVal = DHT.humidity;
  moistureLevel = analogRead(moisturePin);
  moistPercentFloat = (moistureLevel / 400.0) * 100.0;
  moistPercentFloat = floor(moistPercentFloat);

  temperatureVal = DHT.temperature;
  doc["temp"] = temperatureVal;
  humidityVal = DHT.humidity;
  doc["humidity"] = humidityVal;
  doc["moisture"] = moistPercentFloat;
  serializeJson(doc, Serial);
  Serial.println();
  delay(1000);

}
