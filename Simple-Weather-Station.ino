/*
Simple Weather Station
*/
#include "DHT.h"

#define PIN 5     // Digital pin connected to the DHT sensor

DHT dht(PIN, DHT11);

void setup() {
  Serial.begin(9600);
  Serial.println(F("Simple Weather Station"));

// prepare sensor
  dht.begin();
}

void loop() {
  
  float humidity = dht.readHumidity();
  
  // Read and calculate values
  float celcius = dht.readTemperature();
  float hic = dht.computeHeatIndex(celcius, humidity, false);
  float fahrenheit = dht.readTemperature(true);
  float hif = dht.computeHeatIndex(fahrenheit, humidity);
 
  // continue on failure.
  if (isnan(humidity) || isnan(celcius) || isnan(fahrenheit)) {
    Serial.println("failure on read, continue, and try again.");
    delay(500);
    return;
  }

  // output values to serial port
  Serial.println(" Humidity: " + String(humidity));
  Serial.println("F: " + String(hif));
  Serial.println("C: " + String(hic));
  Serial.println("");

  // delay read, some reading take up to 250ms
  delay(2500);
}
