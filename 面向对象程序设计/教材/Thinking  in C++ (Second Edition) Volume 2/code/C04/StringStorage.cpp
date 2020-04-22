//: C04:StringStorage.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
//{L} ../TestSuite/Test
#include <string>
#include <iostream>
#include "../TestSuite/Test.h"
using namespace std;

class StringStorageTest : public Test {
public:
  void run() {
    string s1("12345");
    // Set the iterator indicate the first element
    string::iterator it = s1.begin();
    // This may copy the first to the second or 
    // use reference counting to simulate a copy 
    string s2 = s1;
    test_(s1 == s2);
    // Either way, this statement may ONLY modify first
    *it = '0';
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    test_(s1 != s2);
  }
};

int main() {
  StringStorageTest sst;
  sst.setStream(&cout);
  sst.run();
  return sst.report();
} ///:~
