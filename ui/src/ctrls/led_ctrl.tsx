import React, { useState, useEffect } from 'react';
import { unwrap, unwrap_num, rgb_to_hex, hex_to_rgb } from '../utils/utils';

function LedCtrl() {
  const [red, set_red] = useState(0);
  const [green, set_green] = useState(0);
  const [blue, set_blue] = useState(0);
  const [brightness, set_brightness] = useState(255);

  useEffect(_ => {
  }, []);

  function set_color(hex_value) {
    const color = hex_to_rgb(hex_value);
    if (color == null) {

    } else {
      const { red, green, blue } = color;
      set_red(red);
      set_green(green);
      set_blue(blue);
    }
  }

  const hex_display = rgb_to_hex({ red, green, blue });
  return (
    <div className="container-column">
      <h1 className="section-title">Lights</h1>
      <div className="container-column mode-form">
        <label htmlFor="color_picker">
          Color: {hex_display}
          <input type="color" name="color_picker" id="color_picker" value={hex_display} onChange={unwrap(set_color)} />
        </label>
        <label htmlFor="red_slider">
          Red: {red}
          <input type="range" min="0" max="255" name="red_slider" id="red_slider" value={red} onChange={unwrap_num(set_red)} />
        </label>
        <label htmlFor="green">
          Green: {green}
          <input type="range" min="0" max="255" name="green" id="green" value={green} onChange={unwrap_num(set_green)} />
        </label>
        <label htmlFor="blue">
          Blue: {blue}
          <input type="range" min="0" max="255" name="blue" id="blue" value={blue} onChange={unwrap_num(set_blue)} />
        </label>
        <label htmlFor="brightness">
          Brightness: {brightness}
          <input type="range" min="0" max="255" name="brightness" id="brightness" value={brightness} onChange={unwrap_num(set_brightness)} />
        </label>
      </div>
    </div>
  );
}

export { LedCtrl };
