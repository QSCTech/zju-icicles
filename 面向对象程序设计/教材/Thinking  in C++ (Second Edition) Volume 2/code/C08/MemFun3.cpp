//: C08:MemFun3.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Using mem_fun()
//{L} ../TestSuite/Test
//{-msc}
#include "NumStringGen.h"
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <functional>
using namespace std;

int main() {
  const int sz = 9;
  vector<string> vs(sz);
  // Fill it with random number strings:
  generate(vs.begin(), vs.end(), NumStringGen());
  copy(vs.begin(), vs.end(), 
    ostream_iterator<string>(cout, "\t"));
  cout << endl;
  const char* vcp[sz];
  transform(vs.begin(), vs.end(), vcp, 
    mem_fun_ref(&string::c_str));
  vector<double> vd;
  transform(vcp,vcp + sz,back_inserter(vd),
    std::atof);
  copy(vd.begin(), vd.end(), 
    ostream_iterator<double>(cout, "\t"));
  cout << endl;
} ///:~
