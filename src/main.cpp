#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include "env.h" // WIFI_SSID, WIFI_PASSWORD

// CONFIGURATION
constexpr auto ssid = WIFI_SSID;
constexpr auto password = WIFI_PASSWORD;
constexpr int port = 80;

// STATE
AsyncWebServer s_server(port);

// SETUP HELPERS
void setup_serial() {
  Serial.begin(115200);
}

void setup_wifi() {
  Serial.printf("Connecting to %s\n", ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup_web_server() {
  s_server.begin();
}

// HOOKS
void setup() {
  setup_serial();
  setup_wifi();
  setup_web_server();
}

void loop(){
}
