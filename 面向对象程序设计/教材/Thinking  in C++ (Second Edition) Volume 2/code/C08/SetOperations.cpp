//: C08:SetOperations.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Set operations on sorted ranges
//{L} ../TestSuite/Test
//{-msc}
#include <vector>
#include <algorithm>
#include "PrintSequence.h"
#include "Generators.h"
using namespace std;

int main() {
  vector<char> v(50), v2(50);
  CharGen g;
  generate(v.begin(), v.end(), g);
  generate(v2.begin(), v2.end(), g);
  sort(v.begin(), v.end());
  sort(v2.begin(), v2.end());
  print(v, "v", "");
  print(v2, "v2", "");
  bool b = includes(v.begin(), v.end(), 
    v.begin() + v.size()/2, v.end());
  cout << "includes: " <<
    (b ? "true" : "false") << endl;
  vector<char> v3, v4, v5, v6;
  set_union(v.begin(), v.end(), 
    v2.begin(), v2.end(), back_inserter(v3));
  print(v3, "set_union", "");
  set_intersection(v.begin(), v.end(), 
    v2.begin(), v2.end(), back_inserter(v4));
  print(v4, "set_intersection", "");
  set_difference(v.begin(), v.end(), 
    v2.begin(), v2.end(), back_inserter(v5));
  print(v5, "set_difference", "");
  set_symmetric_difference(v.begin(), v.end(), 
    v2.begin(), v2.end(), back_inserter(v6));
  print(v6, "set_symmetric_difference","");
} ///:~
