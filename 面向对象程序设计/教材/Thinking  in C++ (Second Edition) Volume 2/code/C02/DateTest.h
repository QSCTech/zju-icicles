//: C02:DateTest.h
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
#include "../TestSuite/Test.h"
#include "Date.h"

class DateTest : public Test {
  Date mybday;
  Date today;
public:
  DateTest()
    : mybday(1951, 10,1) {}
  void run() {
    testOps();
    testDuration();
  }
  void testOps() {
    test_(mybday < today);
    test_(mybday <= today);
    test_(mybday != today);
    test_(mybday == mybday);
  }
  void testDuration() {
    Date d2(2001, 7, 4);
    Duration dur = duration(mybday, d2);
    test_(dur.years == 49);
    test_(dur.months == 9);
    test_(dur.days == 3);
  }
}; ///:~
