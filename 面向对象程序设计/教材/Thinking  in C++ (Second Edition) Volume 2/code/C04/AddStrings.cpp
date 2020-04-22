//: C04:AddStrings.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
//{L} ../TestSuite/Test
#include <string>
#include <iostream>
using namespace std;

int main() {
  string s1("This ");
  string s2("That ");
  string s3("The other ");
  // operator+ concatenates strings
  s1 = s1 + s2;
  cout << s1 << endl;
  // Another way to concatenates strings
  s1 += s3;
  cout << s1 << endl;
  // You can index the string on the right
  s1 += s3 + s3[4] + "oh lala";
  cout << s1 << endl;
} ///:~
