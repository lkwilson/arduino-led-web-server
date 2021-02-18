import React, { useState, useEffect } from 'react';

function AllLeds() {
  const [leds, set_leds] = useState([]);

  useEffect(_ => {
    // Load from API
  }, []);

  return (
    <div className="container-column">
      <h1 className="section-title">All Lights</h1>
      <p>Coming soon!</p>
    </div>
  );
}

export {
  AllLeds,
};
