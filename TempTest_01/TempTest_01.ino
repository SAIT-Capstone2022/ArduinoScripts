#include "dht.h"
#define dht_apin A0
dht DHT;

void setup() {
  Serial.begin(9600);
  delay(500);
  delay(1000);


}

void loop() {
  DHT.read11(dht_apin);
  Serial.print("Humidity ");
  Serial.println(DHT.humidity);
  Serial.print("Temperature ");
  Serial.println(DHT.temperature);
  delay(5000);
}
