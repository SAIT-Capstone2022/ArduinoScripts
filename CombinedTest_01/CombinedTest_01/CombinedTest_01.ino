#include <dht.h>
#include "dht.h"
#define dht_apin A0
dht DHT;

int moisturePin=1;
float temperatureVal, humidityVal, currentTemp, currentHumidity;
int moistureLevel, currentVal;

void setup() {
  Serial.begin(9600);
  delay(1500);
  pinMode(moisturePin, INPUT);
}

void loop() {
  DHT.read11(dht_apin);
  temperatureVal = DHT.temperature;
  humidityVal = DHT.humidity;
  moistureLevel = analogRead(moisturePin);

  if(humidityVal >= currentHumidity + 5 || humidityVal <= currentHumidity - 5){
    //print humidity
    humidityVal = DHT.humidity;
    Serial.print("Humidity ");
    Serial.println(humidityVal);
    currentHumidity = humidityVal;

    //print temperature
    temperatureVal = DHT.temperature;
    Serial.print("Temperature ");
    Serial.println(temperatureVal);
    currentTemp = temperatureVal;

    //print Moisture
    moistureLevel = analogRead(moisturePin);
    Serial.print(moistureLevel);
    Serial.println(",");
    currentVal = moistureLevel;

    //All printing needs to be output as JSON or BSON format
  }
  
  else if(temperatureVal >= currentTemp + 2 || temperatureVal <= currentTemp -2){
    //print humidity
    humidityVal = DHT.humidity;
    Serial.print("Humidity ");
    Serial.println(humidityVal);
    currentHumidity = humidityVal;

    //print temperature
    temperatureVal = DHT.temperature;
    Serial.print("Temperature ");
    Serial.println(temperatureVal);
    currentTemp = temperatureVal;

    //print Moisture
    moistureLevel = analogRead(moisturePin);
    Serial.print(moistureLevel);
    Serial.println(",");
    currentVal = moistureLevel;

    //All printing needs to be output as JSON or BSON format
  }
  else if (moistureLevel >= currentVal + 20 || moistureLevel <= currentVal - 20){
    //print humidity
    humidityVal = DHT.humidity;
    Serial.print("Humidity ");
    Serial.println(humidityVal);
    currentHumidity = humidityVal;

    //print temperature
    temperatureVal = DHT.temperature;
    Serial.print("Temperature ");
    Serial.println(temperatureVal);
    currentTemp = temperatureVal;

    //print Moisture
    moistureLevel = analogRead(moisturePin);
    Serial.print(moistureLevel);
    Serial.println(",");
    currentVal = moistureLevel;

    //All printing needs to be output as JSON or BSON format
  }
  
  delay(500);
}
