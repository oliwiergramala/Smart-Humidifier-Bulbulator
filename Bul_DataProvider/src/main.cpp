#include <Arduino.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <PubSubClient.h>
#include <WiFi.h>

//DataProvider

//DHT11
#include <dht11.h>
#define DHT11PIN 0
dht11 DHT11;


//Connection
const char* ssid = "";
const char* password = "";
const char* mqtt_server = "192.168.1.103";

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
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
}


void reconnect()
{
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    String clientId = "ESP32-C3 DataProvider";
    clientId += String(random(0xffff), HEX);
    
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  StaticJsonDocument<32> doc;
  char output[32];

  long now = millis();
  if (now - lastMsg > 10000) {
    lastMsg = now;
    int chk = DHT11.read(DHT11PIN);
    doc["t"] = (float)DHT11.temperature;
    doc["h"] = (float)DHT11.humidity;
    serializeJson(doc, output);
    Serial.println(output);
    client.publish("/home/sensors", output);
  }
}
