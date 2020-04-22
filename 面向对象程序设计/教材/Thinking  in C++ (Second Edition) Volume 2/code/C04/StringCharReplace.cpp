//: C04:StringCharReplace.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
//{L} ../TestSuite/Test
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
  string s("aaaXaaaXXaaXXXaXXXXaaa");
  cout << s << endl;
  replace(s.begin(), s.end(), 'X', 'Y');
  cout << s << endl;
} ///:~
