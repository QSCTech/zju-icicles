//: C03:MemTest.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
//{L} MemCheck
//{-msc}
// Test of MemCheck system
#include "MemCheck.h"

int main() {
  void* v = std::malloc(100);
  delete v;
  int* x = new int;
  std::free(x);
  new double;
} ///:~
