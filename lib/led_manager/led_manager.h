#pragma once

#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>
#include <qr_util.h>


#include "state_manager.h"

template<size_t DATA_PIN, size_t NUM_LEDS>
struct LedManager {
  public: // ctors
    LedManager() : m_leds(), m_state_manager(m_leds) {}

  public: // api
    void setup() {
      Serial.printf("LED manager loading with %d leds and data pin %d\n", NUM_LEDS, DATA_PIN);
      FastLED.addLeds<NEOPIXEL, DATA_PIN>(m_leds, NUM_LEDS);
    }

    void loop() {
      m_state_manager.update();
      FastLED.show();
    }

  public: // web api
    void add_handles(AsyncWebServer& server) {
      Serial.println("Adding handles for LedManager");

      AsyncCallbackJsonWebHandler* handler = new AsyncCallbackJsonWebHandler(
          "",
          [](AsyncWebServerRequest *request, JsonVariant &json) {
            if (request)
            JsonObject& jsonObj = json.as<JsonObject>();
            //Check if GET parameter exists
            if(request->hasParam("download"))
            {
              AsyncWebParameter* p = request->getParam("download");
              p.name()
              p.value() 
            }
            // ...
          });

      server.addHandler(handler);
    }

  private: // members
    array_t<CRGB, NUM_LEDS> m_leds;
    StateManager<NUM_LEDS> m_state_manager;
};
