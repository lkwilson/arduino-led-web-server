import React, { createContext, useState, useEffect } from 'react';
import { ModeConfig } from '../utils/api_calls';

const ModeContext = createContext(null);

function ModeContextProvider(props) {
  const { children } = props;

  const [mode, set_mode] = useState(null);

  useEffect(_ => {
    const new_mode: ModeConfig = {
      name: "RANDOM",
      type: "INDIVIDUAL",
      delay_duration: 100,
      fade_duration: 500,
    };

    const timer = setTimeout(_ => {
      set_mode(new_mode);
    }, 1000);

    return _ => clearTimeout(timer);
  }, [])

  return (
    <ModeContext.Provider value={mode}>
      {children}
    </ModeContext.Provider>
  );
}

export { ModeContext, ModeContextProvider };
