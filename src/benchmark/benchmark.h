#ifndef GIST_BENCHMARK_BENCHMARK_H_
#define GIST_BENCHMARK_BENCHMARK_H_

#include "gist/gist.h"
#include "gist/predicate.h"

#define BENCHMARK_ERROR "Benchmark ERROR: "

class Benchmark {
public:
    enum Type {NONE, B_TREE_BENCHMARK, R_TREE_BENCHMARK};

    Benchmark(Type type, const unsigned int thread_count);
    virtual ~Benchmark();
    void Run();

private:
    enum State {IDLE, POPULATING, READY, MEASURING, FINISHED};

    Predicate* GeneratePredicate();
    char* GenerateData();
    void PopulationThreadFunction();
    void MeasurementThreadFunction();
    void Populate();
    void Measure();

    Type type_ = Type::NONE;
    State state_ = State::IDLE;
    Gist* gist_ = nullptr;
    unsigned int thread_count_ = 0;

    const unsigned int kMeasureTime = 3;
};

#endif  // GIST_BENCHMARK_BENCHMARK_H_
