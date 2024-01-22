#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Définition des pins
#define SENSOR 33  // Assurez-vous que c'est le pin correct pour le DHT
#define LED 26

#define DHTPIN SENSOR // Utiliser le pin défini pour le capteur
#define DHTTYPE DHT11 // ou DHT22 ou DHT21 selon votre capteur

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  dht.begin();

  // Récupérer les détails du capteur pour obtenir le min_delay
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
}

void loop() {
  digitalWrite(LED, HIGH); // Allume le LED lors de la lecture des données

  // Délai entre les mesures
  delay(delayMS);

  // Lecture de la température
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (!isnan(event.temperature)) {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }

  // Lecture de l'humidité
  dht.humidity().getEvent(&event);
  if (!isnan(event.relative_humidity)) {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }

  digitalWrite(LED, LOW); // Éteint le LED après la lecture
  delay(5000 - delayMS); // Attendre un total de 5 secondes avant la prochaine mesure
}
