import React from 'react';
import { ModeContextProvider } from './mode_context';
import { LedsContextProvider } from './leds_context';
import { BrightnessContextProvider } from './brightness_context';
import { OnlineContextProvider } from './online_context';

function StateContextProvider(props) {
  const { children } = props;
  return (
    <OnlineContextProvider>
      <BrightnessContextProvider>
        <ModeContextProvider>
          <LedsContextProvider>
            {children}
          </LedsContextProvider>
        </ModeContextProvider>
      </BrightnessContextProvider>
    </OnlineContextProvider>
  );
}

export {
  StateContextProvider,
};
