//: TestSuite:Suite.h
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
#ifndef SUITE_H
#define SUITE_H
#include "../TestSuite/Test.h"
#include <vector>
#include <stdexcept>
using std::vector;
using std::logic_error;

class TestSuiteError : public logic_error {
public:
  TestSuiteError(const string& s = "")
    : logic_error(s) {}
};

class Suite {
public:
  Suite(const string& name, ostream* osptr = &cout);
  string getName() const;
  long getNumPassed() const;
  long getNumFailed() const;
  const ostream* getStream() const;
  void setStream(ostream* osptr);
  void addTest(Test* t) throw (TestSuiteError);
  void addSuite(const Suite&) 
    throw(TestSuiteError);
  void run();  // Calls Test::run() repeatedly
  long report() const;
  void free(); // Deletes tests
private:
  string name;
  ostream* osptr;
  vector<Test*> tests;
  void reset();
  // Disallowed ops:
  Suite(const Suite&);
  Suite& operator=(const Suite&);
};

inline
Suite::Suite(const string& name, ostream* osptr)
   : name(name) {
  this->osptr = osptr;
}

inline string Suite::getName() const {
  return name;
}

inline const ostream* Suite::getStream() const {
  return osptr;
}

inline void Suite::setStream(ostream* osptr) {
  this->osptr = osptr;
}
#endif // SUITE_H ///:~
