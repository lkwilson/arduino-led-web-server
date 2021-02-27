import React, { useEffect, useRef } from 'react';

import Pickr from '@simonwep/pickr';
import '@simonwep/pickr/dist/themes/monolith.min.css';
import { build_single_microtask_queue, ignore_task_results, log_task_results } from './task_queues';

/*
The change event is triggered when manually set or when actually picked by
the user. This makes it difficult to differentiate. However, if a change
event is triggered and the color matches the state color, then the update was
manual. If a change event is triggered and the color doesn't match, then the
user just picked a color.
*/

function color_to_pickr_string(color) {
  const { red, green, blue } = color;
  return `rgb(${red}, ${green}, ${blue})`;
}

function report_change_id(changed, changed_color, updated, updated_color) {
  return `${changed} changed (${color_to_pickr_string(changed_color)}). Updating ${updated} (${color_to_pickr_string(updated_color)})`;
}

function initialize_pickr(default_color) {
  return Pickr.create({
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
}

function are_colors_equal(lhs, rhs) {
  return (
    lhs.red === rhs.red &&
    lhs.green === rhs.green &&
    lhs.blue === rhs.blue
  );
}

function ColorPickrWrapper({ color, set_color }) {
  const color_updates_ref = useRef(build_single_microtask_queue());
  const set_color_ref = useRef();
  set_color_ref.current = new_color => {
    if (!are_colors_equal(color, new_color)) {
      const res = color_updates_ref.current(() => {
        set_color(new_color);
      });
      //log_task_results(report_change_id("pickr", new_color, "state", color), res);
      ignore_task_results(res);
    }
  };

  // Mount picker
  const pickr_ref = useRef(null);
  useEffect(() => {
    // Add pickr to dom
    const default_color = color_to_pickr_string(color)
    const pickr = initialize_pickr(default_color);
    pickr_ref.current = pickr;

    // On change update state
    pickr.on('change', () => pickr.applyColor());
    pickr.on('save', new_color => {
      if (new_color != null) {
        const [ red, green, blue ] = new_color.toRGBA();
        set_color_ref.current({ red, green, blue });
      }
    });

    // Remove pickr from dom
    return () => pickr.destroyAndRemove();
  }, []);

  useEffect(() => {
    const pickr = pickr_ref.current;
    if (pickr === null) {
      return;
    }

    const [ red, green, blue ] = pickr.getColor().toRGBA();
    const old_color = { red, green, blue };
    if (!are_colors_equal(old_color, color)) {
      //console.log(report_change_id("state", color, "pickr", old_color))
      pickr.setColor(color_to_pickr_string(color));
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
