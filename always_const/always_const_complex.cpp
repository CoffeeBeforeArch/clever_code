// This program shows off the clever initialization of a string
// By: Nick from CoffeeBeforeArch

#include <benchmark/benchmark.h>
#include <cstdlib>
#include <string>

using std::string;

// What if we have a more complex initialization?
static void baseBench(benchmark::State &s) {
  const int i = rand();
  while (s.KeepRunning()) {
    // By forgetting const, we call the constructor then do assignment
    string s;
    switch (i % 4) {
      case 0:
        s = "String is Mod 0     ";
        break;
      case 1:
        s = "String is Mod 2     ";
        break;
      case 2:
        s = "String is Mod 3    ";
        break;
      case 3:
        s = "String is Mod 4    ";
        break;
    }
  }
}
BENCHMARK(baseBench);

// We can solve more complex initialization with lambdas!
static void betterBench(benchmark::State &s) {
  const int i = rand();
  while (s.KeepRunning()) {
    // By forgetting const, we call the constructor then do assignment
    const string s = [&]() {
      switch (i % 4) {
        case 0:
          return "String is Mod 0    ";
        case 1:
          return "String is Mod 2    ";
        case 2:
          return "String is Mod 3    ";
        case 3:
          return "String is Mod 4    ";
        default:
          return "Some string to shut the compiler up";
      }
    }();
  }
}
BENCHMARK(betterBench);

BENCHMARK_MAIN();
