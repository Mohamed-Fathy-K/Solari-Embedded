#include "HardwareSerial.h"
#include "Temperature.h"
#include "MQTT.h"


void Temperature_PrintSystemTemp() {
  float temperature = temperatureRead();
  Serial.print("Temp = ");
  Serial.println(temperature);
}


void Temperature_SendSystemTempOverMQTT() {
  float temperature = temperatureRead();

  // Convert float to string for MQTT
  char tempStr[10];
  dtostrf(temperature, 6, 2, tempStr);

  // Publish temperature data over MQTT
  if (MQTT_publish(MQTT_PUBLISH_TOPIC, tempStr, RETAINED_MESSAGE) == ES_OK) {
    Serial.print("Published Temperature: ");
    Serial.println(tempStr);
  } else {
    Serial.println("Failed to publish temperature data.");
  }
}
