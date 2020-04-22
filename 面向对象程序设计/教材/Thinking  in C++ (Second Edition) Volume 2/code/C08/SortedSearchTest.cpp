//: C08:SortedSearchTest.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
//{L} ../C07/StreamTokenizer ../TestSuite/Test
// Test searching in sorted ranges
//{-g++295}
//{-msc}
#include "../C07/StreamTokenizer.h"
#include "PrintSequence.h"
#include "NString.h"
#include "../require.h"
#include <algorithm>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

int main() {
  ifstream in("SortedSearchTest.cpp");
  assure(in, "SortedSearchTest.cpp");
  StreamTokenizer words(in);
  deque<NString> dstr;
  string word;
  while((word = words.next()).size() != 0)
    dstr.push_back(NString(word));
  vector<NString> v(dstr.begin(), dstr.end());
  sort(v.begin(), v.end());
  print(v, "sorted");
  typedef vector<NString>::iterator sit;
  sit it, it2;
  string f("include");
  cout << "binary search: " 
    << binary_search(v.begin(), v.end(), f) 
    << endl;
  it = lower_bound(v.begin(), v.end(), f);
  it2 = upper_bound(v.begin(), v.end(), f);
  print(it, it2, "found range");
  pair<sit, sit> ip = 
    equal_range(v.begin(), v.end(), f);
  print(ip.first, ip.second, 
    "equal_range");
} ///:~
