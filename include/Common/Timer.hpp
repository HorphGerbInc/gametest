
#ifndef _TIMER_HPP_
#define _TIMER_HPP_


const int Milliseconds = 1;
const int Seconds = 1000 * Milliseconds;
const int Minutes = 60 * Seconds;
const int Hours = 60 * Minutes;
const int Days = 24 * Hours;


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