#ifndef GIST_BENCHMARK_TIMER_H_
#define GIST_BENCHMARK_TIMER_H_

#include <chrono>

class Timer {
public:
    Timer() {
        Reset();
    }

    void Reset() {
        start_ = std::chrono::high_resolution_clock::now();
    }

    template<typename TimeUnit>
    double Elapsed() {
        auto duration = std::chrono::duration_cast<TimeUnit>(std::chrono::high_resolution_clock::now() - start_);
        return duration.count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;

};

#endif  // GIST_BENCHMARK_TIMER_H_
