// This program shows off the clever initialization of a string
// By: Nick from CoffeeBeforeArch

#include <string>
#include <benchmark/benchmark.h>

using std::string;

// A simple benchmark to test the creation of a string
static void baseBench(benchmark::State &s){
  while(s.KeepRunning()){
    // By forgetting const, we call the constructor then do assignment
    string s;
    s = "Simple string";
  }
}
BENCHMARK(baseBench);

// A simple benchmark to test the creation of a string
static void betterBench(benchmark::State &s){
  while(s.KeepRunning()){
    // Now the strings constructor perform initialization
    const string s = "Simple string";
  }
}
BENCHMARK(betterBench);

BENCHMARK_MAIN();
