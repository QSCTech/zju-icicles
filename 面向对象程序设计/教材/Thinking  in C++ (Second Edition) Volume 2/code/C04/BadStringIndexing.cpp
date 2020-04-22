//: C04:BadStringIndexing.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
//{L} ../TestSuite/Test
#include <string>
#include <iostream>
using namespace std;

int main(){
  string s("1234");
  // Runtime problem: goes beyond array bounds:
  //! s[5];
  // Saves you by throwing an exception:
  try {
    s.at(5);
  } catch(...) {
    cerr << "Went beyond array bounds!" << endl;
  }
} ///:~
