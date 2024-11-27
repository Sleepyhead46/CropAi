#include "DHT.h"
#define DHTPIN 2

#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
#include <Arduino.h>

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 3, TXPin = 4;
static const uint32_t GPSBaud = 9600;
#include <ArduinoJson.h>

TinyGPSPlus gps;

SoftwareSerial ss(TXPin, RXPin);

int pHSense = A0;
int samples = 10;
float adc_resolution = 1024.0;

void setup() {

  Serial.begin(9600);
  dht.begin();

  {
    Serial.begin(9600);
    // delay(100);
}

  Serial.begin(9600);
  ss.begin(GPSBaud);

}


void loop() {
  // wait a few seconds between measurements.
  // delay(2000);
  // read humidity
  float humi  = dht.readHumidity();
  // read temperature as Celsius
  float tempC = dht.readTemperature();
  // check if any reads failed
  if (isnan(humi) || isnan(tempC)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    StaticJsonDocument<200> jsonDocument;
    jsonDocument["humi"] = humi;
    jsonDocument["tempC"] = tempC;

    String jsonString;
  serializeJson(jsonDocument, jsonString);

  // Send the JSON string over Serial
  Serial.println(jsonString);
  }
    delay(500); 
}
