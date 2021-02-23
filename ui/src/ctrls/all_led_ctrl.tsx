import React, { useState, useEffect, useContext } from 'react';
import { LedsContext } from '../contexts/leds_context';
import { OnlineContext } from '../contexts/online_context';

import { rgb_to_hex } from '../utils/utils';

function AllLeds(props) {
  const { set_color } = props;
  const { leds, refresh_leds } = useContext(LedsContext);

  const { online } = useContext(OnlineContext)

  function handle_led_selected(event, index) {
    event.preventDefault();
    const { red, green, blue } = leds[index];
    set_color({ red, green, blue });
  }

  let display_leds = online ? "Loading..." : "Offline";
  if (leds != null && leds.length !== 0) {
    display_leds = leds.map((led, index) => {
      const { red, green, blue } = led;
      const hex_color = rgb_to_hex({red, green, blue});
      const key = `led_number_${index}`;

      return (
        <div key={key} onClick={event => handle_led_selected(event, index)}>
          <div>{hex_color.toUpperCase()}</div>
          <input
              type="color"
              value={hex_color}
              disabled
              />
        </div>
      );
    });
  }

  return (
    <div className="container-column">
      <h1 className="section-title">All Lights</h1>
      <div className="container-row justify-space-evenly">
        {display_leds}
      </div>
    </div>
  );
}

export {
  AllLeds,
};
