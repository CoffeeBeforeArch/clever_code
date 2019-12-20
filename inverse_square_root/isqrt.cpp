// This program shows off some clever code to do an inverse square root
// This was famously used in the videogame Quake III Arena
// By: Nick from CoffeeBeforeArch

#include <benchmark/benchmark.h>
#include <immintrin.h>
#include <cstring>
#include <iostream>

// A UB implementation of the fast inverse square root function
float Q_rsqrt_ub(float num) {
  int i;
  float x2, y;
  const float threehalfs = 1.5f;

  x2 = num * 0.5f;
  y = num;

  // UB!
  // Type punning is bad!
  i = *(int *)&y;
  i = 0x5f3759df - (i >> 1);

  // UB!
  // Type punning is bad!
  y = *(float *)&i;
  y = y * (threehalfs - (x2 * y * y));

  return y;
}

// A non-UB implementation of the fast inverse square root function
float Q_rsqrt(float num) {
  int i;
  float x2, y;
  const float threehalfs = 1.5f;

  x2 = num * 0.5f;
  y = num;

  // Copying the bits solves our problems
  // Optimizers can tell what we're trying to do!
  std::memcpy(&i, &y, sizeof(float));
  i = 0x5f3759df - (i >> 1);

  // Copying the bits solves our problems
  // Optimizers can tell what we're trying to do!
  std::memcpy(&y, &i, sizeof(float));
  y = y * (threehalfs - (x2 * y * y));

  return y;
}

// Use intrinsic instead!
__m128 Q_rsqrt(__m128 num) { return _mm_rsqrt_ps(num); }

// Benchmark the UB implementation
static void UBBench(benchmark::State &s) {
  float in[4] = {4.0f, 16.0f, 64.0f, 256.0f};
  volatile float out[4];

  while (s.KeepRunning()) {
    for (int i = 0; i < 4; i++) {
      out[i] = Q_rsqrt_ub(in[i]);
    }
  }
}
BENCHMARK(UBBench);

// Benchmark the well-defined implementation
static void WDBench(benchmark::State &s) {
  float in[4] = {4.0f, 16.0f, 64.0f, 256.0f};
  volatile float out[4];

  while (s.KeepRunning()) {
    for (int i = 0; i < 4; i++) {
      out[i] = Q_rsqrt(in[i]);
    }
  }
}
BENCHMARK(WDBench);

// Benchmark the intrinsic implementation
static void IntrinsicBench(benchmark::State &s) {
  __m128 in = _mm_set_ps(4.0f, 16.0f, 64.0f, 256.0f);
  volatile __m128 out;

  while (s.KeepRunning()) {
    out = Q_rsqrt(in);
  }
}
BENCHMARK(IntrinsicBench);

BENCHMARK_MAIN();
