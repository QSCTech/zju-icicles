//: C08:FindBlanks.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Demonstrate mem_fun_ref() with string::empty()
//{L} ../TestSuite/Test
// Probably a bug in this program:
//{-msc}
//{-bor} dumps core
//{-g++295} dumps core
//{-g++3} dumps core
#include "../require.h"
#include <algorithm>
#include <list>
#include <string>
#include <fstream>
#include <functional>
using namespace std;

typedef list<string>::iterator LSI;

LSI blank(LSI begin, LSI end) {
   return find_if(begin, end, 
     mem_fun_ref(&string::empty));
}

int main(int argc, char* argv[]) {
  char* fname = "FindBlanks.cpp";
  if(argc > 1) fname = argv[1];
  ifstream in(fname);
  assure(in, fname);
  list<string> ls;
  string s;
  while(getline(in, s))
    ls.push_back(s);
  LSI lsi = blank(ls.begin(), ls.end());
  while(lsi != ls.end()) {
    *lsi = "A BLANK LINE";
    lsi = blank(lsi, ls.end());
  }
  string f(argv[1]);
  f += ".out";
  ofstream out(f.c_str());
  copy(ls.begin(), ls.end(), 
    ostream_iterator<string>(out, "\n"));
} ///:~
