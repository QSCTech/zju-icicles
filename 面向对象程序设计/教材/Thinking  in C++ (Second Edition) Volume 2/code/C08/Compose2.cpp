//: C08:Compose2.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Using the SGI STL compose2() function
//{L} ../TestSuite/Test
//{-bor} Can add the header by hand
//{-msc} Can add the header by hand
#include "copy_if.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <functional>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
  srand(time(0));
  vector<int> v(100);
  generate(v.begin(), v.end(), rand);
  transform(v.begin(), v.end(), v.begin(),
    bind2nd(divides<int>(), RAND_MAX/100));
  vector<int> r;
  copy_if(v.begin(), v.end(), back_inserter(r),
    compose2(logical_and<bool>(),
      bind2nd(greater_equal<int>(), 30),
      bind2nd(less_equal<int>(), 40)));
  sort(r.begin(), r.end());
  copy(r.begin(), r.end(),
    ostream_iterator<int>(cout, " "));
  cout << endl;
} ///:~
