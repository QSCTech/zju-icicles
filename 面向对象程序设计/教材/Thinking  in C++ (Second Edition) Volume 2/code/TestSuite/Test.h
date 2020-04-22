//: TestSuite:Test.h
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
#ifndef TEST_H
#define TEST_H
#include <string>
#include <iostream>
#include <cassert>
using std::string;
using std::ostream;
using std::cout;

// The following have underscores because they 
// are macros (and it's impolite to usurp other 
// users' functions!). For consistency, 
// succeed_() also has an underscore.

#define test_(cond) \
  do_test(cond, #cond, __FILE__, __LINE__)
#define fail_(str) \
  do_fail(str, __FILE__, __LINE__)

class Test {
public:
  Test(ostream* osptr = &cout);
  virtual ~Test(){}
  virtual void run() = 0;
  long getNumPassed() const;
  long getNumFailed() const;
  const ostream* getStream() const;
  void setStream(ostream* osptr);
  void succeed_();
  long report() const;
  virtual void reset();
protected:
  void do_test(bool cond, const string& lbl,
               const char* fname, long lineno);
  void do_fail(const string& lbl,
               const char* fname, long lineno);
private:
  ostream* osptr;
  long nPass;
  long nFail;
  // Disallowed:
  Test(const Test&);
  Test& operator=(const Test&);
};

inline Test::Test(ostream* osptr) {
  this->osptr = osptr;
  assert(osptr);
  nPass = nFail = 0;
}

inline long Test::getNumPassed() const {
  return nPass;
}

inline long Test::getNumFailed() const {
  return nFail;
}

inline const ostream* Test::getStream() const {
  return osptr;
}

inline void Test::setStream(ostream* osptr) {
  this->osptr = osptr;
}

inline void Test::succeed_() {
  ++nPass;
}

inline void Test::reset() {
  nPass = nFail = 0;
}
#endif // TEST_H ///:~
