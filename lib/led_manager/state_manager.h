#pragma once

#include <FastLED.h>

enum class ColorStateEnum {
  IDLE,
  FADE,
  FOLLOW,
};

enum class StateManagerEnum {
  IDLE,
  RANDOM,
};

String enum_to_string(const StateManagerEnum type) {
  switch (type) {
    case StateManagerEnum::IDLE: return "IDLE";
    case StateManagerEnum::RANDOM: return "RANDOM";
    default: return "UNKNOWN";
  }
}

enum class RandomTypeEnum {
  UNIFORM,
  INDIVIDUAL,
};

String enum_to_string(const RandomTypeEnum type) {
  switch (type) {
    case RandomTypeEnum::UNIFORM: return "UNIFORM";
    case RandomTypeEnum::INDIVIDUAL: return "INDIVIDUAL";
    default: return "UNKNOWN";
  }
}

bool string_to_enum(const String& str, RandomTypeEnum& value) {
  if (str == "UNIFORM") {
    value =  RandomTypeEnum::UNIFORM;
    return true;
  } else if (str == "INDIVIDUAL") {
    value = RandomTypeEnum::INDIVIDUAL;
    return true;
  } else {
    return false;
  }
}

uint8_t rand_color() {
  return rand() % 256;
}

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

struct FadeColorState {
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
    switch (m_state) {
      case ColorStateEnum::FADE: {
        const auto done = m_fade.update(current_time, led);
        if (done) {
          m_state = ColorStateEnum::IDLE;
        }
        break;
      }
      case ColorStateEnum::FOLLOW: {
        m_follow.update(current_time, led);
        break;
      }
      case ColorStateEnum::IDLE: {
        break;
      }
      default: {
        Serial.println("Error: Invalid color state");
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

  FadeColorState m_fade;
  FollowState m_follow;
  ColorStateEnum m_state;
};

template<size_t NUM_LEDS>
struct RandomStateManager;

struct BrightnessStateManager {
  public: // api
    uint8_t get() const {
      return FastLED.getBrightness();
    }

    void set(
        const millis_t init_time,
        const millis_t delay_duration,
        const millis_t fade_duration,
        const uint8_t target_brightness)
    {
      m_init_time = init_time;
      m_delay_duration = delay_duration;
      m_fade_duration = fade_duration;
      m_fader.set(FastLED.getBrightness(), target_brightness);
      m_active = true;
    }

    // returns true when done
    void update(const millis_t current_time) {
      if (not m_active) {
        return;
      }
      const auto delay_interval = current_time - m_init_time;
      const auto fade_interval = delay_interval - m_delay_duration;
      if (delay_interval <= m_delay_duration) {
        // Do nothing
      } else if (fade_interval < m_fade_duration) {
        // 0 < fade_interval < m_fade_duration
        const auto progress = static_cast<double>(fade_interval) / m_fade_duration;
        FastLED.setBrightness(m_fader.get(progress));
      } else {
        FastLED.setBrightness(m_fader.get_end());
        m_active = false;
      }
    }

  private: // members
    bool m_active;
    FadeLogic m_fader;
    millis_t m_init_time;
    millis_t m_delay_duration;
    millis_t m_fade_duration;
};


template<size_t NUM_LEDS>
struct StateManager {
  public: // ctors
    StateManager(array_t<CRGB, NUM_LEDS>& leds)
    : m_state(StateManagerEnum::IDLE), m_leds(leds), m_states(), m_random_state_manager(*this) {}

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
      for (size_t i = 0; i < NUM_LEDS; ++i) {
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

      m_brightness_state_manager.update(current_time);
      bool any_active = false;
      for (size_t i = 0; i < NUM_LEDS; ++i) {
        const auto state = m_states[i].update(current_time, m_leds[i]);
        any_active = any_active or state != ColorStateEnum::IDLE;
      }
      if (not any_active) {
        switch (m_state) {
          case StateManagerEnum::RANDOM: {
            m_random_state_manager.update();
            break;
          }
          default: {
            // do nothing since idling
            break;
          }
        }
      }
    }

    void set_brightness(const millis_t current_time, const millis_t delay_duration, const millis_t fade_duration, const uint8_t brightness) {
      m_brightness_state_manager.set(current_time, delay_duration, fade_duration, brightness);
    }

    uint8_t get_brightness() const {
      return m_brightness_state_manager.get();
    }

    void set_random_state(const RandomTypeEnum type, const millis_t delay_duration, const millis_t fade_duration) {
      m_state = StateManagerEnum::RANDOM;
      m_random_state_manager.set(type, delay_duration, fade_duration);
    }

    void set_idle_state() {
      m_state = StateManagerEnum::IDLE;
    }

    StateManagerEnum get_state() const {
      return m_state;
    }

    RandomStateManager<NUM_LEDS> get_random_state_manager() const {
      return m_random_state_manager;
    }

  private: // members
    StateManagerEnum m_state;
    array_t<CRGB, NUM_LEDS>& m_leds;
    array_t<ColorState, NUM_LEDS> m_states;

    // brightness state manager
    BrightnessStateManager m_brightness_state_manager;

    // random state manager
    RandomStateManager<NUM_LEDS> m_random_state_manager;
};

template<size_t NUM_LEDS>
struct RandomStateManager {
  public:
    RandomStateManager(StateManager<NUM_LEDS>& state_manager)
    : m_state_manager(state_manager) {}

    void set(const RandomTypeEnum type, const millis_t delay_duration, const millis_t fade_duration) {
      m_type = type;
      m_delay_duration = delay_duration;
      m_fade_duration = fade_duration;
    }

    void update() {
      const auto current_time = millis();
      switch(m_type) {
        case RandomTypeEnum::UNIFORM: {
          CRGB rnd_color = CHSV(rand_color(), 255, 255);
          m_state_manager.set(
              current_time,
              m_delay_duration,
              m_fade_duration,
              rnd_color);
          break;
        }
        case RandomTypeEnum::INDIVIDUAL: {
          for (size_t i = 0; i < NUM_LEDS; ++i) {
            CRGB rnd_color = CHSV(rand_color(), 255, 255);
            m_state_manager.set(
                i,
                current_time,
                m_delay_duration,
                m_fade_duration,
                rnd_color);
          }
          break;
        }
      }
    }

  public: // accessors
    RandomTypeEnum get_type() const { return m_type; }
    millis_t get_delay_duration() const { return m_delay_duration; }
    millis_t get_fade_duration() const { return m_fade_duration; }

  private: // members
    StateManager<NUM_LEDS>& m_state_manager;
    RandomTypeEnum m_type;
    millis_t m_delay_duration;
    millis_t m_fade_duration;
};
