//: C08:Binder3.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Binders aren't limited to producing predicates
//{L} ../TestSuite/Test
#include "Generators.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <functional>
using namespace std;

int main() {
  ostream_iterator<int> out(cout, " ");
  vector<int> v(15);
  generate(v.begin(), v.end(), URandGen(20));
  copy(v.begin(), v.end(), out);
  cout << endl;
  transform(v.begin(), v.end(), v.begin(),
    bind2nd(multiplies<int>(), 10));
  copy(v.begin(), v.end(), out);
  cout << endl;
} ///:~
