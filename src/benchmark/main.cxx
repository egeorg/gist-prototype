#include "easylogging++.h"

#include "benchmark/benchmark.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[]) {
    el::Configurations conf("../log.conf");
    el::Loggers::reconfigureAllLoggers(conf);

    Benchmark benchmark(Benchmark::Type::B_TREE_BENCHMARK, 4);
    benchmark.Run();

    return 0;
}