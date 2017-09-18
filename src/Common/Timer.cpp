
#include <chrono>
using namespace std::chrono;

#include <Common/Timer.hpp>

namespace jerobins {
  namespace common {
    Timer::Timer() {
      running = false;
      start = 0;
      duration = 0;
    }

    void Timer::Start() {
      auto now = high_resolution_clock::now();
      start = duration_cast<nanoseconds>(now.time_since_epoch()).count();
      running = true;
    }

    void Timer::Stop() {
      auto now = high_resolution_clock::now();
      auto ticks = duration_cast<nanoseconds>(now.time_since_epoch()).count();
      running = false;
      duration = ticks - start;
    }

    void Timer::Reset() { duration = 0; }

    uint64_t Timer::Duration() {
      if (running) {
        auto now = high_resolution_clock::now();
        auto ticks = duration_cast<nanoseconds>(now.time_since_epoch()).count();
        duration = ticks - start;
      }
      return duration;
    }
  }
}
