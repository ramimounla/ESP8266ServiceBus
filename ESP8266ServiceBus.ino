#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID ""
#define STAPSK  ""
#endif

const char* ssid = STASSID;
const char* password = STAPSK;



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

  // Static IP Setup Info Here...
  WiFi.config(ip, gateway, subnet); //If you need Internet Access You should Add DNS also...
  
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

  Serial.println("HTTP server started");
}

void loop(void) {
  
}
