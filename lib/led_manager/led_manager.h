#pragma once

#include <web_utils.h>
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

    void add_handles(AsyncWebServer& server) {
      Serial.println("Adding handles for LedManager");

      // GET REQUESTS
      server.on("/api/led", HTTP_GET, [this](AsyncWebServerRequest* request) {
        if (request->hasParam("index")) {
          const auto index = request->getParam("index")->value().toInt();
          this->api_get_led(request, index);
        } else {
          this->api_get_led(request);
        }
      });

      server.on("/api/brightness", HTTP_GET, [this](AsyncWebServerRequest* request) {
        this->api_get_brightness(request);
      });

      server.on("/api/mode", HTTP_GET, [this](AsyncWebServerRequest* request) {
        this->api_get_mode(request);
      });

      // POST REQUESTS
      server.addHandler(new AsyncCallbackJsonWebHandler(
          "/api/led",
          [this](AsyncWebServerRequest* request, JsonVariant& json) {
            this->api_post_led(request, json);
          }));

      server.addHandler(new AsyncCallbackJsonWebHandler(
          "/api/leds",
          [this](AsyncWebServerRequest* request, JsonVariant& json) {
            this->api_post_leds(request, json);
          }));

      server.addHandler(new AsyncCallbackJsonWebHandler(
          "/api/brightness",
          [this](AsyncWebServerRequest* request, JsonVariant& json) {
            this->api_post_brightness(request, json);
          }));

      server.addHandler(new AsyncCallbackJsonWebHandler(
          "/api/mode",
          [this](AsyncWebServerRequest* request, JsonVariant& json) {
            this->api_post_mode(request, json);
          }));
    }

  public: // web api
    void api_get_led(AsyncWebServerRequest* request, size_t index) const {
      auto response = lw::make_ptr<AsyncJsonResponse>();
      auto&& response_json = response->getRoot().as<JsonObject>();

      if (index < NUM_LEDS) {
        const auto& led = m_leds[index];
        response_json["index"] = index;
        response_json["red"] = led.red;
        response_json["green"] = led.green;
        response_json["blue"] = led.blue;

        response->setLength();
        request->send(response.release());
      } else {
        lw::error(request, "index out of bounds");
      }
    }
 
    void api_get_led(AsyncWebServerRequest* request) const {
      auto response = lw::make_ptr<AsyncJsonResponse>(true /*is array*/);
      auto&& root = response->getRoot();

      for (size_t i = 0; i < NUM_LEDS; ++i) {
        const auto& led = m_leds[i];
        auto&& led_json = root.createNestedObject();
        led_json["index"] = i;
        led_json["red"] = led.red;
        led_json["green"] = led.green;
        led_json["blue"] = led.blue;
      }

      response->setLength();
      request->send(response.release());
    }

    void api_get_mode(AsyncWebServerRequest* request) const {
      auto response = lw::make_ptr<AsyncJsonResponse>();
      auto&& root = response->getRoot().as<JsonObject>();

      const auto& state = m_state_manager.get_state();
      root["name"] = enum_to_string(state);
      switch (state) {
        case StateManagerEnum::IDLE: {
          break;
        }
        case StateManagerEnum::RANDOM: {
          auto random_state_manager = m_state_manager.get_random_state_manager();
          root["type"] = enum_to_string(random_state_manager.get_type());
          root["delay_duration"] = random_state_manager.get_delay_duration();
          root["fade_duration"] = random_state_manager.get_fade_duration();
          break;
        }
        default: {
          lw::error(request, "Unable to get current mode");
          return;
        }
      }

      response->setLength();
      request->send(response.release());
    }

    void api_get_brightness(AsyncWebServerRequest* request) const {
      auto response = lw::make_ptr<AsyncJsonResponse>();
      auto&& root = response->getRoot().as<JsonObject>();

      root["brightness"] = m_state_manager.get_brightness();

      response->setLength();
      request->send(response.release());
    }

    void api_post_led(AsyncWebServerRequest* request, JsonVariant& json) {
      if (not json.is<JsonArray>()) {
        lw::error(request, "Expected an array");
        return;
      }
      auto&& data = json.as<JsonArray>();

      const auto current_time = millis();
      for (const auto& led_data_variant : data) {
        if (not led_data_variant.is<JsonObject>()) {
          lw::error(request, "Expected objects within the array");
          return;
        }
        auto&& led_data = led_data_variant.as<JsonObject>();

        size_t index;
        if (not lw::load_value(request, index, led_data, "index")) { return; }
        if (index >= NUM_LEDS) {
          lw::error(request, "index is too large");
          return;
        }

        millis_t delay_duration = 0;
        millis_t fade_duration = 0;
        if (not lw::load_value_if_any(request, delay_duration, led_data, "delay_duration")) { return; }
        if (not lw::load_value_if_any(request, fade_duration, led_data, "fade_duration")) { return; }

        auto color = m_leds[index];
        if (not lw::load_value_if_any(request, color.red, led_data, "red")) { return; }
        if (not lw::load_value_if_any(request, color.green, led_data, "green")) { return; }
        if (not lw::load_value_if_any(request, color.blue, led_data, "blue")) { return; }

        m_state_manager.set(
            index,
            current_time,
            delay_duration,
            fade_duration,
            color);
      }

      request->send(200);
    }

    void api_post_leds(AsyncWebServerRequest* request, JsonVariant& json) {
      if (not json.is<JsonObject>()) {
        lw::error(request, "Expected an object");
        return;
      }
      auto&& data = json.as<JsonObject>();

      millis_t delay_duration = 0;
      millis_t fade_duration = 0;
      if (not lw::load_value_if_any(request, delay_duration, data, "delay_duration")) { return; }
      if (not lw::load_value_if_any(request, fade_duration, data, "fade_duration")) { return; }

      CRGB color;
      if (not lw::load_value(request, color.red, data, "red")) { return; }
      if (not lw::load_value(request, color.green, data, "green")) { return; }
      if (not lw::load_value(request, color.blue, data, "blue")) { return; }

      m_state_manager.set(
          millis(), // current time
          delay_duration,
          fade_duration,
          color);
      request->send(200);
    }

    void api_post_mode(AsyncWebServerRequest* request, JsonVariant& json) {
      if (not json.is<JsonObject>()) {
        lw::error(request, "Expected an object");
        return;
      }
      auto&& data = json.as<JsonObject>();

      String name;
      if (not lw::load_value(request, name, data, "name")) { return; }

      if (name == "IDLE") {
        set_mode_idle(request, data);
      } else if (name == "RANDOM") {
        set_mode_random(request, data);
      } else {
        lw::error(request, "Invalid mode");
      }
    }

    void set_brightness(const millis_t current_time, const millis_t delay_duration, const millis_t fade_duration, const uint8_t brightness) {
      m_state_manager.set_brightness(current_time, delay_duration, fade_duration, brightness);
    }

    void api_post_brightness(AsyncWebServerRequest* request, JsonVariant& json) {
      if (not json.is<JsonObject>()) {
        lw::error(request, "Expected an object");
        return;
      }
      auto&& data = json.as<JsonObject>();

      uint8_t brightness;
      if (not lw::load_value(request, brightness, data, "brightness")) { return; }

      millis_t delay_duration = 0;
      millis_t fade_duration = 0;
      if (not lw::load_value_if_any(request, delay_duration, data, "delay_duration")) { return; }
      if (not lw::load_value_if_any(request, fade_duration, data, "fade_duration")) { return; }

      set_brightness(millis(), delay_duration, fade_duration, brightness);

      request->send(200);
    }

  private: // helpers

    void set_mode_idle(AsyncWebServerRequest* request, const JsonObject&) {
      m_state_manager.set_idle_state();
      request->send(200);
    }

    void set_mode_random(AsyncWebServerRequest* request, const JsonObject& data) {
      String type;
      millis_t delay_duration = 0;
      millis_t fade_duration = 0;

      if (not lw::load_value(request, type, data, "type")) { return; }
      if (not lw::load_value_if_any(request, delay_duration, data, "delay_duration")) { return; }
      if (not lw::load_value_if_any(request, fade_duration, data, "fade_duration")) { return; }

      RandomTypeEnum type_enum;
      if (not string_to_enum(type, type_enum)) {
        lw::error(request, "Invalid type for random mode");
        return;
      }

      m_state_manager.set_random_state(
          type_enum,
          delay_duration,
          fade_duration);
      request->send(200);
    }

  private: // members
    array_t<CRGB, NUM_LEDS> m_leds;
    StateManager<NUM_LEDS> m_state_manager;
};
