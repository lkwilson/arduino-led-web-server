import { h, createContext } from 'preact';
import { useState, useEffect } from 'preact/hooks';
import { get_led } from '../utils/api_calls';

const LedsContext = createContext(null);

function LedsContextProvider({ children }) {
  const [leds, set_leds] = useState([]);

  function refresh_leds() {
    get_led()
        .then(response => {
          // TODO: This needs to be fixed server side. and probably also made
          // resilient on client side.
          //set_leds(response.data);
        })
        .catch(error => {
          console.error(error);
        });
  }

  // load state
  useEffect(() => {
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
