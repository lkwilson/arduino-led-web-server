import React from 'react';
import { createContext, useState, useEffect } from 'react';
import { get_led } from '../utils/api_calls';

const LedsContext = createContext(null);

function LedsContextProvider(props) {
  const { children } = props;
  const [leds, set_leds] = useState([]);

  function refresh_leds() {
    get_led()
        .then(response => {
          console.log(response.data);
          set_leds(response.data);
        })
        .catch(error => {
          console.error(error);
        });
  }

  // load state
  useEffect(_ => {
    refresh_leds();
  }, []);

  const leds_state = {
    leds,
    refresh_leds,
  };

  return (
    <LedsContext.Provider value={leds_state}>
      {children}
    </LedsContext.Provider>
  );
}

export {
  LedsContext,
  LedsContextProvider,
};
