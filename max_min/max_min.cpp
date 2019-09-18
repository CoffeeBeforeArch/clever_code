// This program shows a number of different ways to get the difference
// of the Max and Min elements of a vector.
// By: Nick from CoffeeBeforeArch

#include <algorithm>
#include <cstdlib>
#include <vector>
#include <iostream>

using std::max;
using std::minmax_element;
using std::vector;
using std::cout;
using std::endl;

// A very intuitive way to solve the problem
// Very old-fashioned, poor performance (must check all combinations)
int findRangeBad(vector<int> v) {
  // Final result will be stored in tmp
  int tmp = 0;

  // Loop over all elements in the array
  for (auto i : v) {
    // Compare against all other elements in the array
    for (auto j : v) {
      // Take the max of the tmp and absolute difference
      tmp = max(tmp, abs(i - j));
    }
  }

  return tmp;
}

// Preprocess the data ahead of time!
// Uses modern features (sort), and also reduces the problems performance to
// that of sort
int findRangeBetter(vector<int> v) {
  // Sort the array using the STL
  sort(begin(v), end(v));
  // Return the last element - the first
  return v.back() - v.front();
}

// Use a function that was built for this exact purpose!
// minmax_element(...) returns a pair of the min and max element
int findRangeBest(vector<int> v) {
  // Get a pair of the min and max element
  auto pair = minmax_element(begin(v), end(v));
  // Return the difference of the pair
  return *pair.second - *pair.first;
}

// Using structured bindings (C++17) we can unpack the pair early!
int findRangeBest17(vector<int> v) {
  // Get a pair of the min and max element and unpack it
  auto [a, b] = minmax_element(begin(v), end(v));
  // Return the difference of the elements
  return *b - *a;
}

int main() {
  // Create a vector with some test numbers
  // Min = 1, Max = 41
  vector<int> v = {20, 3, 2, 35, 41, 4, 9, 1, 25};

  // Get 4 solutions using our 4 functions
  int sol1 = findRangeBad(v);
  int sol2 = findRangeBetter(v);
  int sol3 = findRangeBest(v);
  int sol4 = findRangeBest17(v);

  // Print out the results
  cout << "sol1 == " << sol1 << endl;
  cout << "sol2 == " << sol2 << endl;
  cout << "sol3 == " << sol3 << endl;
  cout << "sol4 == " << sol4 << endl;

  return 0;
}
