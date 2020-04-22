//: C02:DateTest.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Automated Testing (with a Framework)
//{L} Date ../TestSuite/Test
#include <iostream>
#include "DateTest.h"
using namespace std;

int main() {
  DateTest test;
  test.run();
  test.report();
  return test.getNumFailed();
}
/* Output:
Passed: 7, Failed: 0
*/ ///:~
