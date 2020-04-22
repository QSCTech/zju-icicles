//: C07:DequeCoreDump.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// How to break a program using a deque
#include <queue>
#include <iostream>
using namespace std;

int main() {
  deque<int> di(100, 0);
  // No problem iterating from beginning to end,
  // even though it spans multiple blocks:
  copy(di.begin(), di.end(), 
    ostream_iterator<int>(cout, " "));
  deque<int>::iterator i = // In the middle:
    di.begin() + di.size() / 2;;
  // Walk the iterator forward as you perform 
  // a lot of insertions in the middle:
  for(int j = 0; j < 1000; j++) {
    cout << j << endl;
    di.insert(i++, 1); // Eventually breaks
  }
} ///:~
