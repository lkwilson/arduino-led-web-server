import React, { useEffect, useRef } from 'react';

import Pickr from '@simonwep/pickr';
import '@simonwep/pickr/dist/themes/monolith.min.css';

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
      theme: "monolith",
      inline: true,
      default: default_color, 
      showAlways: true,
      //position: 'top-middle',
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
        preview: true,
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

export {
  ColorPickrWrapper,
};
