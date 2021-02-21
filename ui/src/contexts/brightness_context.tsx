import { h, createContext } from 'preact';
import { useEffect, useState } from 'preact/hooks';
import { get_brightness } from '../utils/api_calls';

const BrightnessContext = createContext(null);

function BrightnessContextProvider({ children }) {
  const [brightness, set_brightness] = useState(null);

  function refresh_brightness() {
    get_brightness()
        .then(response => {
          set_brightness(response.data.brightness);
        })
        .catch(err => {
          console.error(err);
        });
  }

  useEffect(() => {
    refresh_brightness();
  }, []);

  const brightness_state = {
    brightness,
    refresh_brightness,
  };

  return (
    <BrightnessContext.Provider value={brightness_state}>
      {children} 
    </BrightnessContext.Provider>
  );
}

export {
  BrightnessContext,
  BrightnessContextProvider,
};
