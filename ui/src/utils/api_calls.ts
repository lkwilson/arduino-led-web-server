import axios from 'axios';

// types
interface RandomModeConfig {
  type: "INDIVIDUAL"|"UNIFORM";
  delay_duration?: number;
  fade_duration?: number;
}

interface IdleConfig {

}

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

export {
  RandomModeConfig,
  IdleConfig,
  ModeConfig,
  LedDataEntry,
  LedsData,
};

// api

function is_connected() {
  return get_alive()
    .then(response_data => {
      return response_data.trim() === "yes";
    })
    .catch(_ => {
      return false;
    });
}

function assert_response_is(response, type: "string"|"object") {
  if (typeof(response.data) === type) {
    return response;
  }
  throw `Response should be of type ${type} but isn't: ${response.data}`;
}

function assert_response_is_object(response) {
  return assert_response_is(response, "object");
}

function assert_response_is_string(response) {
  return assert_response_is(response, "string");
}

function get_alive() {
  return axios.get('api/alive').then(assert_response_is_string);;
}

function get_led(index?: number) {
  if (index !== undefined) {
    return axios.get(`api/led?index=${index}`).then(assert_response_is_object);
  } else {
    return axios.get("api/led").then(assert_response_is_object);
  }
}

function get_mode() {
  return axios.get("api/mode").then(assert_response_is_object);
}

function get_brightness() {
  return axios.get("api/brightness").then(assert_response_is_object);
}

function post_mode(name: string, config: ModeConfig) {
  return axios.post("api/mode", { name, ...config });
}

function post_led(led_data: Array<LedDataEntry>) {
  return axios.post("api/led", led_data);
}

function post_leds(leds_data: LedsData) {
  return axios.post("api/led", leds_data);
}

function post_brightness(brightness: number) {
  return axios.post("api/brightness", { brightness })
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
