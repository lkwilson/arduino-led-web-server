function unwrap(cb) {
  return event => cb(event.target.value);
}

function unwrap_num(cb) {
  const unwrapper = unwrap(Number);
  return event => cb(unwrapper(event));
}

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


export {
  unwrap,
  unwrap_num,
  hex_to_rgb,
  rgb_to_hex,
};
