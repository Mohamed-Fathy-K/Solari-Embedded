#ifndef MQTT_H_
#define MQTT_H_

#include "ERROR_STATE.h"
#include <stdint.h>

/* WiFi Macros*/
#define ESP8266_BOARD 0
#define ESP32_BOARD 1
#define ESP_BOARD ESP8266_BOARD

#if ESP_BOARD == ESP8266_BOARD
  #include <ESP8266WiFi.h>
#elif ESP_BOARD == ESP32_BOARD
  #include <WiFi.h>
#endif

#define WIFI_SSID "Gewana"
#define WIFI_PASSWORD "171823_Abeer"


/* MQTT Macros*/
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

#define MQTT_SERVER "7ecb7163642946fe9098e05b57857ef6.s1.eu.hivemq.cloud"
#define MQTT_PORT 8883
#define MQTT_USER "hivemq.webclient.1742559886790"
#define MQTT_PASSWORD ":E4;2?.0Dc6GBAbsCkar"
#define MQTT_PUBLISH_TOPIC "node/solari"
#define MQTT_SUBSCRIBE_TOPIC "web/solari"
#define MQTT_CLIENT_ID "Solari2025"

#define QOS0 0
#define QOS1 1
#define QOS2 2
#define QOS QOS0

/* persistent session 
 *  for persistent session --> false
 *  for clean session --> true
 */
#define PERSISTENT false
/*
 * keepAlive value is in the range of 60s : 64800s (18h)
 */
#define KEEPALIVE 120
/*
 * retained message
 * for retained messages --> true
 * for normal message --> false
 */
#define RETAINED_MESSAGE false
 
#define LWT_TOPIC "node/solari"
#define LWT_MESSAGE "Solari is disconnected"
#define LWT_QOS QOS0
#define LWT_RETAINED_STATE true

/* WiFi Functions*/
errorState WiFi_setup();
/* MQTT Functions*/
errorState MQTT_setup(char *server, uint16_t port, void (*pf_callback) (char * , byte *, unsigned int));
errorState MQTT_publish(const char *topic, const char * message, bool retained);
errorState MQTT_subscribe(const char *topic, uint8_t qos); 
void MQTT_maintainConnection(void);
#endif /* MQTT_H_ */
