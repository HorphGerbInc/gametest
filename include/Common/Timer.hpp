
#ifndef _TIMER_HPP_
#define _TIMER_HPP_

namespace jerobins {
  namespace common {
    class Timer {
    public:
        Timer();
        void Start();
        void Stop();
        void Reset();
        uint64_t Duration();

    private:
        bool running;
        uint64_t start;
        uint64_t duration;
    };
  }
}
#endif