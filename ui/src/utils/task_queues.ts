function build_single_task_queue() {
  let current_task = null;

  function add_task(task) {
    if (current_task !== null) {
      clearTimeout(current_task);
    }
    current_task = setTimeout(task);
  }

  return add_task;
}

function build_single_microtask_queue() {
  let current_microtask = null;
  let queue = Promise.resolve();

  function add_microtask(callback) {
    current_microtask = callback;
    queue = queue.then(() => {
      if (current_microtask !== null) {
        current_microtask();
        current_microtask = null;
      }
    });
  }

  return add_microtask;
}

export {
  build_single_task_queue,
  build_single_microtask_queue,
};
