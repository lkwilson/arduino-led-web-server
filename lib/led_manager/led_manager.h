#pragma once

// TODO: change ! to not

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

    void add_handles(AsyncWebServer& server) {
      Serial.println("Adding handles for LedManager");

      server.on("/api/led", HTTP_GET, [this](AsyncWebServerRequest* request) {
        if (request.hasParam("index")) {
          const auto& index_param = request.getParam("index");
          // TODO: add error checking
          const auto index = index_param.value().toInt();
          this->api_get_led(request, index);
        } else {
          this->api_get_led(request, );
        }
      });

      server.on("/api/mode", HTTP_GET, [this](AsyncWebServerRequest* request) {
        this->api_get_mode(request);
      });

      server.on("/api/led", HTTP_POST, [this](AsyncWebServerRequest* request) {
        this->api_post_led(request);
      });

      server.on("/api/leds", HTTP_POST, [this](AsyncWebServerRequest* request) {
        this->api_post_leds(request);
      });

      server.on("/api/mode", HTTP_POST, [this](AsyncWebServerRequest* request) {
        this->api_post_mode(request);
      });

      // TODO: this apparently doesn't catch GET requests, so I should be safe
      // to put this above the get requests.
      // TODO: this also catches PUT and PATCH as well, but that's not a big
      // deal.
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
          "/api/mode",
          [this](AsyncWebServerRequest *request, JsonVariant &json) {
            this->api_post_mode(request, json);
          }));
    }


  public: // web api

    void api_get_led(AsyncWebServerRequest* request, size_t index) {
      auto response = new AsyncJsonResponse();
      JsonObject& root = response->getRoot();

      if (index < NUM_LEDS) {
        const auto& led = m_leds[index];
        root["index"] = index;
        root["red"] = led.red;
        root["green"] = led.green;
        root["blue"] = led.blue;

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
      auto&& root = response->getRoot();
      // TODO: Do I need to cast it?
      //auto&& root = response->getRoot().as<JsonObject>();

      switch (state) {
        case IDLE:
        {
          root["type"] = "IDLE";
          break;
        }
        case RANDOM:
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
          error(request, "Unable to get state");
          delete response;
          return;
        }
      }

      response->setLength();
      request->send(response);
    }

    void api_post_led(AsyncWebServerRequest* request, JsonVariant& json) {
      if (!json.is<JsonArray>()) {
        error(request, "Expected an array");
        return;
      }

      const auto current_time = millis();

      auto&& data = json.as<JsonArray>();
      for (auto&& led_data_variant : data) {
        if (!led_data_variant.is<JsonObject>()) {
          error(request, "Expected objects in the array");
          return;
        }
        const auto& led_data = led_data_variant.as<JsonObject>();

        // Get index
        if (!led_data.containsKey("index")) {
          error(request, "index must be specified");
          return;
        } else if (!led_data["index"].is<int>()) {
          error(request, "index should be a number");
          return;
        }
        const auto index = convert_to_index(led_data["index"].as<int>());
        if (index >= NUM_LEDS) {
          error(request, "An LED index was out of range");
          return;
        }

        // Get delay and fade
        millis_t delay_duration = 0;
        millis_t fade_duration = 0;

        if (led_data.containsKey("delay_duration")) {
          if (!led_data["delay_duration"].is<int>()) {
            error(request, "delay_duration should be a number");
            return;
          }

          delay_duration = convert_to_time_value(led_data["delay_duration"].as<int>());
        }
        if (led_data.containsKey("fade_duration")) {
          if (!led_data["fade_duration"].is<int>()) {
            error(request, "fade_duration should be a number");
            return;
          }

          fade_duration = convert_to_time_value(led_data["fade_duration"].as<int>());
        }

        // Update colors
        const auto& led = m_leds[index];
        auto red = led.r;
        auto green = led.g;
        auto blue = led.b;
        if (led_data.containsKey("red")) {
          if (!led_data["red"].is<int>()) {
            error(request, "red should be a number")
          }

          red = convert_to_color_value(led_data["red"].as<int>());
        }
        if (led.containsKey("green")) {
          if (!led["green"].is<int>()) {
            error(request, "green should be a number")
          }

          green = convert_to_color_value(led["green"].as<int>());
        }
        if (led.containsKey("blue")) {
          if (!led["blue"].is<int>()) {
            error(request, "blue should be a number")
          }

          blue = convert_to_color_value(led["blue"].as<int>());
        }
        m_state_manager.set(
            index
            current_time,
            delay_duration,
            fade_duration,
            red, green, blue);
      }

      request->send(200);
    }

    void api_post_leds(AsyncWebServerRequest* request, JsonVariant& json) {
      if (!json.is<JsonObject>()) {
        error(request, "Expected an object");
        return;
      }

      const auto& data = json.as<JsonObject>();

      // Get delay and fade
      millis_t delay_duration = 0;
      millis_t fade_duration = 0;

      if (data.containsKey("delay_duration")) {
        if (!data["delay_duration"].is<int>()) {
          error(request, "delay_duration should be a number");
          return;
        }

        delay_duration = convert_to_time_value(data["delay_duration"].as<int>());
      }
      if (data.containsKey("fade_duration")) {
        if (!data["fade_duration"].is<int>()) {
          error(request, "fade_duration should be a number");
          return;
        }

        fade_duration = convert_to_time_value(data["fade_duration"].as<int>());
      }

      if (!data.containsKey("red")) {
        error(request, "red should be a number");
        return;
      } else if (!data["red"].is<int>()) {
        error(request, "red should be a number");
        return;
      }
      const auto red = convert_to_color_value(data["red"].as<int>())

      if (!data.containsKey("green")) {
        error(request, "green should be a number");
        return;
      } else if (!data["green"].is<int>()) {
        error(request, "green should be a number");
        return;
      }
      const auto green = convert_to_color_value(data["green"].as<int>())

      if (!data.containsKey("blue")) {
        error(request, "blue should be a number");
        return;
      } else if (!data["blue"].is<int>()) {
        error(request, "blue should be a number");
        return;
      }
      const auto blue = convert_to_color_value(data["blue"].as<int>())

      m_state_manager.set(
          current_time
          delay_duration,
          fade_duration,
          red, green, blue)
      request->send(200);
    }

    void api_post_mode(AsyncWebServerRequest* request, JsonVariant& json) {
      if (!json.is<JsonObject>()) {
        error(request, "Expected an object");
        return;
      }

      const auto& data = json.as<JsonObject>();

      if (!data.containsKey("name")) {
        error(request, "name required");
        return;
      } else if (!data["name"].is<char *>()) {
        error(request, "name must be a string");
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

  private: // helpers

    void set_mode_idle(AsyncWebServerRequest* request, const JsonObject&) const {
      m_state_manager.set_idle_state();
      request->send(200);
    }

    void set_mode_random(AsyncWebServerRequest* request, const JsonObject& data) const {
      if (!data.containsKey("type")) {
        error(request, "type is required");
        return;
      } else if (!data["type"].is<char *>()) {
        error(request, "type should be a string");
        return;
      }
      auto&& type = data["type"].as<String>();

      // Get delay and fade
      millis_t delay_duration = 0;
      millis_t fade_duration = 0;

      if (data.containsKey("delay_duration")) {
        if (!data["delay_duration"].is<int>()) {
          error(request, "delay_duration should be a number");
          return;
        }

        delay_duration = convert_to_time_value(data["delay_duration"].as<int>());
      }
      if (data.containsKey("fade_duration")) {
        if (!data["fade_duration"].is<int>()) {
          error(request, "fade_duration should be a number");
          return;
        }

        fade_duration = convert_to_time_value(data["fade_duration"].as<int>());
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
        error(request, "Invalid random type");
        return;
      }
      request->send(200);
    }

    size_t convert_to_color_value(int val) const {
      if (val < 0) {
        val = 0;
      } else if (val > 255) {
        val = 255;
      }
      return static_cast<size_t>(val);
    }

    millis_t convert_to_time_value(int val) const {
      if (val < 0) {
        val = 0;
      }
      return static_cast<millis_t>(val);
    }

    size_t convert_to_index(int val) const {
      if (val < 0) {
        val = 0;
      }
      return static_cast<size_t>(val);
    }

    void error(AsyncWebServerRequest* request, char* msg) const {
      // TODO: Support error codes
      request->send(400, "text/plain", msg);
    }

  private: // members
    array_t<CRGB, NUM_LEDS> m_leds;
    StateManager<NUM_LEDS> m_state_manager;
};
