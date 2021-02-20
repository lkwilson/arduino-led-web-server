import axios from 'axios';

// helpers

function jsonify_response(response) {
  return JSON.parse(response.data);
}

// api

function get_led(index?: number) {
  if (index !== undefined) {
    return axios.get(`api/led?index=${index}`).then(jsonify_response);
  } else {
    return axios.get("api/led").then(jsonify_response);
  }
}

function get_mode() {
  return axios.get("api/mode").then(jsonify_response);
}

function get_brightness() {
  return axios.get("api/brightness").then(jsonify_response);
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
  get_led,
  get_mode,
  get_brightness,
  post_led,
  post_leds,
  post_mode,
  post_brightness,
};
