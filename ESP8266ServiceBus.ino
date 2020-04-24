#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

#ifndef STASSID
#define STASSID ""
#define STAPSK  ""
#endif

const char* ssid = STASSID;
const char* password = STAPSK;


/* MQTT Credentials */
#define MQTT_USERNAME "YOUR_MAQIATTO_USERNAME"
#define MQTT_KEY      "YOUR_MAQIATTO_PASS"
#define MQTT_TOPIC    "YOUR_MAQIATTO_TEST_TOPIC"

const char* mqttServer = "maqiatto.com";
const int mqttPort = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";
const char* mqttTopic = "";

WiFiClient espClient;
PubSubClient client(espClient);

void handleRoot() {
  digitalWrite(LED_BUILTIN, 0);
  digitalWrite(LED_BUILTIN, 1);
}

void switchOn() {
  digitalWrite(LED_BUILTIN, 0);
}

void switchOff() {
  digitalWrite(LED_BUILTIN, 1);
}

void handleNotFound() {
  digitalWrite(LED_BUILTIN, 0);
  
  digitalWrite(LED_BUILTIN, 1);
}

void setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 1);
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  WiFi.hostname("ledhost"); //set hostname
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  
   while (!client.connected()) {
      Serial.println("Connecting to MQTT...");
      if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
        Serial.println("connected"); 
      } else {
        Serial.print("failed with state ");
        Serial.print(client.state());
        delay(2000);
      }
   }

   client.subscribe(mqttTopic);
}

void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}
 
void loop() {
  client.loop();
}
