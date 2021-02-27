import React, { useContext, useState, useEffect } from 'react';
import '../utils/utils.css';
import './mode_ctrl.css'
import { unwrap, unwrap_num } from '../utils/utils';
import { post_mode } from '../utils/api_calls';
import { ModeContext } from '../contexts/mode_context';

function parse_number_input(event) {
  const value = event.target.value;
  if (value == null || value === "") {
    return "";
  } else {
    return Math.max(0, Math.round(Number(value)));
  }
}

function ModeCtrl() {
  const [ name, set_name ] = useState("");
  const [ random_type, set_random_type ] = useState("");
  const [ random_delay_duration, set_random_delay_duration ] = useState("");
  const [ random_fade_duration, set_random_fade_duration ] = useState("");

  const { mode, refresh_mode } = useContext(ModeContext);

  useEffect(_ => {
    if (mode != null) {
      if (name !== mode.name) {
        set_name(mode.name);
      }
      if (mode.name === "IDLE") {
        // no idle state
      } else if (mode.name === "RANDOM") {
        if (random_type !== mode.type) {
          set_random_type(mode.type)
        }
        if (random_delay_duration !== mode.delay_duration) {
          set_random_delay_duration(mode.delay_duration);
        }
        if (random_fade_duration !== mode.fade_duration) {
          if (mode.fade_duration === 0) {
            set_random_fade_duration("");
          } else {
            set_random_fade_duration(mode.fade_duration);
          }
        }
      }
    }
  }, [mode]);

  function set_random_delay(event) {
    set_random_delay_duration(parse_number_input(event));
  }

  function set_random_fade(event) {
    set_random_fade_duration(parse_number_input(event));
  }

  function update_mode_random_handler() {
    if (name === "IDLE") {
      post_mode(name, {})
    } else if (name === "RANDOM") {
      if (random_type === "") {
        console.log("No random type selected");
        return;
      }
      const config = {
        type: random_type,
      };
      if (random_delay_duration === "") {
        config['delay_duration'] = 0;
      } else {
        config['delay_duration'] = Number(random_delay_duration);
      }
      if (random_fade_duration === "") {
        config['fade_duration'] = 0;
      } else {
        config['fade_duration'] = Number(random_fade_duration);
      }
      post_mode(name, config)
    } else {
      console.log("No mode selected");
    }
  }

  return (
    <>
      <h1 className="section-title">Modes</h1>
      <div className="mode-list">
        <label htmlFor="idle_mode" className="mode-card">
          <input type="radio" name="name" id="idle_mode" value="IDLE" onChange={unwrap(set_name)} checked={name==="IDLE"}/>
          <div className="mode-options">
            <h2>Idle</h2>
          </div>
        </label>
        <label htmlFor="random_mode" className="mode-card">
          <input type="radio" name="name" id="random_mode" value="RANDOM" onChange={unwrap(set_name)} checked={name==="RANDOM"}/>
          <div className="mode-options">
            <h2 className="mode-title">Random</h2>
            <label htmlFor="random_type_uniform" className="mode-radio-option">
              Uniform
              <br/>
              <input type="radio" name="random_type" id="random_type_uniform" value="UNIFORM" onChange={unwrap(set_random_type)} checked={random_type==="UNIFORM"}/>
            </label>
            <label htmlFor="random_type_individual" className="mode-radio-option">
              Individual
              <br/>
              <input type="radio" name="random_type" id="random_type_individual" value="INDIVIDUAL" onChange={unwrap(set_random_type)} checked={random_type==="INDIVIDUAL"}/>
            </label>
            <label htmlFor="random_delay_duration">Delay (ms):</label>
            <input type="number" placeholder="0" name="random_delay_duration" id="random_delay_duration" value={random_delay_duration} onChange={set_random_delay}/>
            <label htmlFor="random_fade_duration">Fade (ms):</label>
            <input type="number" placeholder="0" name="random_fade_duration" id="random_fade_duration" value={random_fade_duration} onChange={set_random_fade}/>
          </div>
        </label>
      </div>
      <div className="update-button" onClick={update_mode_random_handler}>Update</div>
    </>
  );
}

export { ModeCtrl };
