import React, {  } from 'react';

import { ModeCtrl } from './ctrls/mode_ctrl';
import { LedCtrl } from './ctrls/leds_ctrl';
import { LedsContextProvider } from './contexts/leds_context';

function App() {
  return (
    <LedsContextProvider>
      <ModeCtrl />
      <LedCtrl />
    </LedsContextProvider>
  );
}

export { App };