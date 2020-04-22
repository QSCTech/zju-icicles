//: C08:Binder1.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Using STL "binders"
//{L} ../TestSuite/Test
//{-g++3}
#include "Generators.h"
#include "copy_if.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <functional>
using namespace std;

int main() {
  const int sz = 10;
  const int max = 40;
  vector<int> a(sz), r;
  URandGen urg(max);
  ostream_iterator<int> out(cout, " ");
  generate_n(a.begin(), sz, urg);
  copy(a.begin(), a.end(), out);
  int* d = find_if(a.begin(), a.end(), 
    bind2nd(less<int>(), 20));
  cout << "\n *d = " << *d << endl;
  // copy_if() is not in the Standard C++ library
  // but is defined later in the chapter:
  copy_if(a.begin(), a.end(), back_inserter(r),
    bind2nd(less<int>(), 20));
  copy(r.begin(), r.end(), out);
  cout << endl;
} ///:~
