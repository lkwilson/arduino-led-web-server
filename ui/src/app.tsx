import React from 'react';

import { ModeCtrl } from './ctrls/mode_ctrl';
import { LedCtrl } from './ctrls/led_ctrl';
import { AllLeds } from './ctrls/all_led_ctrl';

function App() {
  return (
    <>
      <ModeCtrl />
      <LedCtrl />
      <AllLeds />
    </>
  );
}

export { App };