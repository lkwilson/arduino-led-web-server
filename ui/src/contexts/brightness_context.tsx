import React, { createContext, useEffect, useState } from 'react';
import { get_brightness } from '../utils/api_calls';

const BrightnessContext = createContext(null);

function BrightnessContextProvider(props) {
  const { children } = props;

  const [brightness, set_brightness] = useState(null);

  function refresh_brightness() {
    get_brightness()
        .then(data => {
          set_brightness(data.brightness);
        })
        .catch(err => {
          console.error(err);
        });
  }

  useEffect(_ => {
    refresh_brightness();
  }, []);

  const brightness_state = {
    brightness,
    refresh_brightness,
  }

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
