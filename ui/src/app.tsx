import React, {  } from 'react';

import './app.css';

import { ModeCtrl } from './ctrls/mode_ctrl';
import { LedCtrl } from './ctrls/leds_ctrl';
import { StateContextProvider } from './contexts/state_context';
import { AllLedsCtrl } from './ctrls/all_led_ctrl';

function App() {
  return (
    <StateContextProvider>
      <LedCtrl />
      <ModeCtrl />
      {/*<AllLedsCtrl />*/}
    </StateContextProvider>
  );
}

export { App };