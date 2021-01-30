#include <wifi_manager.h>
#include <web_server_manager.h>

constexpr auto serial_baud_rate = 115200;

WiFiManager s_wifi_manager;
WebServerManager s_web_server_manager;

void setup() {
  // Setup Serial
  Serial.begin(serial_baud_rate);
  Serial.println();

  // Setup WiFi
  s_wifi_manager.setup();

  // Setup Web Server
  s_web_server_manager.setup();
}

void loop() {}
