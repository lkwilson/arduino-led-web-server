import React, { useState, useEffect, useRef } from 'react';
import { unwrap, unwrap_num, rgb_to_hex, hex_to_rgb } from '../utils/utils';
import { ColorPickrWrapper } from '../utils/pickr_adapter';

function LedCtrl() {
  const [color, set_color] = useState({ red: 0, green: 0, blue: 0 });
  const [brightness, set_brightness] = useState(255);
  const [delay_duration, set_delay_duration ] = useState("");
  const [fade_duration, set_fade_duration ] = useState("");

  useEffect(_ => {
    // Load from API
  }, []);

  const int_color = {
    red: Math.round(color.red),
    green: Math.round(color.green),
    blue: Math.round(color.blue),
  };
  const set_red = red => set_color({ ...int_color, red });
  const set_green = green => set_color({ ...int_color, green });
  const set_blue = blue => set_color({ ...int_color, blue });

  function set_delay(value) {
    if (value == null || value === "") {
      set_delay_duration("");
    } else {
      set_delay_duration(Math.max(0, Math.round(Number(value))));
    }
  }
  function set_fade(event) {
    const value = event.target.value;
    if (value == null || value === "") {
      set_fade_duration("");
    } else {
      set_fade_duration(Math.max(0, Math.round(Number(value))));
    }
  }

  function set_display_color(hex_color) {
    const rgb_color = hex_to_rgb(hex_color);

    if (rgb_color == null) {
      return;
    }

    set_color(rgb_color);
  }

  const { red, green, blue } = int_color;
  const hex_value = rgb_to_hex(int_color);
  return (
    <div className="container-column">
      <h1 className="section-title">Lights</h1>
      <div className="container-column mode-form">
        <div>
          {hex_value.toUpperCase()}
          <ColorPickrWrapper color={color} set_color={set_color} />
        </div>
        <label htmlFor="red_slider">
          Red: {red} (0x{red.toString(16).toUpperCase()})
          <br />
          <input type="range" min="0" max="255" name="red_slider" id="red_slider" value={red} onChange={unwrap_num(set_red)} />
        </label>
        <label htmlFor="green">
          Green: {green} (0x{green.toString(16).toUpperCase()})
          <br />
          <input type="range" min="0" max="255" name="green" id="green" value={green} onChange={unwrap_num(set_green)} />
        </label>
        <label htmlFor="blue">
          Blue: {blue} (0x{blue.toString(16).toUpperCase()})
          <br />
          <input type="range" min="0" max="255" name="blue" id="blue" value={blue} onChange={unwrap_num(set_blue)} />
        </label>
        <label htmlFor="brightness">
          Brightness: {brightness} ({Math.round(brightness / 255 * 100)}%)
          <br />
          <input type="range" min="0" max="255" name="brightness" id="brightness" value={brightness} onChange={unwrap_num(set_brightness)} />
        </label>
        <label htmlFor="led_delay_duration">
          Delay:
          <input type="number" placeholder="0" name="led_delay_duration" id="led_delay_duration" value={delay_duration} onChange={unwrap(set_delay)}/>
          ms
        </label>
        <label htmlFor="led_fade_duration">
          Fade:
          <input type="number" placeholder="0" name="led_fade_duration" id="led_fade_duration" value={fade_duration} onChange={unwrap(set_fade)}/>
          ms
        </label>
        <div>
          Native Pickr:
          <br/>
          <input type="color" name="color_display" id="color_display" value={hex_value} onChange={unwrap(set_display_color)}/>
        </div>
      </div>
    </div>
  );
}

export { LedCtrl };
