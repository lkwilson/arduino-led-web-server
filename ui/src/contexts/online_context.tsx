import React, { createContext, useState, useEffect } from 'react';
import { is_connected } from '../utils/api_calls';

const OnlineContext = createContext(null);

function OnlineContextProvider(props) {
  const { children } = props;
  const [online, set_online] = useState(true);

  function refresh_online() {
    is_connected()
        .then(connected => {
          if (online !== connected) {
            set_online(connected);
          }
        });
  }

  useEffect(_ => {
    const timer = setInterval(refresh_online, 1000);
    return _ => clearInterval(timer);
  }, []);

  const online_state = {
    online,
    refresh_online,
  };

  return (
    <OnlineContext.Provider value={online_state}>
      {children}
    </OnlineContext.Provider>
  );
}

export {
  OnlineContext,
  OnlineContextProvider,
};
