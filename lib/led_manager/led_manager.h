#pragma once

#include <ESPAsyncWebServer.h>

struct LedManager {
  void setup() {
    Serial.println("LED Manager loaded");
  }

  void add_handles(AsyncWebServer&) {
    Serial.println("Adding handles for LedManager");
  }
};
