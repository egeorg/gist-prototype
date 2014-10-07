cmake_minimum_required(VERSION 2.8.4)
project(Gist)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=gnu++0x")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/")
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/logs)

enable_testing()

file(GLOB GIST_SOURCES ${PROJECT_SOURCE_DIR}/src/gist/*.cxx)
file(GLOB BENCHMARK_SOURCES ${PROJECT_SOURCE_DIR}/src/benchmark/*.cxx)
file(GLOB TEST_SOURCES ${PROJECT_SOURCE_DIR}/src/tests/*.cxx)

include_directories(${PROJECT_SOURCE_DIR}/src/)
include_directories(${PROJECT_SOURCE_DIR}/third_party/)

add_executable(benchmark ${BENCHMARK_SOURCES} ${GIST_SOURCES})
target_link_libraries(benchmark)

add_executable(gist_tests ${TEST_SOURCES})
target_link_libraries(gist_tests -lgtest -lgtest_main)

add_test(NAME run_gist_tests COMMAND gist_tests)