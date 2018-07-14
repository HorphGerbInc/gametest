
#ifndef _LOCK_HPP_
#define _LOCK_HPP_

#include <mutex>

namespace jerobins {
  namespace sync {
    /**
     * @brief Lock class which should only be created on the stack.
     *
     */
    class Lock {
    public:
      /**
       * @brief Takes a mutex and locks it.
       *
       * @param mutex Mutex to use.
       */
      Lock(std::mutex &mutex) : m(mutex) { m.lock(); }

      /**
       * @brief Releases the mutex.
       *
       */
      ~Lock() { m.unlock(); }

    private:
      Lock();
      std::mutex &m;
    };
  } // namespace Sync
} // namespace jerobins

#endif