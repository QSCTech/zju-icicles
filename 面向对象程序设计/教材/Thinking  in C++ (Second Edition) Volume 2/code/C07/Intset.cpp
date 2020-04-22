//: C07:Intset.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Simple use of STL set
//{L} ../TestSuite/Test
#include <set>
#include <iostream>
using namespace std;

int main() {
  set<int> intset;
    for(int i = 0; i < 25; i++)
      for(int j = 0; j < 10; j++)
        // Try to insert multiple copies:
        intset.insert(j);
  // Print to output:
  copy(intset.begin(), intset.end(),
    ostream_iterator<int>(cout, "\n"));
} ///:~
