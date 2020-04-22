//: C07:ListRobustness.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// lists are harder to break
//{L} ../TestSuite/Test
#include <list>
#include <iostream>
using namespace std;

int main() {
  list<int> li(100, 0);
  list<int>::iterator i = li.begin();
  for(int j = 0; j < li.size() / 2; j++)
    i++;
  // Walk the iterator forward as you perform 
  // a lot of insertions in the middle:
  for(int k = 0; k < 1000; k++)
    li.insert(i++, 1); // No problem
  li.erase(i);
  i++;
  //! *i = 2; // Oops! It's invalid
} ///:~
