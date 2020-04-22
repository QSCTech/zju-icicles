//: C02:StackTest.h
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
#ifndef STACKTEST_H
#define STACKTEST_H
#include "Stack.h"
#include "../TestSuite/Test.h"
#include <iostream>
using namespace std;

class StackTest : public Test {
  enum {SIZE = 5};
  Stack<int> stk;
public:
  StackTest() : stk(SIZE){}
  void run(){
    testUnderflow();
    testPopulate();
    testOverflow();
    testPop();
    testBadSize();
  }
  void testBadSize(){
    try {
      Stack<int> s(0);
      fail_("Bad Size");
    }
    catch (StackError&) {
      succeed_();
    }
  }
  void testUnderflow(){
    test_(stk.size() == 0);
    try {
      stk.top();
      fail_("Underflow");
    }
    catch (StackError&) {
      succeed_();
    }
    try {
      stk.pop();
      fail_("Underflow");
    }
    catch (StackError&) {
      succeed_();
    }
  }
  void testPopulate(){
    try {
      for (int i = 0; i < SIZE; ++i)
        stk.push(i);
      succeed_();
    }
    catch (StackError&) {
      fail_("Populate");
    }
    test_(stk.size() == SIZE);
    test_(stk.top() == SIZE-1);
  }
  void testOverflow(){
    try {
      stk.push(SIZE);
      fail_("Overflow");
    }
    catch (StackError&) {
      succeed_();
    }
  }
  void testPop(){
    for (int i = 0; i < SIZE; ++i)
      test_(stk.pop() == SIZE-i-1);
    test_(stk.size() == 0);
  }
}; 
#endif // STACKTEST_H ///:~
