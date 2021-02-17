import React, { useState, useEffect, useRef } from 'react';
import { unwrap, unwrap_num, rgb_to_hex, hex_to_rgb } from '../utils/utils';
import Pickr from '@simonwep/pickr';
import '@simonwep/pickr/dist/themes/classic.min.css';

function ColorPickrWrapper(props) {
  const { color, set_color } = props;
  const pickr_ref = useRef(null);

  // Mount color picker
  useEffect(_ => {
    const { red, green, blue } = color;
    const default_color = `rgb(${[red, green, blue].join(', ')})`;

    // Add color pickr to dom
    const pickr = Pickr.create({
      el: "#advanced_color_picker",
      theme: "classic",
      inline: true,
      default: default_color, 
      swatches: [
        'rgb(244, 67, 54)',
        'rgb(233, 30, 99)',
        'rgb(156, 39, 176)',
        'rgb(103, 58, 183)',
        'rgb(63, 81, 181)',
        'rgb(33, 150, 243)',
        'rgb(3, 169, 244)',
        'rgb(0, 188, 212)',
        'rgb(0, 150, 136)',
        'rgb(76, 175, 80)',
        'rgb(139, 195, 74)',
        'rgb(205, 220, 57)',
        'rgb(255, 235, 59)',
        'rgb(255, 193, 7)',
      ],
      components: {
        preview: false,
        hue: true,
      }
    });
    pickr_ref.current = pickr;

    // On color update, set color
    pickr.on('change', _ => pickr.applyColor());
    pickr.on('save', color => {
      if (color != null) {
        const [ red, green, blue, _ ] = color.toRGBA();
        set_color({ red, green, blue });
      }
    });

    // Remove pickr from dom
    return _ => pickr.destroyAndRemove();
  }, []);

  useEffect(_ => {
    const pickr = pickr_ref.current;
    if (pickr == null) {
      return;
    }

    const { red, green, blue } = color;
    const [ current_red, current_green, current_blue ] = pickr.getColor().toRGBA();
    const red_changed = red !== current_red;
    const green_changed = green !== current_green;
    const blue_changed = blue !== current_blue;
    if (red_changed || green_changed || blue_changed) {
      const new_color = `rgb(${[red, green, blue].join(', ')})`;
      pickr.setColor(new_color);
    }
  }, [color]);

  return (
    <div className="container-column" style={{alignItems: "center"}}>
      <div id="advanced_color_picker" />
    </div>
  );
}

function LedCtrl() {
  const [color, set_color] = useState({ red: 0, green: 0, blue: 0 });
  const [brightness, set_brightness] = useState(255);
  const [delay_duration, set_delay_duration ] = useState("");
  const [fade_duration, set_fade_duration ] = useState("");

  const int_color = {
    red: Math.round(color.red),
    green: Math.round(color.green),
    blue: Math.round(color.blue),
  };
  const set_red = red => set_color({ ...int_color, red });
  const set_green = green => set_color({ ...int_color, green });
  const set_blue = blue => set_color({ ...int_color, blue });

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
        <label htmlFor="color_display">
          Color: {hex_value}
          <input type="color" name="color_display" id="color_display" value={hex_value} onChange={unwrap(set_display_color)}/>
        </label>
        <label htmlFor="red_slider">
          Red: {red} {red.toString(16)}
          <input type="range" min="0" max="255" name="red_slider" id="red_slider" value={red} onChange={unwrap_num(set_red)} />
        </label>
        <label htmlFor="green">
          Green: {green} {green.toString(16)}
          <input type="range" min="0" max="255" name="green" id="green" value={green} onChange={unwrap_num(set_green)} />
        </label>
        <label htmlFor="blue">
          Blue: {blue} {blue.toString(16)}
          <input type="range" min="0" max="255" name="blue" id="blue" value={blue} onChange={unwrap_num(set_blue)} />
        </label>
        <label htmlFor="brightness">
          Brightness: {brightness} {Math.round(brightness / 255 * 100)}%
          <input type="range" min="0" max="255" name="brightness" id="brightness" value={brightness} onChange={unwrap_num(set_brightness)} />
        </label>
        <label htmlFor="led_delay_duration">
          Delay:
          <input type="number" placeholder="0" name="led_delay_duration" id="led_delay_duration" value={delay_duration} onChange={unwrap_num(set_delay_duration)}/>
          ms
        </label>
        <label htmlFor="led_fade_duration">
          Fade:
          <input type="number" placeholder="0" name="led_fade_duration" id="led_fade_duration" value={fade_duration} onChange={unwrap_num(set_fade_duration)}/>
          ms
        </label>
        <ColorPickrWrapper color={color} set_color={set_color} />
      </div>
    </div>
  );
}

export { LedCtrl };
