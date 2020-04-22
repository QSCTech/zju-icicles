//: C06:TemplateTemplate.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
//{L} ../TestSuite/Test
//{-msc}
#include <vector>
#include <iostream>
#include <string>
using namespace std;

// As long as things are simple, 
// this approach works fine:
template<typename C>
void print1(C& c) {
  typename C::iterator it;
  for(it = c.begin(); it != c.end(); it++)
    cout << *it << " ";
  cout << endl;
}

// Template-template argument must 
// be a class; cannot use typename:
template<typename T, template<typename> class C>
void print2(C<T>& c) {
  copy(c.begin(), c.end(), 
    ostream_iterator<T>(cout, " "));
  cout << endl;
}

int main() {
  vector<string> v(5, "Yow!");
  print1(v);
  print2(v);
} ///:~
