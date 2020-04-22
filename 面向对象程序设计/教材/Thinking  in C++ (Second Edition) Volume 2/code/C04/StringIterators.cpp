//: C04:StringIterators.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
//{L} ../TestSuite/Test
//{-msc} Execution error
#include <string>
#include <iostream>
using namespace std;

int main() {
  string source("xxx");
  string s(source.begin(), source.end());
  cout << s << endl;
} ///:~
