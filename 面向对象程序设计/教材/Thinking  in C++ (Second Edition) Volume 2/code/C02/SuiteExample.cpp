//: C02:SuiteExample.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
//{L} ../TestSuite/Test ../TestSuite/Suite Date
#include <iostream>
#include "../TestSuite/Suite.h"
#include "DateTest.h"
#include "StackTest.h"
using namespace std;

int main() {
  Suite s("Date and Stack Tests");
  s.addTest(new DateTest);
  s.addTest(new StackTest);
  s.run();
  long nFail = s.report();
  s.free();
  cout << "\nTotal failures: " << nFail << endl;
  return nFail;
}

/* Output:
Suite "Date and Stack Tests"
============================
Test "DateTest":
	Passed: 7	Failed: 0
Test "StackTest":
	Passed: 14	Failed: 0
============================

Total failures: 0
*/ ///:~
