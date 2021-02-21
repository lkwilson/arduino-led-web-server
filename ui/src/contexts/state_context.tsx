import { h } from 'preact';
import { ModeContextProvider } from './mode_context';
import { LedsContextProvider } from './leds_context';
import { BrightnessContextProvider } from './brightness_context';

function StateContextProvider({ children }) {
  return (
    <BrightnessContextProvider>
      <ModeContextProvider>
        <LedsContextProvider>
          {children}
        </LedsContextProvider>
      </ModeContextProvider>
    </BrightnessContextProvider>
  )
}

export {
  StateContextProvider,
};
