#ifndef GIST_BENCHMARK_BENCHMARK_H_
#define GIST_BENCHMARK_BENCHMARK_H_

#include <random>
#include <cygwin/stat.h>

#include "gist/gist.h"
#include "gist/predicate.h"

#define BENCHMARK_ERROR "Benchmark ERROR: "

class Benchmark {
public:
    enum Type {NONE, B_TREE_BENCHMARK, R_TREE_BENCHMARK};

    Benchmark(Type type, const uint32_t thread_count);
    virtual ~Benchmark();
    void Run();

private:
    enum State {IDLE, POPULATING, READY, MEASURING, FINISHED};

    Predicate *GeneratePredicate();
    char *GenerateData();
    void PopulationThreadFunction();
    void MeasurementThreadFunction();
    void Populate();
    void Measure();

    const uint32_t kMeasureTime = 3;
    const uint32_t kDataLength = 32; // TODO: dynamic?
    const char kDataCharacters[62] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    const uint32_t kRngSeed = 0;

    Type type_ = Type::NONE;
    State state_ = State::IDLE;
    Gist *gist_ = nullptr;
    uint32_t thread_count_ = 0;
    std::mt19937 rng;
    std::uniform_int_distribution<uint32_t> data_distribution{std::uniform_int_distribution<uint32_t>(0, (sizeof(kDataCharacters) / sizeof(char)) - 1)};
};

#endif  // GIST_BENCHMARK_BENCHMARK_H_
