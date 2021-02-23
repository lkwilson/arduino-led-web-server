import axios from 'axios';

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

// api

const queue_full_error = "Queue is full. Skipping.";
const send_queue = (_ => {
  let queues = {};
  let lengths = {};
  const max_length = 2;

  function add(id, cb) {
    if (!(id in queues)) {
      queues[id] = Promise.resolve();
      lengths[id] = 0;
    }
    const results = queues[id].then(_ => {
      lengths[id] = lengths[id] - 1;
      if (lengths[id] >= max_length) {
        throw queue_full_error;
      }
      return cb();
    });
    lengths[id] = lengths[id] + 1;
    queues[id] = results.catch(_ => {}).then();
    return results;
  }

  return {
    add,
  }
})();

function is_connected() {
  return send_queue.add("is_connected", _ => {
    return get_alive()
      .then(response => {
        return response.data.trim() === "yes";
      })
      .catch(_ => {
        return false;
      });
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
  return send_queue.add("get_alive", _ => {
    return axios.get('api/alive').then(assert_response_is_string);
  });
}

function get_led(index?: number) {
  return send_queue.add("get_led", _ => {
    if (index !== undefined) {
      return axios.get(`api/led?index=${index}`).then(assert_response_is_object);
    } else {
      return axios.get("api/led").then(assert_response_is_object);
    }
  });
}

function get_mode() {
  return send_queue.add("get_mode", _ => {
    return axios.get("api/mode").then(assert_response_is_object);
  });
}

function get_brightness() {
  return send_queue.add("get_brightness", _ => {
    return axios.get("api/brightness").then(assert_response_is_object);
  });
}

function post_mode(name: string, config?: ModeConfig) {
  return send_queue.add("post_mode", _ => {
    if (config === undefined) {
      config = {};
    }
    return axios.post("api/mode", { name, ...config });
  });
}

function post_led(led_data: Array<LedDataEntry>) {
  return send_queue.add("post_led", _ => {
    return axios.post("api/led", led_data);
  });
}

function post_leds(leds_data: LedsData) {
  return send_queue.add("post_leds", _ => {
    return axios.post("api/leds", leds_data);
  });
}

function post_brightness(data: BrightnessData) {
  return send_queue.add("post_brightness", _ => {
    return axios.post("api/brightness", data)
  });
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
