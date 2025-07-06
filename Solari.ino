#include "MQTT.h"
#include "CurrentSensor.h"
#include "voltageSensor.h"
#define "ultrasonic.h"

#define VOLTAGE1_PIN   14 
#define VOLTAGE2_PIN   27 
volatile float current_value = 0;
volatile float voltage1_value = 0;
volatile float voltage2_value = 0;

volatile uint32_t cleaning_time = 0;

float getCurrent(void) {
  if(currentMeasure(current_value) == ES_OK)
    return current_value;
}

float getVoltage(uint8_t voltage_pin) {
  if(CalculateVoltage(voltage_pin, voltage1_value) == ES_OK)
    return voltage1_value;
}

float getPower(uint8_t voltage_pin) {
  return (getCurrent() * getVoltage());
}

// receving the time of frequent cleaning
void mqttCallback(char *topic , byte *payload, unsigned int length) {
  if(length == 4) 
    cleaning_time = (((uint32_t) payload[0] << 24) | ((uint32_t) payload[1] << 16) | ((uint32_t) payload[2] << 8) | ((uint32_t) payload[3]));
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
    record["v1"] = getVoltage(VOLTAGE1_PIN);
    record["v2"] = getVoltage(VOLTAGE2_PIN);
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
  MQTT_publish(MQTT_READINGS_PUBLISH_TOPIC, jsonStr.c_str(), RETAINED_MESSAGE);
}

void sendWaterLevel(void) {
  // Free the heap before allocation
  ESP.getFreeHeap();
  // Allocating the heap
  DynamicJsonDocument tank(8);
  // Free the heap after allocation
  ESP.getFreeHeap();

  tank["percentage"] = ultrasonicGetContainerFillPercentage();
  tank["status"] = ultrasonicGetContainerFillPercentage() <= 15 ? "empty" : "good";

  String jsonStr;
  serializeJson(doc, jsonStr);
  
  MQTT_publish(MQTT_WATER_LEVEL_PUBLISH_TOPIC, jsonStr.c_str(), RETAINED_MESSAGE);
}

void sendFaults(void) {
  uint32_t fault = classifyFault(current_value, voltage1_value, voltage2_value);

  if(fault != 0)
    MQTT_publish(MQTT_FAULTS_PUBLISH_TOPIC, fault, RETAINED_MESSAGE);
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
