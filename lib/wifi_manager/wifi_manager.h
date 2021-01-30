#pragma once

#include <ESP8266WiFi.h>

struct WiFiManager {
  public: // api
    void setup() const;

  private: // helper methods
    void wait_for_connection() const;
    void configure() const;
    void reconnect() const;
};
