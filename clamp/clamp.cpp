// This program shows two implementations of a clamp function in C++
// By: Nick from CoffeeBeforeArch

#include <benchmark/benchmark.h>
#include <vector>
#include <cstdlib>

static void clampBench(benchmark::State &s) {
  int N = s.range(0);
  std::vector<int> v;
  v.reserve(N);
  for(int i = 0; i < N; i++){
    v.push_back(rand());
  }

  while(s.KeepRunning()){
    for(auto &i: v){
      i = i > 255 ? 255 : i;
    }
  }
}
BENCHMARK(clampBench)->Range(1 << 10, 1 << 15);

BENCHMARK_MAIN();
