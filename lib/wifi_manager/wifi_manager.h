#pragma once

#ifdef ESP32
#include <WiFi.h>
//#include <AsyncTCP.h>
#else
#include <ESP8266WiFi.h>
//#include <ESPAsyncTCP.h>
#endif

struct WiFiManager {
  public: // api
    void setup() const;

  private: // helper methods
    void wait_for_connection() const;
    void configure() const;
    void reconnect() const;
};
