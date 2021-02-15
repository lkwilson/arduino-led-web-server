function unwrap_event(cb) {
  return event => cb(event.target.value);
}

export { unwrap_event };
