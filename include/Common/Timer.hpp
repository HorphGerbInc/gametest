
#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <cstdint>

/**
 * @brief Denotes milliseconds.
 *
 */
const int Milliseconds = 1;
/**
 * @brief Denotes Seconds in terms of Milliseconds.
 *
 */
const int Seconds = 1000 * Milliseconds;
/**
 * @brief Denotes Minutes in terms of Milliseconds
 *
 */
const int Minutes = 60 * Seconds;
/**
 * @brief Denotes Hours in terms of Milliseconds
 *
 */
const int Hours = 60 * Minutes;
/**
 * @brief Denotes Days in terms of Milliseconds
 *
 */
const int Days = 24 * Hours;

namespace jerobins {
  namespace common {
    /**
     * @brief Basic timer class.
     *
     */
    class Timer {
    public:
      /**
       * @brief Create a timer set to 0.
       *
       */
      Timer();

      /**
       * @brief Start the timer.
       *
       */
      void Start();

      /**
       * @brief Stop the timer.
       *
       */
      void Stop();

      /**
       * @brief Reset the timer to 0.
       *
       */
      void Reset();

      /**
       * @brief Returns the duration of the timer.
       *
       * @return uint64_t The current duration in milliseconds.
       */
      uint64_t Duration();

    private:
      bool running;
      uint64_t start;
      uint64_t duration;
    };
  } // namespace common
} // namespace jerobins
#endif