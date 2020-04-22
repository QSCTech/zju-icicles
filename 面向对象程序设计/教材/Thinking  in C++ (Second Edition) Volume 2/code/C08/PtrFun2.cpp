//: C08:PtrFun2.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Using ptr_fun() for two-argument functions
//{L} ../TestSuite/Test
//{-bor}
//{-g++3}
#include <algorithm>
#include <vector>
#include <iostream>
#include <functional>
#include <cmath>
using namespace std;

double d[] = { 01.23, 91.370, 56.661,
  023.230, 19.959, 1.0, 3.14159 };
const int dsz = sizeof d / sizeof *d;

int main() {
  vector<double> vd;
  transform(d, d + dsz, back_inserter(vd), 
    bind2nd(ptr_fun(pow), 2.0));
  copy(vd.begin(), vd.end(),
    ostream_iterator<double>(cout, " "));
  cout << endl;    
} ///:~
