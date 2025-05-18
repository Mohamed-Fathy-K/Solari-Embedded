#include "MQTT.h"

volatile float current = 0.0;
volatile float voltage = 0.0;
volatile float power = 0.0;

char currentSetence[30] = "";
char voltageSetence[30] = "";
char powerSetence[30] = "";

float getCurrent(void) {
  static float current = 8.3;
  return (current + 0.1);
}

float getVoltage(void) {
  static float voltage = 4.2;
  return (voltage - 0.1);
}

float getPower(void) {
  return (getCurrent() * getVoltage());
}

void mqttCallback(char *topic , byte *payload, unsigned int length) {
  for(uint8_t i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
}

void setup() {
  Serial.begin(115200);
  
  if(WiFi_setup() == ES_OK 
     && MQTT_setup(MQTT_SERVER, MQTT_PORT, mqttCallback) == ES_OK) {
    Serial.println("WiFi and MQTT setup is completed successfully!");
  }
  
  if(MQTT_subscribe(MQTT_SUBSCRIBE_TOPIC, QOS0) == ES_OK) {
    Serial.println("Setup function is completed without any errors.");
  }

}

void loop() {
  MQTT_maintainConnection();

  current = getCurrent();
  voltage = getVoltage();
  power = getPower();

  sprintf(currentSetence, "current = %.2f", current);
  sprintf(voltageSetence, "voltage = %.2f", voltage);
  sprintf(powerSetence, "power = %.2f", power);

  MQTT_publish(MQTT_CURRENT_PUBLISH_TOPIC, currentSetence, RETAINED_MESSAGE);
  MQTT_publish(MQTT_VOLTAGE_PUBLISH_TOPIC, voltageSetence, RETAINED_MESSAGE);
  MQTT_publish(MQTT_POWER_PUBLISH_TOPIC, powerSetence, RETAINED_MESSAGE);

  delay(500);
  
}
