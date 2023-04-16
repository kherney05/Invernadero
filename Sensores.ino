
#include "Sensores.h"
#include "DHT.h"


void readLight() {
  lightValue = analogRead(lightPin);
  Serial.print(F("Luz: "));
  Serial.println(lightValue);
}

void readHumeFloor() {
  humeFloor = analogRead(humeFloorPin);
  Serial.print(F("Humidity floor: "));
  Serial.println(humeFloor);
}
void readTemp() {
  Serial.print(millis());
  // Wait a few seconds between measurements.
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  hume = dht.readHumidity();
  // Read temperature as Celsius (the default)
  temp = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(hume) || isnan(temp) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, hume);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(temp, hume, false);

  Serial.print(F("\nHumidity: "));
  Serial.print(hume);
  Serial.print(F("%  \nTemperature: "));
  Serial.print(temp);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  \nHeat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}
