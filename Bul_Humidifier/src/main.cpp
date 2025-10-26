#include <Arduino.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <WiFi.h>
//Including MQTT protocol 
#include <PubSubClient.h>


//Pin for humidifier module
#define HUMPIN 0

//The level of humidity to  maintaine
float maintainedHumidity = 60.00; 

long lastMsg = 0;

//Connection to WiFi and Server
const char* ssid = "";
const char* password = "";
const char* mqtt_server = "192.168.1.103";

const char* topic_request = "/bul_data/humidity/request";
const char* topic_response = "/bul_data/humidity/response";


WiFiClient espClient;
PubSubClient client(espClient);

void checkingHumindityLevel(float hum)
{

  if(hum > maintainedHumidity)
  {
    digitalWrite(HUMPIN, LOW);
  }else
  {
    digitalWrite(HUMPIN, HIGH);
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  // converting payload
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print(": ");
  Serial.println(message);

  // Parsowanie JSON
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, message);

  if (error) {
    Serial.print("ERROR: Parsing JSON failed: ");
    Serial.println(error.c_str());
    return;
  }

  long timestamp = doc["timestamp"];
  float humidity = doc["humidity"];
  checkingHumindityLevel(humidity);
  Serial.print("Timestamp: ");
  Serial.println(timestamp);
  Serial.print("Humidity: ");
  Serial.println(humidity);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting with MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Connecte");
      client.subscribe(topic_response);
    } else {
      Serial.print("Error, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}
void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(HUMPIN, OUTPUT);
  
  Serial.println();
  Serial.println("Connecting with Wi-Fi...");

  WiFi.mode(WIFI_STA); 
  WiFi.setTxPower(WIFI_POWER_8_5dBm); 

  WiFi.begin(ssid, password, 0, NULL, true);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  static unsigned long lastRequest = 0;
  if (millis() - lastRequest > 10000) {
    lastRequest = millis();
    Serial.println("Sending request for data to NODE-RED");
    client.publish(topic_request, "ESP32 C3 Humidity");
  }
}
