import React, { createContext, useState, useEffect } from 'react';
import { is_connected } from '../utils/api_calls';

const OnlineContext = createContext(null);
const one_second = 1000;
const five_minutes = 5 * 60 * one_second;

function OnlineContextProvider(props) {
  const { children } = props;
  const [online, set_online] = useState(true);
  const [retry_timeout, set_retry_timeout] = useState(one_second);

  function refresh_online() {
    is_connected()
        .then(connected => {
          if (online !== connected) {
            set_online(connected);
          }
        });
  }

  useEffect(_ => {
    const timer = setInterval(() => {
      refresh_online();
      const max_retry_timeout = online ? one_second : five_minutes;
      const new_retry_timeout = Math.min(max_retry_timeout, retry_timeout * 2);
      if (new_retry_timeout !== retry_timeout) {
        set_retry_timeout(new_retry_timeout);
      }
    }, retry_timeout);
    return _ => clearInterval(timer);
  }, [retry_timeout, online]);

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
