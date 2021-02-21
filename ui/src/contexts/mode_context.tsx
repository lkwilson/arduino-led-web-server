import React, { createContext, useState, useEffect } from 'react';
import { get_mode } from '../utils/api_calls';

const ModeContext = createContext(null);

function ModeContextProvider(props) {
  const { children } = props;

  const [mode, set_mode] = useState(null);

  function refresh_mode() {
    get_mode()
        .then(response => {
          set_mode(response.data);
        })
        .catch(error => {
          console.error(error);
        })
  }

  useEffect(_ => {
    refresh_mode();
  }, [])

  const mode_state = {
    mode,
    refresh_mode,
  }

  return (
    <ModeContext.Provider value={mode_state}>
      {children}
    </ModeContext.Provider>
  );
}

export { ModeContext, ModeContextProvider };
