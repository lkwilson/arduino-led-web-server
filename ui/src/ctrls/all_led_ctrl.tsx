import React, { useState, useEffect, useContext } from 'react';
import { LedsContext } from '../contexts/leds_context';

import { rgb_to_hex } from '../utils/utils';

function AllLeds(props) {
  const { set_color } = props;
  const leds = useContext(LedsContext);

  function handle_led_selected(index) {
    const { red, green, blue } = leds[index];
    set_color({ red, green, blue });
  }

  let display_leds = null;
  if (leds != null && leds.length !== 0) {
    display_leds = leds.map(led => {
      const { index, red, green, blue } = led;
      const hex_color = rgb_to_hex({red, green, blue});
      const key = `led_number_${index}`;
      const style = {
        background: hex_color,
        borderRadius: "1px",
      }

      return (
        <div
            key={key}
            style={style}
            onClick={_ => handle_led_selected(index)} >
          Led #{index}
        </div>
      );
    });
  }


  return (
    <div className="container-column">
      <h1 className="section-title">All Lights</h1>
      <p>Coming soon!</p>
      {display_leds}
    </div>
  );
}

export {
  AllLeds,
};
