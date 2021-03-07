import { build_single_task_queue } from './task_queues';

// types

interface RandomModeConfig {
  type: "INDIVIDUAL"|"UNIFORM";
  delay_duration?: number;
  fade_duration?: number;
}

interface IdleConfig {}

type ModeConfig = RandomModeConfig | IdleConfig;

interface LedDataEntry {
  index: number;
  red?: number;
  green?: number;
  blue?: number;
  delay_duration?: number;
  fade_duration?: number;
}

interface LedsData {
  red: number;
  green: number;
  blue: number;
  delay_duration?: number;
  fade_duration?: number;
}

interface BrightnessData {
  brightness: number;
  delay_duration?: number;
  fade_duration?: number;
}

export {
  RandomModeConfig,
  IdleConfig,
  ModeConfig,
  LedDataEntry,
  LedsData,
};

// utils

function get_data(url) {
  return fetch(url).then(response => response.json());
}

function post_data(url, data) {
  return fetch(url, {
    method: "POST",
    headers: {
      'Accept': 'application/json',
      'Content-Type': 'application/json',
    },
    body: JSON.stringify(data),
  });
}

// api

function is_connected() {
  return get_alive()
    .then((response) => {
      return response.trim() === 'yes';
    })
    .catch((error) => {
      console.error('Not connected:', error);
      return false;
    });
}

function assert_response_is_object(response) {
  if (typeof response === 'object') {
    return response;
  }
  throw `Response should be an object but isn't: ${String(response).substr(0, 20)}`;
}

function get_alive() {
  return fetch('api/alive').then((response) => response.text());
}

function get_led(index?: number) {
  if (index !== undefined) {
    return get_data(`api/led?index=${index}`).then(assert_response_is_object);
  } else {
    return get_data("api/led").then(assert_response_is_object);
  }
}

function get_mode() {
  return get_data("api/mode").then(assert_response_is_object);
}

function get_brightness() {
  return get_data("api/brightness").then(assert_response_is_object);
}

function post_mode(name: string, config?: ModeConfig) {
  if (config === undefined) {
    config = {};
  }
  return post_data("api/mode", { name, ...config });
}

function post_led(led_data: Array<LedDataEntry>) {
  return post_data("api/led", led_data);
}

function post_leds(leds_data: LedsData) {
  return post_data("api/leds", leds_data);
}

function post_brightness(data: BrightnessData) {
  return post_data("api/brightness", data)
}

export {
  is_connected,
  get_alive,
  get_led,
  get_mode,
  get_brightness,
  post_led,
  post_leds,
  post_mode,
  post_brightness,
};
