interface TaskResult<T> {
  result: T,
}

function ignore_task_results<T>(results: Promise<TaskResult<T>>) {
  results.then(({result}) => {
    Promise.resolve(result).then(() => {}).catch(() => {});
  }).catch(() => {});
}

function log_task_results<T>(id: string, results: Promise<TaskResult<T>>) {
  results.then(({result}) => {
    console.log(`Task ${id} was run:`);
    Promise.resolve(result)
        .then(result_value => {
          console.log(`Task ${id} resolved:`, result_value);
        })
        .catch(error => {
          console.log(`Task ${id} rejected:`, error);
        });
  }).catch(() => {
    console.log(`Task ${id} cancelled`);
  });
}

function build_single_task_queue() {
  let current_task: number|null = null;
  let current_reject: (reason?: any) => void;

  function add_task<T>(task: () => T): Promise<TaskResult<T>> {
    return new Promise((resolve, reject) => {
      if (current_task !== null) {
        clearTimeout(current_task);
        current_reject();
      }

      current_task = setTimeout(() => {
        resolve({ result: task() });
      });
      current_reject = reject;
    });
  }

  return add_task;
}

function build_single_microtask_queue() {
  let cancel_microtask = null;

  function add_microtask<T>(callback: () => T): Promise<TaskResult<T>> {
    return new Promise((resolve, reject) => {
      if (cancel_microtask !== null) {
        cancel_microtask();
      }

      let cancelled = false;
      cancel_microtask = () => {
        cancelled = true;
      }

      Promise.resolve().then(() => {
        if (cancelled) {
          reject();
        } else {
          resolve({ result: callback() });
        }
      });
    });
  }

  return add_microtask;
}

// If the task returns a promise, then the next task won't run until the task
// resolves.
function build_single_promise_queue() {
  let last_task = Promise.resolve();
  let last_task_cancel = null;

  function add_promise<T>(callback: () => Promise<T>) {
    if (last_task_cancel !== null) {
      last_task_cancel();
    }

    let cancelled = false;
    last_task_cancel = () => {
      cancelled = true;
    };

    return new Promise((resolve, reject) => {
      last_task.then(() => {
        if (cancelled) {
          reject();
        } else {
          const result = callback();
          last_task = result.then(() => {}).catch(() => {});
          resolve({ result });
        }
      });
    })
  }

  return add_promise;
}

export {
  build_single_task_queue,
  build_single_microtask_queue,
  build_single_promise_queue,
  ignore_task_results,
  log_task_results,
};
