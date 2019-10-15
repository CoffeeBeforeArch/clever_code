// This program shows two ways to implement quicksort in C++
// By: Nick from CoffeeBeforeArch

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

using std::cout;
using std::distance;
using std::endl;
using std::generate;
using std::next;
using std::partition;
using std::swap;
using std::vector;

// Create a sub-array for elements "<=" and ">" the pivot
// Takes an array, left index, and pivot index as arguments
int partition(vector<int> &v, int l, int p) {
  // Start with a sub-array that is empty
  int low = l - 1;

  // Compare all numbers before the pivot
  int high = p - 1;

  // Go over all elements in sub-array
  for (int i = l; i <= high; i++) {
    // Does this element go in the "<=" sub-array?
    if (v[i] <= v[p]) {
      // Move over marker of sub-array
      low++;

      // Swap the element into position
      swap(v[low], v[i]);
    }
  }
  // Move the pivot into the correct position
  swap(v[low + 1], v[p]);

  // Return the index of the element in the correct place
  return low + 1;
}

// Recursive function that partitions the array into "<="/">"
// sub-arrays, and calls quicksort on them
// Classic implementation (very much C-style)
void naiveQuicksort(vector<int> &v, int l, int p) {
  // Recursively called until only a single element left
  if (l < p) {
    // Partition the array into "<="/">" sub-arrays
    int new_p = partition(v, l, p);

    // Sort the sub-arrays via recursive calls
    // Sort the "<=" sub-array
    naiveQuicksort(v, l, new_p - 1);
    // Sort the ">" sub-array
    naiveQuicksort(v, new_p + 1, p);
  }
}

// Better version of quicksort using std::partition from the the STL!
// Now we only have to write a single function!
void goodQuicksort(vector<int>::iterator first, vector<int>::iterator last) {
  // We've reached the base case!
  if (first == last) {
    return;
  }

  // Take the pivot as the middle element
  auto pivot = *next(first, distance(first, last) / 2);

  // Partition to get all elements less that the pivot
  auto mid_1 =
      partition(first, last, [pivot](const auto &em) { return em < pivot; });

  // Partition to get all elements greater than the pivot
  auto mid_2 =
      partition(mid_1, last, [pivot](const auto &em) { return !(pivot < em); });

  // Recusive calls to quicksort until we are left with a single element
  goodQuicksort(first, mid_1);
  goodQuicksort(mid_2, last);
}

int main() {
  // Create two vectors of random ints (copy one to the other)
  vector<int> v1;
  v1.resize(10);
  generate(begin(v1), end(v1), []() { return rand() % 100; });
  vector<int> v2 = v1;

  // Print vectors before
  cout << "BEFORE" << endl;
  cout << "v1: ";
  for (auto i : v1) {
    cout << i << " ";
  }
  cout << endl;

  cout << "v2: ";
  for (auto i : v2) {
    cout << i << " ";
  }
  cout << endl;

  // Sort the two vectors
  naiveQuicksort(v1, 0, v1.size() - 1);
  goodQuicksort(begin(v2), end(v2));

  // Print the sorted arrays
  cout << "AFTER" << endl;
  cout << "v1: ";
  for (auto i : v1) {
    cout << i << " ";
  }
  cout << endl;

  cout << "v2: ";
  for (auto i : v2) {
    cout << i << " ";
  }
  cout << endl;

  return 0;
}
