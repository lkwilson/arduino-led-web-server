import React from 'react';
import { createContext, useState, useEffect } from 'react';

const LedsContext = createContext(null);

function LedsContextProvider(props) {
  const { children } = props;
  const [leds, set_leds] = useState([]);

  // load state
  useEffect(_ => {
    const new_leds = [1, 2, 3, 4, 5, 6].map(red => (
      {
        index: 0,
        red: red*40,
        green: 20,
        blue: 30,
      }
    ));
    const timer = setTimeout(_ => {
      set_leds(new_leds);
    }, 1000);
    return _ => clearTimeout(timer);
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
