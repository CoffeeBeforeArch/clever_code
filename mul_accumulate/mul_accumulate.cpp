// This program shows 3 ways for multiplying two vectors together and taking
// the sum of all the products
// By: Nick from CoffeeBeforeArch

#include <execution>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

using std::cout;
using std::endl;
using std::inner_product;
using std::multiplies;
using std::plus;
using std::transform_reduce;
using std::vector;

// Naive implementation of mulAndAccumulate
// Uses our own hand-written for-loop
int badMulAccumulate(vector<int> &v1, vector<int> &v2) {
  int tmp = 0;
  for (auto i = 0u; i < v1.size(); i++) {
    tmp += v1[i] * v2[i];
  }

  return tmp;
}

// Better implementation using std::inner_product!
// Allows us to traverse two containers together without indexing!
// Reduces our implementation to a single line of code.
// By default, performs multiplication and addition
int goodMulAccumulate(vector<int> &v1, vector<int> v2) {
  // inner_product(begin(v1), end(v1), begin(v2), 0, plus<int>(),
  // multiplies<int>());
  return inner_product(begin(v1), end(v1), begin(v2), 0);
}

// Now we have an implementation we can parallelize and vectorize!
int goodMulAccumulate17(vector<int> &v1, vector<int> &v2) {
  return transform_reduce(std::execution::par_unseq, begin(v1), end(v1),
                          begin(v2), 0, plus<int>(), multiplies<int>());
}

// Add parallelize and vectorize
int main() {
  // Declare and initialize our input vectors
  vector<int> v1 = {1, 2, 3, 4, 5};
  vector<int> v2 = {10, 100, 1000, 10000, 100000};

  // Call our three implementations
  cout << badMulAccumulate(v1, v2) << endl;
  cout << goodMulAccumulate(v1, v2) << endl;
  cout << goodMulAccumulate17(v1, v2) << endl;

  return 0;
}
