//: C02:StackTest.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
//{L} ../TestSuite/Test
#include <iostream>
#include "StackTest.h"
using namespace std;

int main() {
  StackTest t;
  t.run();
  t.report();
  return t.getNumFailed();
} ///:~
