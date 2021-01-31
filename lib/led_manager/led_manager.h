#pragma once

#include <ESPAsyncWebServer.h>
#include <FastLED.h>
#include <qr_util.h>

struct Fader {
  public: // ctor
    Fader() : m_active(false) {}

  public: // api
    void set(
        const millis_t start_time,
        unsigned long duration,
        const CRGB& current_color,
        const uint8_t r,
        const uint8_t g,
        const uint8_t b) {
      m_active = true;
      m_base_color = current_color;
      m_target_color.r = r;
      m_target_color.g = g;
      m_target_color.b = b;

      m_r_offset = r;
      m_r_offset -= current_color.r;

      m_g_offset = g;
      m_g_offset -= current_color.g;

      m_b_offset = b;
      m_b_offset -= current_color.b;

      m_start_time = start_time;
      m_duration = duration;
    }

    bool is_active() const {
      return m_active;
    }

    bool update(const millis_t current_time, CRGB& led) {
      const auto passed_time = current_time - m_start_time;
      if (passed_time < m_duration) {
        const auto progress = static_cast<double>(passed_time) / m_duration;
        const auto transformed_progress = transform_progress(progress);
        led.r = m_base_color.r + static_cast<int>(transformed_progress * m_r_offset);
        led.g = m_base_color.g + static_cast<int>(transformed_progress * m_g_offset);
        led.b = m_base_color.b + static_cast<int>(transformed_progress * m_b_offset);
      } else {
        m_active = false;
        led = m_target_color;
      }
      return m_active;
    }

    void clear() {
      m_active = false;
    }

  private: // helper methods
    // This can change how the transition curve looks. Currently it's linear.
    double transform_progress(const double progress) {
      return progress;
    }

  private: // members
    bool m_active;

    CRGB m_base_color;
    CRGB m_target_color;

    int m_r_offset;
    int m_b_offset;
    int m_g_offset;

    millis_t m_start_time;
    millis_t m_duration;
};

template<size_t NUM_LEDS>
struct FadeManager {
  public: // ctors
    FadeManager(array_t<CRGB, NUM_LEDS>& leds) : m_leds(leds), m_faders() {}

  public: // api
    void set(
        const size_t i,
        const millis_t start_time,
        unsigned long duration,
        const uint8_t r,
        const uint8_t g,
        const uint8_t b) {
      m_faders[i].set(start_time, duration, m_leds[i], r, g, b);
    }

    void set(
        const millis_t start_time,
        unsigned long duration,
        const uint8_t r,
        const uint8_t g,
        const uint8_t b) {
      for (size_t i = 0; i < NUM_LEDS; ++i) {
        set(i, start_time, duration, r, g, b);
      }
    }

    void clear(const size_t i) {
      m_faders[i].clear();
    }

    void clear() {
      for (size_t i = 0; i < NUM_LEDS; ++i) {
        clear(i);
      }
    }

    bool update(const size_t i, const millis_t current_time) {
      return m_faders[i].update(current_time, m_leds[i]);
    }

    bool update(const millis_t current_time) {
      bool any_active = false;
      for (size_t i = 0; i < NUM_LEDS; ++i) {
        if (update(i, current_time)) {
          any_active = true;
        }
      }
      return any_active;
    }

  private: // members
    array_t<CRGB, NUM_LEDS>& m_leds;
    array_t<Fader, NUM_LEDS> m_faders;
};

template<size_t DATA_PIN, size_t NUM_LEDS>
struct LedManager {
  public: // ctors
    LedManager() : m_leds(), m_fade_manager(m_leds) {}

  public: // api
    void setup() {
      Serial.printf("LED manager loading with %d leds and data pin %d\n", NUM_LEDS, DATA_PIN);
      FastLED.addLeds<NEOPIXEL, DATA_PIN>(m_leds, NUM_LEDS);
    }

    void loop() {
      fade_all_to(10, 10, 10, 500);
      fade_all_to(10, 0, 0, 500);
      fade_all_to(0, 10, 0, 500);
      fade_all_to(0, 0, 10, 500);
      fade_all_to(0, 0, 0, 500);
    }

  public: // web api
    void add_handles(AsyncWebServer&) {
      Serial.println("Adding handles for LedManager");
    }

  private: // helper methods
    void fade_all_to(const uint8_t r, const uint8_t g, const uint8_t b, unsigned long duration) {
      const auto start_time = millis();
      Serial.printf("Starting fade: %d %d %d %d\n", r, g, b, duration);
      m_fade_manager.set(start_time, duration, r, g, b);
      while (m_fade_manager.update(millis()))
      {
        FastLED.show();
        yield();
      }
    }

  private: // members
    array_t<CRGB, NUM_LEDS> m_leds;
    FadeManager<NUM_LEDS> m_fade_manager;
};
