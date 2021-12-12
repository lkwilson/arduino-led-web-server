#pragma once

#ifdef ESP32
#include <WiFi.h>
#include <ESPmDNS.h>
//#include <AsyncTCP.h>
#else
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
//#include <ESPAsyncTCP.h>
#endif

struct WiFiManager {
  public: // api
    void setup() const;
    void setup(const char* const ssid, const char* const password) const;

  private: // helper methods
    void wait_for_connection() const;
    void configure() const;
    void reconnect() const;
};
