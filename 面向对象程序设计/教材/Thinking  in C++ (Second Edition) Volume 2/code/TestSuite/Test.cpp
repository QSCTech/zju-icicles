//: TestSuite:Test.cpp {O}
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
#include "Test.h"
#include <iostream>
#include <typeinfo> // Visual C++ requires /GR""
using namespace std;

void Test::do_test(bool cond, 
                   const std::string& lbl,
                   const char* fname, 
                   long lineno){
  if (!cond)
    do_fail(lbl, fname, lineno);
  else
    succeed_();
}

void Test::do_fail(const std::string& lbl,
                   const char* fname, 
                   long lineno){
  ++nFail;
  if (osptr){
    *osptr << typeid(*this).name()
             << "failure: (" << lbl << ") , "
             << fname
             << " (line " << lineno << ")\n";
  }
}

long Test::report() const {
  if (osptr){
    *osptr << "Test \"" << typeid(*this).name()
             << "\":\n\tPassed: " << nPass
             << "\tFailed: " << nFail
             << endl;
  }
  return nFail;
} ///:~
