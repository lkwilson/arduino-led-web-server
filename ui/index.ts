import './index.css';

function get_value_from_id(id: string) {
  const el = document.getElementById(id) as HTMLInputElement;
  return el.value;
}

function get_value_from_event(event: Event) {
  const el = event.target as HTMLInputElement;
  return el.value;
}

const local_state = {
  red: null,
  green: null,
  blue: null,
};

const remote_state = {
  red: null,
  green: null,
  blue: null,
};

function rgb_to_hex({ red, green, blue }) {
  function componentToHex(c) {
    const hex = c.toString(16);
    return hex.length == 1 ? "0" + hex : hex;
  }

  return "#" + componentToHex(red) + componentToHex(green) + componentToHex(blue);
}

function hex_to_rgb(hex) {
  const result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
  return result ? {
    red: parseInt(result[1], 16),
    green: parseInt(result[2], 16),
    blue: parseInt(result[3], 16)
  } : null;
}

interface ServerResponse {
  text: string,
  status: number,
}

function send_request(method, url, timeout = 500): Promise<ServerResponse> {
  return new Promise((resolve, reject) => {
    console.debug("Sending:", method, url);
    const request = new XMLHttpRequest();

    request.addEventListener("load", function() {
      resolve({
        text: request.responseText,
        status: request.status,
      });
    });
    request.addEventListener("error", function() {
      reject("error");
    });
    request.addEventListener("abort", function() {
      reject("abort");
    });
    request.addEventListener("timeout", function() {
      reject("timeout");
    });

    request.open(method, url, true);
    request.timeout = timeout;
    request.send();
  });
}

function build_update() {
  const update_red = local_state.red !== remote_state.red;
  const update_green = local_state.green !== remote_state.green;
  const update_blue = local_state.blue !== remote_state.blue;

  const num_update_colors = [update_red, update_green, update_blue].filter(v=>v).length;
  if (num_update_colors > 1) {
    return {
      color: 'all',
      url: `/color/${local_state.red}/${local_state.green}/${local_state.blue}`,
    };
  } else if (update_red) {
    return {
      color: 'red',
      url: `/red/${local_state.red}`,
    };
  } else if (update_green) {
    return {
      color: 'green',
      url: `/green/${local_state.green}`,
    };
  } else if (update_blue) {
    return {
      color: 'blue',
      url: `/blue/${local_state.blue}`,
    };
  } else {
    return null;
  }
}

let pushing = false;
let last_state_push = {
  id: null,
  tries: 0,
};
function increment_push(id) {
  if (last_state_push.id !== id) {
    last_state_push.id = id;
    last_state_push.tries = 0;
  } else {
    ++last_state_push.tries;
  }
  return last_state_push.tries > 5;
}

function update_with_response(color, text) {
  let new_values = text.trim().split(' ').filter(str => str.length !== 0).map(str => parseInt(str));
  if (new_values.some(isNaN)) {
    console.error("The response was invalid:", text, new_values);
  } else if (color === 'all' && new_values.length === 3) {
    const [ red, green, blue ] = new_values;
    Object.assign(remote_state, { red, green, blue });
  } else if (new_values.length === 1) {
    remote_state[color] = new_values[0];
  } else {
    console.error("The response was invalid:", text, new_values);
    return;
  }
}

async function push_state() {
  if (pushing) {
    return;
  }
  pushing = true;
  const update = build_update();
  if (update === null) {
    // TODO: what?
    //push_state.id = null;
    pushing = false;
    return;
  }
  const { color, url } = update;
  if (increment_push(url)) {
    console.error("Retried too many times. Stopping.");
    pushing = false;
    return;
  }
  send_request("POST", url).then(resp => {
    const { status, text } = resp;
    if (status > 400) {
      console.error("Unable to push state to server:", url);
    } else {
      update_with_response(color, text)
    }
  }).then(_ => {
    pushing = false;
    push_state();
  }).catch(err => {
    console.error("Failed to push state to server:", err);
    pushing = false;
    push_state();
  });
}

function update_color(color, value) {
  local_state[color] = Number(value);

  render();
  push_state();
}

function update_hex(value) {
  const { red, green, blue } = hex_to_rgb(value);
  local_state.red = red * 4;
  local_state.green = green * 4;
  local_state.blue = blue * 4;

  render();
  push_state();
}

function update_value(id: string, value) {
  document.getElementById(`${id}_value`).innerHTML = value;
  (document.getElementById(id) as HTMLInputElement).value = value;
}

function render() {
  const { red, green, blue } = local_state;
  const hex = rgb_to_hex({
    red: Math.floor(red/4),
    green: Math.floor(green/4),
    blue: Math.floor(blue/4),
  });
  update_value("hex", hex);
  update_value("red", red);
  update_value("green", green);
  update_value("blue", blue);
}

function get_state() { 
  return new Promise(async (resolve, reject) => {
    for (let i = 0; i < 5; ++i) {
      try {
        const { text, status } = await send_request("GET", "/color");
        if (status > 400) {
          console.error("Failed to get state from server. It may not be online.");
        } else {
          resolve(text);
          return;
        }
      } catch (err) {
        console.error("An error occurred loading the state:", err);
      }
    }
    reject();
  });
}

function pull_state() {
  get_state().then(text => {
    update_with_response('all', text);
    render();
  }).catch(_ => {
    console.error("Unable to load state");
    render();
  });
}

function setup() {
  // Loading state from server side rendered state.
  const server_state = {
    red: parseInt(get_value_from_id("red")),
    green: parseInt(get_value_from_id("green")),
    blue: parseInt(get_value_from_id("blue")),
  };
  Object.assign(remote_state, server_state);
  Object.assign(local_state, server_state);
  render();

  // Uncomment to have client poll server state
  //setInterval(pull_state, 1000);
  document.getElementById("red").addEventListener("input", event => update_color("red", get_value_from_event(event)));
  document.getElementById("green").addEventListener("input", event => update_color("green", get_value_from_event(event)));
  document.getElementById("blue").addEventListener("input", event => update_color("blue", get_value_from_event(event)));
  document.getElementById("hex").addEventListener("input", event => update_hex(get_value_from_event(event)));
}

setup();
