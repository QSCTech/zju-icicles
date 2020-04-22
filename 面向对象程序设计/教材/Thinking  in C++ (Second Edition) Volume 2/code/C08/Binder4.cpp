//: C08:Binder4.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// The bound argument does not have 
// to be a compile-time constant
//{L} ../TestSuite/Test
//{-g++295}
#include "copy_if.h"
#include "PrintSequence.h"
#include "../require.h"
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdlib>
using namespace std;

int boundedRand() { return rand() % 100; }

int main() {
  const int sz = 20;
  int a[20], b[20] = {0};
  generate(a, a + sz, boundedRand);
  int val = boundedRand();
  int* end = copy_if(a, a + sz, b, bind2nd(greater<int>(), val));
  // Sort for easier viewing:
  sort(a, a + sz);
  sort(b, end);
  print(a, a + sz, "array a", " ");
  print(b, end, "values greater than yours"," ");
} ///:~
