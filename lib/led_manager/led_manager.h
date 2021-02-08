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
      FastLED.setBrightness(100);
      FastLED.addLeds<NEOPIXEL, DATA_PIN>(m_leds, NUM_LEDS);
    }

    void loop() {
      m_state_manager.update();
      FastLED.show();
    }

    void add_handles(AsyncWebServer& server) {
      Serial.println("Adding handles for LedManager");

      // POST REQUESTS
      server.addHandler(new AsyncCallbackJsonWebHandler(
          "/api/led",
          [this](AsyncWebServerRequest *request, JsonVariant &json) {
            this->api_post_led(request, json);
          }));

      server.addHandler(new AsyncCallbackJsonWebHandler(
          "/api/leds",
          [this](AsyncWebServerRequest *request, JsonVariant &json) {
            this->api_post_leds(request, json);
          }));

      server.addHandler(new AsyncCallbackJsonWebHandler(
          "/api/brightness",
          [this](AsyncWebServerRequest *request, JsonVariant &json) {
            this->api_post_brightness(request, json);
          }));

      server.addHandler(new AsyncCallbackJsonWebHandler(
          "/api/mode",
          [this](AsyncWebServerRequest *request, JsonVariant &json) {
            this->api_post_mode(request, json);
          }));

      // GET REQUESTS
      server.on("/api/led", HTTP_GET, [this](AsyncWebServerRequest* request) {
        if (request->hasParam("index")) {
          const auto index = request->getParam("index")->value().toInt();
          this->api_get_led(request, index);
        } else {
          this->api_get_led(request);
        }
      });

      server.on("/api/mode", HTTP_GET, [this](AsyncWebServerRequest* request) {
        this->api_get_mode(request);
      });
    }

  public: // web api

    void api_get_led(AsyncWebServerRequest* request, size_t index) {
      auto response = new AsyncJsonResponse();
      auto&& response_json = response->getRoot().as<JsonObject>();

      if (index < NUM_LEDS) {
        const auto& led = m_leds[index];
        response_json["index"] = index;
        response_json["red"] = led.red;
        response_json["green"] = led.green;
        response_json["blue"] = led.blue;

        response->setLength();
        request->send(response);
      } else {
        error(request, "index out of bounds");
        delete response; 
      }
    }
 
    void api_get_led(AsyncWebServerRequest* request) {
      auto response = new AsyncJsonResponse(true /*is array*/);
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
      request->send(response);
    }

    void api_get_mode(AsyncWebServerRequest* request) {
      auto response = new AsyncJsonResponse();
      auto&& root = response->getRoot().as<JsonObject>();

      const auto& state = m_state_manager.get_state();
      switch (state) {
        case StateManagerEnum::IDLE:
        {
          root["type"] = "IDLE";
          break;
        }
        case StateManagerEnum::UNIFORM_RANDOM:
        case StateManagerEnum::EACH_RANDOM:
        {
          root["type"] = "RANDOM";
          // TODO: Build out the random framework
          // max_brightness: max_brightness,
          // delay_duration: delay_duration,
          // fade_duration: fade_duration,
          break;
        }
        default:
        {
          error(request, "Unable to get current mode");
          delete response;
          return;
        }
      }

      response->setLength();
      request->send(response);
    }

    void api_post_led(AsyncWebServerRequest* request, JsonVariant& json) {
      if (not json.is<JsonArray>()) {
        error(request, "Expected an array");
        return;
      }

      const auto current_time = millis();

      const auto& data = json.as<JsonArray>();
      for (const auto& led_data_variant : data) {
        if (not led_data_variant.is<JsonObject>()) {
          error(request, "Expected objects within the array");
          return;
        }
        const auto& led_data = led_data_variant.as<JsonObject>();

        // Get index
        if (not led_data.containsKey("index")) {
          error(request, "index is required for each array entry");
          return;
        } else if (not led_data["index"].is<size_t>()) {
          error(request, "invalid value for index");
          return;
        }
        const auto index = led_data["index"].as<size_t>();
        if (index >= NUM_LEDS) {
          error(request, "index is too large");
          return;
        }

        // Get delay and fade
        millis_t delay_duration = 0;
        millis_t fade_duration = 0;

        if (led_data.containsKey("delay_duration")) {
          if (not led_data["delay_duration"].is<millis_t>()) {
            error(request, "Invalid value for delay_duration");
            return;
          }

          delay_duration = led_data["delay_duration"].as<millis_t>();
        }
        if (led_data.containsKey("fade_duration")) {
          if (not led_data["fade_duration"].is<millis_t>()) {
            error(request, "Invalid value for fade_duration");
            return;
          }

          fade_duration = led_data["fade_duration"].as<millis_t>();
        }

        // Update colors
        const auto& led = m_leds[index];
        auto red = led.r;
        auto green = led.g;
        auto blue = led.b;
        if (led_data.containsKey("red")) {
          if (not led_data["red"].is<uint8_t>()) {
            error(request, "Invalid value for red");
            return;
          }

          red = led_data["red"].as<uint8_t>();
        }
        if (led_data.containsKey("green")) {
          if (not led_data["green"].is<uint8_t>()) {
            error(request, "Invalid value for green");
            return;
          }

          green = led_data["green"].as<uint8_t>();
        }
        if (led_data.containsKey("blue")) {
          if (not led_data["blue"].is<uint8_t>()) {
            error(request, "Invalid value for blue");
            return;
          }

          blue = led_data["blue"].as<uint8_t>();
        }
        m_state_manager.set(
            index,
            current_time,
            delay_duration,
            fade_duration,
            red, green, blue);
      }

      request->send(200);
    }

    void api_post_leds(AsyncWebServerRequest* request, JsonVariant& json) {
      if (not json.is<JsonObject>()) {
        error(request, "Expected an object");
        return;
      }

      const auto& data = json.as<JsonObject>();

      const auto current_time = millis();
      // Get delay and fade
      millis_t delay_duration = 0;
      millis_t fade_duration = 0;

      if (data.containsKey("delay_duration")) {
        if (not data["delay_duration"].is<millis_t>()) {
          error(request, "Invalid value for delay_duration");
          return;
        }

        delay_duration = data["delay_duration"].as<millis_t>();
      }
      if (data.containsKey("fade_duration")) {
        if (not data["fade_duration"].is<millis_t>()) {
          error(request, "Invalid value for fade_duration");
          return;
        }

        fade_duration = data["fade_duration"].as<millis_t>();
      }

      if (not data.containsKey("red")) {
        error(request, "red is required");
        return;
      } else if (not data["red"].is<uint8_t>()) {
        error(request, "Invalid value for red");
        return;
      }
      const auto red = data["red"].as<uint8_t>();

      if (not data.containsKey("green")) {
        error(request, "green is required");
        return;
      } else if (not data["green"].is<uint8_t>()) {
        error(request, "Invalid value for green");
        return;
      }
      const auto green = data["green"].as<uint8_t>();

      if (not data.containsKey("blue")) {
        error(request, "blue is required");
        return;
      } else if (not data["blue"].is<uint8_t>()) {
        error(request, "Invalid value for blue");
        return;
      }
      const auto blue = data["blue"].as<uint8_t>();

      m_state_manager.set(
          current_time,
          delay_duration,
          fade_duration,
          red, green, blue);
      request->send(200);
    }

    void api_post_mode(AsyncWebServerRequest* request, JsonVariant& json) {
      if (not json.is<JsonObject>()) {
        error(request, "Expected an object");
        return;
      }

      const auto& data = json.as<JsonObject>();

      if (not data.containsKey("name")) {
        error(request, "name is required");
        return;
      } else if (not data["name"].is<String>()) {
        error(request, "Invalid value for name");
        return;
      }

      const auto name = data["name"].as<String>();
      if (name == "IDLE") {
        set_mode_idle(request, data);
      } else if (name == "RANDOM") {
        set_mode_random(request, data);
      } else {
        error(request, "Invalid mode");
        return;
      }
    }

    void api_post_brightness(AsyncWebServerRequest* request, JsonVariant& json) {
      if (not json.is<JsonObject>()) {
        error(request, "Expected an object");
        return;
      }

      const auto& data = json.as<JsonObject>();

      if (not data.containsKey("brightness")) {
        error(request, "brightness is required");
        return;
      } else if (not data["brightness"].is<uint8_t>()) {
        error(request, "Invalid value for brightness");
        return;
      }

      const auto brightness = data["brightness"].as<uint8_t>();
      FastLED.setBrightness(brightness);

      request->send(200);
    }

  private: // helpers

    void set_mode_idle(AsyncWebServerRequest* request, const JsonObject&) {
      m_state_manager.set_idle_state();
      request->send(200);
    }

    void set_mode_random(AsyncWebServerRequest* request, const JsonObject& data) {
      if (not data.containsKey("type")) {
        error(request, "type is required");
        return;
      } else if (not data["type"].is<String>()) {
        error(request, "Invalid value for type");
        return;
      }
      auto&& type = data["type"].as<String>();

      // Get delay and fade
      millis_t delay_duration = 0;
      millis_t fade_duration = 0;

      if (data.containsKey("delay_duration")) {
        if (not data["delay_duration"].is<millis_t>()) {
          error(request, "Invalid value for delay_duration");
          return;
        }

        delay_duration = data["delay_duration"].as<millis_t>();
      }
      if (data.containsKey("fade_duration")) {
        if (not data["fade_duration"].is<millis_t>()) {
          error(request, "Invalid value for fade_duration");
          return;
        }

        fade_duration = data["fade_duration"].as<millis_t>();
      }

      // TODO: match apis and add brightness
      if (type == "UNIFORM") {
        m_state_manager.start_uniform_random_fade_loop(
            delay_duration,
            fade_duration);
      } else if (type == "INDIVIDUAL") {
        m_state_manager.start_each_random_fade_loop(
            delay_duration,
            fade_duration);
      } else {
        error(request, "Invalid type for random mode");
        return;
      }
      request->send(200);
    }

    template<typename msg_t>
    void error(AsyncWebServerRequest* request, msg_t&& msg) const {
      // TODO: Support error codes
      request->send(400, "text/plain", std::forward<msg_t>(msg));
    }

  private: // members
    array_t<CRGB, NUM_LEDS> m_leds;
    StateManager<NUM_LEDS> m_state_manager;
};
