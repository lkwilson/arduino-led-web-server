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
    .then(response => {
      return response.data.trim() === "yes";
    })
    .catch(_ => {
      return false;
    });
}

function assert_response_is(response, type: "string"|"object") {
  if (typeof(response.data) === type) {
    return response;
  }
  throw `Response should be of type ${type} but isn't: ${response.data.toString().substr(0, 20)}`;
}

function assert_response_is_object(response) {
  return assert_response_is(response, "object");
}

function assert_response_is_string(response) {
  return assert_response_is(response, "string");
}

function get_alive() {
  return get_data('api/alive').then(assert_response_is_string);
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
