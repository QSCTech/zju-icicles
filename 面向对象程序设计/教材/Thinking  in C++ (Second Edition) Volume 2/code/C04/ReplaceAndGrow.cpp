//: C04:ReplaceAndGrow.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
//{L} ../TestSuite/Test
#include <string>
#include <iostream>
using namespace std;

int main() {
  string bigNews("I saw Elvis in a UFO. "
    "I have Been working too hard.");
  string replacement("wig");
  // The first arg says "replace chars 
  // beyond the end of the existing string":
  bigNews.replace(bigNews.size(), 
    replacement.size(), replacement);
  cout << bigNews << endl;
} ///:~
