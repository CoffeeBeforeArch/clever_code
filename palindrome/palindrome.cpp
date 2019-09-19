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

// Very intuitive way to get a palindrome
// A little ugly! Not easily apparent what the purpose of the loop and
// conditional check is doing
bool isPalindrome(const string &s) {
  // Get the size of the string
  std::size_t size = s.size();

  // Iterate over the length of the string
  for (std::size_t i = 0; i < size; i++) {
    // Compare both sides of the string and see if they are the same
    if (s[i] != s[size - i - 1]) {
      // If not, it's not a palindrome
      return false;
    }
  }

  // Otherwise, it is!
  return true;
}

int main() {
  // Two strings
  // One is a palindrome
  string s1("rotor");
  // One is not
  string s2("candy");

  // Test each of our functions
  bool sol1 = isPalindrome(s1);
  bool sol2 = isPalindrome(s1);
  bool sol3 = isPalindrome(s1);
  bool sol4 = isPalindrome(s1);

  cout << sol1 << endl;
}
