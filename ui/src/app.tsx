import React from 'react';

import { ModeCtrl } from './ctrls/mode_ctrl';
import { LedCtrl } from './ctrls/led_ctrl';

function App() {
  return (
    <>
      <ModeCtrl />
      <LedCtrl />
    </>
  );
}

export { App };