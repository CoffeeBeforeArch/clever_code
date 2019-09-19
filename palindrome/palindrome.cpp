// This program shows off 3 different ways of calculating a palindrome
// in C++
// By: Nick from CoffeeBeforeArch

#include <algorithm>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::equal;
using std::string;
using std::reverse;
using std::equal;

// Compares letters at the front to those at the back 
// A little ugly! Not easily apparent what the purpose of the loop and
// conditional check is doing
bool isPalindromeBad(const string &s) {
  // Get the size of the string
  std::size_t size = s.size();
  
  // Get the stopping point for comparison
  auto stop = size / 2;

  // Check the first half of the string to the second half
  for (std::size_t i = 0; i < stop; i++) {
    // Compare both sides of the string and see if they are the same
    if (s[i] != s[size - i - 1]) {
      // If !=, it's not a palindrome
      return false;
    }
  }

  // Otherwise, it is!
  return true;
}

// A more intuitive way to solve the problem. We can just use reverse
// the string and do an equality comparison
// Slightly more expensive. Reverse has to do (last - first) / 2 swaps
bool isPalindromeBetter(const string &s) {
  return s == reverse(s);
}

// As (almost) always, there's an STL function to the rescue
// Will be better performance that reversal then comparison
// No messy code like the first example
bool isPalindromeBest(const string &s) {
  // Use the equal function!
  // Size of the comparison is determined from the first two iterators,
  // so we don't have to pass rend(s) to the function.
  return equal(begin(s), end(s), rbegin(s));
}

int main() {
  // Two strings
  // One is a palindrome
  string s1("rotor");
  // One is not
  string s2("candy");

  // Test each of our functions
  bool sol1 = isPalindromeBad(s1);
  bool sol2 = isPalindromeBetter(s1);
  bool sol3 = isPalindromeBest(s1);

  cout << sol1 << endl;
}
