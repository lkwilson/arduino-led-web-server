import React from 'react';
import { createContext, useState, useEffect } from 'react';

const LedsContext = createContext(null);

function LedsContextProvider({ children }) {
  const [leds, set_leds] = useState([]);

  // load state
  useEffect(_ => {
    let timer = null;
    timer = setTimeout(_ => {
      const new_leds = [
        {
          index: 0,
          red: 10,
          green: 20,
          blue: 30,
        }
      ];
      set_leds(new_leds);

      timer = null;
    }, 1000);

    return _ => {
      if (timer != null) {
        clearTimeout(timer);
      }
    }
  }, []);

  return (
    <LedsContext.Provider value={leds}>
      {children}
    </LedsContext.Provider>
  );
}

export {
  LedsContext,
  LedsContextProvider,
};
