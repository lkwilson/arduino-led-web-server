import { h, createContext } from 'preact';
import { useState, useEffect } from 'preact/hooks';
import { get_mode } from '../utils/api_calls';

const ModeContext = createContext(null);

function ModeContextProvider({ children }) {
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

  useEffect(() => {
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
