#pragma once

#include <ESPAsyncWebServer.h>
#include <FastLED.h>

template<size_t DATA_PIN, size_t NUM_LEDS>
struct LedManager {
  public: // api
    void setup() {
      Serial.println("LED Manager loaded");
      FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    }

    void loop() {
      leds[0] = CRGB::White;
      FastLED.show(); 
      delay(30);

      leds[0] = CRGB::Red;
      FastLED.show(); 
      delay(30);

      leds[0] = CRGB::Green;
      FastLED.show(); 
      delay(30);

      leds[0] = CRGB::Blue;
      FastLED.show(); 
      delay(30);

      leds[0] = CRGB::Black;
      FastLED.show(); 
      delay(1000);
    }

  public: // web api
    void add_handles(AsyncWebServer&) {
      Serial.println("Adding handles for LedManager");
    }

  public: // led api

  private: // members
    CRGB leds[NUM_LEDS];
};
