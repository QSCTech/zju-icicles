//: C08:Binder2.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// More binders
//{L} ../TestSuite/Test
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <functional>
using namespace std;

int main() {
  ostream_iterator<string> out(cout, " ");
  vector<string> v, r;
  v.push_back("Hi");
  v.push_back("Hi");
  v.push_back("Hey");
  v.push_back("Hee");
  v.push_back("Hi");
  copy(v.begin(), v.end(), out);
  cout << endl;
  // Replace each "Hi" with "Ho":
  replace_copy_if(v.begin(), v.end(), 
    back_inserter(r), 
    bind2nd(equal_to<string>(), "Hi"), "Ho");
  copy(r.begin(), r.end(), out);
  cout << endl;
  // Replace anything that's not "Hi" with "Ho":
  replace_if(v.begin(), v.end(), 
    not1(bind2nd(equal_to<string>(),"Hi")),"Ho");
  copy(v.begin(), v.end(), out);
  cout << endl;
} ///:~
