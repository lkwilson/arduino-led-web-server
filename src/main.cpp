#include <wifi_manager.h>
#include <web_server_manager.h>
#include <led_manager.h>

constexpr auto SERIAL_BAUD_RATE = 115200;
constexpr auto LED_DATA_PIN = 6;
constexpr auto LED_NUM_LIGHTS = 10;

WiFiManager s_wifi_manager;
WebServerManager s_web_server_manager;
LedManager<LED_DATA_PIN, LED_NUM_LIGHTS> s_led_manager;

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

void loop() {
  s_led_manager.loop();
}
