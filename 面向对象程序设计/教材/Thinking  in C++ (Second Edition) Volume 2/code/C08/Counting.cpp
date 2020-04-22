//: C08:Counting.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// The counting algorithms
//{L} ../TestSuite/Test
//{-g++295}
//{-msc}
#include "PrintSequence.h"
#include "Generators.h"
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  vector<char> v;
  generate_n(back_inserter(v), 50, CharGen());
  print(v, "v", "");
  // Create a set of the characters in v:
  set<char> cs(v.begin(), v.end());
  set<char>::iterator it = cs.begin();
  while(it != cs.end()) {
    int n = count(v.begin(), v.end(), *it);
    cout << *it << ": " << n << ", ";
    it++;
  }
  int lc = count_if(v.begin(), v.end(), 
    bind2nd(greater<char>(), 'a'));
  cout << "\nLowercase letters: " << lc << endl;
  sort(v.begin(), v.end());
  print(v, "sorted", "");
} ///:~
