#include "benchmark/benchmark.h"

#include <thread>

#include "easylogging++.h"
#include "timer.h"

Benchmark::Benchmark(Type type, const uint32_t thread_count) {
    type_ = type;
    switch (type_) {
        case Type::B_TREE_BENCHMARK:
            // gist_ = new BTreeGist();
            LOG(INFO) << "Benchmark: Tree type - B+ Tree.";
            break;
        case Type::R_TREE_BENCHMARK:
            // gist_ = new RTreeGist();
            LOG(INFO) << "Benchmark: Tree type - R Tree.";
            break;
        default:
            LOG(FATAL) << "Benchmark: Unknown tree type.";
    }
    thread_count_ = thread_count;
    rng.seed(kRngSeed);
}

Benchmark::~Benchmark() {
    if (gist_ != nullptr) {
        delete gist_;
    }
}

void Benchmark::Run() {
    CHECK_EQ(state_, State::IDLE) << BENCHMARK_ERROR << "Wrong state on Run()";
    LOG(INFO) << "Benchmark: Running ";
    Populate();
    Measure();
}

void Benchmark::Populate() {
    CHECK_EQ(state_, State::IDLE) << BENCHMARK_ERROR << "Wrong state on Populate()";
    LOG(INFO) << "Benchmark: Populating";
    state_ = State::POPULATING;
    std::vector<std::thread> threads;
    for (uint32_t i = 0; i < thread_count_; i++) {
        threads.push_back(std::thread(&Benchmark::PopulationThreadFunction, this));
    }
    for (auto &thread : threads) {
        thread.join();
    }
    state_ = State::READY;
}

void Benchmark::Measure() {
    CHECK_EQ(state_, State::READY) << BENCHMARK_ERROR << "Wrong state on Measure()";
    LOG(INFO) << "Benchmark: Measuring";
    state_ = State::MEASURING;
    std::vector<std::thread> threads;
    for (uint32_t i = 0; i < thread_count_; i++) {
        threads.push_back(std::thread(&Benchmark::MeasurementThreadFunction, this));
    }
    std::this_thread::sleep_for(std::chrono::seconds(kMeasureTime));
    state_ = State::FINISHED;
    for (auto &thread : threads) {
        thread.join();
    }
}

void Benchmark::PopulationThreadFunction() {
    Timer timer;
    // TODO: populate the gist
    LOG(INFO) << "Benchmark: Population thread stopped. Running time: " << timer.Elapsed<std::chrono::milliseconds>() << " millisec.";
}

void Benchmark::MeasurementThreadFunction() {
    Timer timer;
    while (state_ == State::MEASURING) {
        // TODO: query the qist
    }
    LOG(INFO) << "Benchmark: Measurement thread stopped. Running time: " << timer.Elapsed<std::chrono::milliseconds>() << " millisec.";
}

Predicate *Benchmark::GeneratePredicate() {
    switch (type_) {
        case Type::B_TREE_BENCHMARK:
            // Interval* interval;
            // TODO: generate random Interval
            // LOG(INFO) << "Benchmark: B+ Tree Interval generated.";
            // return interval;
            break;
        case Type::R_TREE_BENCHMARK:
            // Rectangle* rectangle;
            // TODO: generate random Rectangle
            // return rectangle
            // LOG(INFO) << "Benchmark: R Tree Rectangle generated.";
            break;
        default:
            LOG(FATAL) << "Benchmark: Unknown tree type.";
    }
    return nullptr;
}

char *Benchmark::GenerateData() {
    char *result = new char[kDataLength + 1];
    for (uint32_t i = 0; i < kDataLength; ++i) {
        result[i] = kDataCharacters[data_distribution(rng)];
    }
    result[kDataLength] = 0;
    return result;
    // TODO
}
