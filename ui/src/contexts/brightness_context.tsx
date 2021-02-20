import React, { createContext, useEffect, useState } from 'react';

const BrightnessContext = createContext(null);

function BrightnessContextProvider(props) {
  const { children } = props;

  const [brightness, set_brightness] = useState(null);

  useEffect(_ => {
    const new_brightness = 230;
    const timer = setTimeout(_ => {
      set_brightness(new_brightness);
    }, 1000);
    return _ => clearTimeout(timer);
  }, []);

  return (
    <BrightnessContext.Provider value={brightness}>
      {children}
    </BrightnessContext.Provider>
  );
}

export {
  BrightnessContext,
  BrightnessContextProvider,
};
