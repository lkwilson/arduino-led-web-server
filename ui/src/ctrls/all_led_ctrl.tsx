import React, { useState, useEffect } from 'react';

function AllLeds() {
  const [leds, set_leds] = useState([]);

  useEffect(_ => {
    // Load from API
  }, []);

  return (<h1>Coming soon!</h1>);
}

export {
  AllLeds,
};
