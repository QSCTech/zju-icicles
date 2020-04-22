//: C08:Removing.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// The removing algorithms
// May be a bug here?
//{L} ../TestSuite/Test
//{-bor}
//{-msc}
//{-g++295}
#include "PrintSequence.h"
#include "Generators.h"
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

struct IsUpper {
  bool operator()(char c) {
    return isupper(c);
  }
};

int main() {
  vector<char> v(50);
  generate(v.begin(), v.end(), CharGen());
  print(v, "v", "");
  // Create a set of the characters in v:
  set<char> cs(v.begin(), v.end());
  set<char>::iterator it = cs.begin();
  vector<char>::iterator cit;
  // Step through and remove everything:
  while(it != cs.end()) {
    cit = remove(v.begin(), v.end(), *it);
    cout << *it << "[" << *cit << "] ";
    print(v, "", "");
    it++;
  }
  generate(v.begin(), v.end(), CharGen());
  print(v, "v", "");
  cit = remove_if(v.begin(), v.end(), IsUpper());
  print(v.begin(), cit, "after remove_if", "");
  // Copying versions are not shown for remove
  // and remove_if.
  sort(v.begin(), cit);
  print(v.begin(), cit, "sorted", "");
  vector<char> v2;
  unique_copy(v.begin(), cit, back_inserter(v2));
  print(v2, "unique_copy", "");
  // Same behavior:
  cit = unique(v.begin(), cit, equal_to<char>());
  print(v.begin(), cit, "unique", "");
} ///:~
