// This program shows a clever way to find which number appears an odd
// number of times in a vector (assumes there is only 1 that fits this
// criteria).
// By: Nick from CoffeeBeforeArch

#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

using std::accumulate;
using std::bit_xor;
using std::cout;
using std::endl;
using std::reduce;
using std::vector;

// Bad implementation of findOdd
// Compares every element against every other element
// Earliest it can exit is after one full scan of the vector
int findOddBad(vector<int> v) {
  // For each element in the vector
  for (auto i : v) {
    // Compare against all other vector elements
    int tmp = 0;
    for (auto j : v) {
      // Increment if we found an instance of "i"
      if (j == i) {
        tmp++;
      }
    }
    // If it appeared an odd number of times, we found the answer
    if (tmp % 2) {
      return i;
    }
  }

  // Returns 0 otherwise
  return 0;
}

// Always completes 1 full scan of the array
// Perform bit-wise XOR all elements together
// Background:
//  1.) XOR is an associative and commutative operation
//  2.) n XOR n = 0 (any number XOR itself is 0)
//  3.) n XOR 0 = n (any number XOR 0 is itself)
// Explanation:
//  The XOR of all even-count elements together is 0 because of (2).
//  The XOR of all odd-count elements together is "n" because of (2)
//  and (3).
//  Performing this operations can occur in any order because of (1),
//  so we can just intuitively XOR from the beginning to the end.
// Much better than the previous, but still a little "old-fashioned"
int findOddBetter(vector<int> v) {
  // Accumulate partial results in tmp
  int tmp = 0;

  // Bit-wise XOR of all elements
  for (auto i : v) {
    tmp ^= i;
  }

  return tmp;
}

// How about 1 line of code!
// Performs the same operation as the above, but we're making use of
// the STL!
int findOddBest(vector<int> v) {
  // Bit-wise XOR of all elements
  return accumulate(begin(v), end(v), 0, bit_xor<int>());
}

// Last implementation was great, but slightly non-intuitive because we
// associate accumulate with addition.
// How about something that's more C++17-style?
int findOddBest17(vector<int> v) {
  // Bit-wise XOR of all elements
  return reduce(begin(v), end(v), 0, bit_xor<int>());
}

int main() {
  // Create a vector
  vector<int> v = {2, 2, 3, 4, 4, 1, 1, 3, 4};

  // Get 4 solutions using our 4 functions
  int sol1 = findOddBad(v);
  int sol2 = findOddBetter(v);
  int sol3 = findOddBest(v);
  int sol4 = findOddBest17(v);

  // Print out the results
  cout << "sol1 == " << sol1 << endl;
  cout << "sol2 == " << sol2 << endl;
  cout << "sol3 == " << sol3 << endl;
  cout << "sol4 == " << sol4 << endl;

  return 0;
}
