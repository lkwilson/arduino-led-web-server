#pragma once

#include <FastLED.h>

enum class ColorStateEnum {
  IDLE,
  FADE,
  FOLLOW,
};

enum class StateManagerEnum {
  IDLE,
  UNIFORM_RANDOM,
  EACH_RANDOM,
};

struct FollowState {
  void update(const millis_t current_time, CRGB& led)
  {

  }
};

struct FadeLogic {
  void set(const int start, const int end) {
    m_start = start;
    m_end = end;
    m_offset = end - start;
  }

  int get(const double progress) const {
    return m_start + m_offset * progress;
  }

  int get_end() const {
    return m_end;
  }

  int m_start;
  int m_end;
  int m_offset;
};

struct FadeState {
  void set(
      const millis_t init_time,
      const millis_t delay_duration,
      const millis_t fade_duration,
      CRGB& led,
      CRGB target_color)
  {
    m_init_time = init_time;
    m_delay_duration = delay_duration;
    m_fade_duration = fade_duration;
    m_red.set(led.red, target_color.red);
    m_green.set(led.green, target_color.green);
    m_blue.set(led.blue, target_color.blue);
  }

  // returns true when done
  bool update(const millis_t current_time, CRGB& led) const {
    const auto delay_interval = current_time - m_init_time;
    const auto fade_interval = delay_interval - m_delay_duration;
    if (delay_interval <= m_delay_duration) {
      // Do nothing
      return false;
    } else if (fade_interval < m_fade_duration) {
      // 0 < fade_interval < m_fade_duration
      const auto progress = static_cast<double>(fade_interval) / m_fade_duration;
      led.red = m_red.get(progress);
      led.green = m_green.get(progress);
      led.blue = m_blue.get(progress);
      return false;
    } else {
      led.red = m_red.get_end();
      led.green = m_green.get_end();
      led.blue = m_blue.get_end();
      return true;
    }
  }

  millis_t m_init_time;
  millis_t m_delay_duration;
  millis_t m_fade_duration;

  FadeLogic m_red;
  FadeLogic m_green;
  FadeLogic m_blue;

  ColorStateEnum m_prev_state;
};

struct ColorState {
  ColorState() : m_state(ColorStateEnum::IDLE) {}

  ColorStateEnum update(const millis_t current_time, CRGB& led) {
    switch (m_state)
    {
      case ColorStateEnum::FADE:
      {
        const auto done = m_fade.update(current_time, led);
        if (done) {
          m_state = ColorStateEnum::IDLE;
        }
        break;
      }
      case ColorStateEnum::FOLLOW:
      {
        m_follow.update(current_time, led);
        break;
      }
      default:
      {
        Serial.println("Error: Invalid color state");
      }
      case ColorStateEnum::IDLE:
      {
        break;
      }
    }
    return m_state;
  }

  void start_fade_state(
      const millis_t init_time,
      const millis_t delay_duration,
      const millis_t fade_duration,
      CRGB& led,
      CRGB target_color) {
    m_state = ColorStateEnum::FADE;
    m_fade.set(init_time, delay_duration, fade_duration, led, target_color);
  }

  FadeState m_fade;
  FollowState m_follow;
  ColorStateEnum m_state;
};

template<size_t NUM_LEDS>
struct StateManager {
  public: // ctors
    StateManager(array_t<CRGB, NUM_LEDS>& leds)
    : m_state(StateManagerEnum::IDLE), m_leds(leds), m_states()
    {}

  public: // api
    void set(
        const size_t i,
        const millis_t current_time,
        const millis_t delay_duration,
        const millis_t fade_duration,
        const CRGB color) {
      m_states[i].start_fade_state(
          current_time,
          delay_duration,
          fade_duration,
          m_leds[i],
          color);
    }

    void set(
        const millis_t current_time,
        const millis_t delay_duration,
        const millis_t fade_duration,
        const CRGB color) {
      for (size_t i = 0; i < NUM_LEDS; ++i)
      {
        set(
            i,
            current_time,
            delay_duration,
            fade_duration,
            color);
      }
    }

    void update() {
      const auto current_time = millis();
      bool any_active = false;
      for (size_t i = 0; i < NUM_LEDS; ++i)
      {
        const auto state = m_states[i].update(current_time, m_leds[i]);
        if (state != ColorStateEnum::IDLE) {
          any_active = true;
        }
      }
      if (!any_active) {
        switch (m_state) {
          case StateManagerEnum::UNIFORM_RANDOM:
          {
            CRGB rnd_color = CHSV(rand_color(), 255, 255);
            set(
                millis(),
                m_random_delay_duration,
                m_random_fade_duration,
                rnd_color);
            break;
          }
          case StateManagerEnum::EACH_RANDOM:
          {
            const auto current_time = millis();
            for (size_t i = 0; i < NUM_LEDS; ++i)
            {
              CRGB rnd_color = CHSV(rand_color(), 255, 255);
              set(
                  i,
                  current_time,
                  m_random_delay_duration,
                  m_random_fade_duration,
                  rnd_color);
            }
            break;
          }
          case StateManagerEnum::IDLE:
          {
            // Do nothing since idling
          }
          default:
          {
            break;
          }
        }
      }
    }

    void start_uniform_random_fade_loop(const millis_t delay_duration, const millis_t fade_duration) {
      m_state = StateManagerEnum::UNIFORM_RANDOM;
      m_random_delay_duration = delay_duration;
      m_random_fade_duration = fade_duration;
    }

    void start_each_random_fade_loop(const millis_t delay_duration, const millis_t fade_duration) {
      m_state = StateManagerEnum::EACH_RANDOM;
      m_random_delay_duration = delay_duration;
      m_random_fade_duration = fade_duration;
    }

    void set_idle_state() {
      m_state = StateManagerEnum::IDLE;
    }

    StateManagerEnum get_state() const {
      return m_state;
    }

  private: // helper methods
    uint8_t rand_color() {
      return random(256);
    }

  private: // members
    StateManagerEnum m_state;
    array_t<CRGB, NUM_LEDS>& m_leds;
    array_t<ColorState, NUM_LEDS> m_states;

    // state members
    millis_t m_random_delay_duration;
    millis_t m_random_fade_duration;
};
