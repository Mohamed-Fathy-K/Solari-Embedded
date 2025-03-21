#include "MQTT.h"

/* configure the MQTT client */
WiFiClientSecure nodeClient;
PubSubClient client(nodeClient);

errorState WiFi_setup() {
  errorState errorState = ES_NOK;

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting..");
  delay(300);

  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  errorState = ES_OK;
  Serial.print("\nConnected to the IP Address: ");
  Serial.println(WiFi.localIP());

  return errorState;
}

/*******************************************************************************************/
errorState MQTT_setup(char *server, uint16_t port, void (*pf_callback) (char * , byte *, unsigned int)) {
  errorState errorState = ES_NOK;

  if(WiFi.status() == WL_CONNECTED) {
    client.setServer(server, port);
    client.setCallback(pf_callback);
    client.setKeepAlive(KEEPALIVE);

    nodeClient.setInsecure();
    
    while(!client.connected()) {
      Serial.println("Connecting to MQTT...");

      if(client.connect(MQTT_CLIENT_ID, 
                        MQTT_USER, 
                        MQTT_PASSWORD,
                        LWT_TOPIC,
                        LWT_QOS,
                        LWT_RETAINED_STATE,
                        LWT_MESSAGE,
                        PERSISTENT)) {
        errorState = ES_OK;
        Serial.println("Connected to the MQTT broker!");
      } else {
        Serial.print("Failed, state: ");
        Serial.print(client.state());
        Serial.println("Retrying in 2 sec....");
        delay(2000);
      }
    }
  }
  
  return errorState;
}

errorState MQTT_publish(const char *topic, const char * message, bool retained) {
  errorState errorState = ES_NOK;
  uint8_t success = 0;
  
  if(client.connected()) {
    if(client.publish(topic, message, retained))
      success = 1;
    errorState = ES_OK;
  }

  if(success) {
    Serial.print("Published to the topic: ");
    Serial.println(topic);
    return errorState;
  } else {
    Serial.print("Failed to publish to the topic: ");
    Serial.println(topic);
    return errorState;
  }
}

errorState MQTT_subscribe(const char *topic, uint8_t qos) {
  errorState errorState = ES_NOK;
  uint8_t success = 0;

  if(client.connected()) {
    if(client.subscribe(topic)) {
      success = 1;
      errorState = ES_OK; 
    }
  }

  if(success) {
    Serial.print("Subscribed to the topic: ");
    Serial.println(topic);
    return errorState;
  } else {
    Serial.print("Failed to subscribe to the topic: ");
    Serial.println(topic);
    return errorState;
  }
}

void MQTT_maintainConnection(void) {
  client.loop();
}
