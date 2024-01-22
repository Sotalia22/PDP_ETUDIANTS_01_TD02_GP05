#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define SENSOR 33  
#define LED 26

#define DHTPIN SENSOR 
#define DHTTYPE DHT11 

DHT_Unified dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  dht.begin();

  digitalWrite(LED, HIGH); // Allume la LED lors de la lecture des données
  
  // Température
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (!isnan(event.temperature)) {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }

  // Humidité
  dht.humidity().getEvent(&event);
  if (!isnan(event.relative_humidity)) {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }

  digitalWrite(LED, LOW); // Éteint le LED après la lecture
  
  // Mode Deep Sleep pour 5 secondes
  esp_sleep_enable_timer_wakeup(5000000);
  esp_deep_sleep_start();
}

void loop() {
  
}
