import axios from 'axios';

interface RandomModeConfig {
  type: "IDLE"|"UNIFORM";
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

function get_led(index?: number) {
  if (index !== undefined) {
    return axios.get(`api/led?index=${index}`);
  } else {
    return axios.get("api/led");
  }
}

function get_mode() {
  return axios.get("api/mode");
}

function get_brightness() {
  return axios.get("api/brightness");
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
  ModeConfig,
  get_led,
  get_mode,
  get_brightness,
  post_led,
  post_leds,
  post_mode,
  post_brightness,
};
