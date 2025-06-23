#include "MQTT.h"

volatile float current = 0.0;
volatile float voltage = 0.0;
volatile float power = 0.0;

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

void sendReadings() {

  // Free the heap before allocation
  ESP.getFreeHeap();
  // Allocating the heap
  DynamicJsonDocument doc(MQTT_MAX_PACKET_SIZE);
  // Free the heap after allocation
  ESP.getFreeHeap();
  JsonArray readings = doc.createNestedArray("readings");

  for(uint8_t i = 0; i < 60; i++) {
    JsonObject record = readings.createNestedObject(); 
    // Storing the data into the object
    record["id"] = MQTT_CLIENT_ID;
    record["v"] = getVoltage();
    record["i"] = getCurrent();
    record["p"] = getPower();
    delay(1000);
  }
  

  String jsonStr;
  serializeJson(doc, jsonStr);
  Serial.print("Payload size: ");
  Serial.println(jsonStr.length());
  Serial.println(jsonStr.c_str());
  
  // Publish to the broker
  MQTT_publish(MQTT__PUBLISH_TOPIC, jsonStr.c_str(), RETAINED_MESSAGE);
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

  sendReadings();
  delay(500);
  
}
