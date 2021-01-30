#include <wifi_manager.h>
#include <web_server_manager.h>
#include <led_manager.h>

constexpr auto SERIAL_BAUD_RATE = 115200;

WiFiManager s_wifi_manager;
WebServerManager s_web_server_manager;
LedManager s_led_manager;

void setup() {
  // Setup Serial
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println();

  // Setup WiFi
  s_wifi_manager.setup();

  // Setup Managers
  s_led_manager.setup();

  // Setup Web Server
  s_web_server_manager.setup(s_led_manager);
}

void loop() {}
