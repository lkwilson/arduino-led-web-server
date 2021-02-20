import React, {  } from 'react';

import { ModeCtrl } from './ctrls/mode_ctrl';
import { LedCtrl } from './ctrls/leds_ctrl';
import { StateContextProvider } from './contexts/state_context';

function App() {
  return (
    <StateContextProvider>
      <ModeCtrl />
      <LedCtrl />
    </StateContextProvider>
  );
}

export { App };