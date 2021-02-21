import React, { useContext, useState, useEffect } from 'react';
import '../utils/utils.css';
import './mode_ctrl.css'
import { unwrap, unwrap_num } from '../utils/utils';
import { post_mode } from '../utils/api_calls';
import { ModeContext } from '../contexts/mode_context';

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

  function update_mode_random_handler() {
    console.log("Setting name:");
    console.log({ name, random_type, random_delay_duration, random_fade_duration });
    if (name === "IDLE") {
      post_mode(name, {})
          .then(resp => console.log({ resp }))
          .catch(error => console.log({ error }));
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
        config['delay_duration'] = Number(random_fade_duration);
      }
      post_mode(name, config)
          .then(resp => console.log({ resp }))
          .catch(error => console.log({ error }));
    } else {
      console.log("No mode selected");
    }
  }

  return (
    <div className="container-column">
      <h1 className="section-title">Modes</h1>
      <div className="container-row mode-form">
        <label htmlFor="idle_mode" className="mode-card">
          <input type="radio" name="name" id="idle_mode" value="IDLE" onChange={unwrap(set_name)} checked={name==="IDLE"}/>
          <div>
            <h1>Idle</h1>
          </div>
        </label>
        <label htmlFor="random_mode" className="mode-card">
          <input type="radio" name="name" id="random_mode" value="RANDOM" onChange={unwrap(set_name)} checked={name==="RANDOM"}/>
          <div className="container-column form-align">
            <h1>Random</h1>
            <div className="container-column">
              <p>Type</p>
              <label htmlFor="random_type_uniform">
                <input type="radio" name="random_type" id="random_type_uniform" value="UNIFORM" onChange={unwrap(set_random_type)} checked={random_type==="UNIFORM"}/>
                Uniform
              </label>
              <label htmlFor="random_type_individual">
                <input type="radio" name="random_type" id="random_type_individual" value="INDIVIDUAL" onChange={unwrap(set_random_type)} checked={random_type==="INDIVIDUAL"}/>
                Individual
              </label>
            </div>
            <label htmlFor="random_delay_duration">
              Delay:
              <input type="number" placeholder="0" name="random_delay_duration" id="random_delay_duration" value={random_delay_duration} onChange={unwrap_num(set_random_delay_duration)}/>
              ms
            </label>
            <label htmlFor="random_fade_duration">
              Fade:
              <input type="number" placeholder="0" name="random_fade_duration" id="random_fade_duration" value={random_fade_duration} onChange={unwrap_num(set_random_fade_duration)}/>
              ms
            </label>
          </div>
        </label>
        <label htmlFor="update_mode_random">
          <input type="button" value="Update" className="update-button" onClick={update_mode_random_handler} />
        </label>
      </div>
    </div>
  );
}

export { ModeCtrl };
