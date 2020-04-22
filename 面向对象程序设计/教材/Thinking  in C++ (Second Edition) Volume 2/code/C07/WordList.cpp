//: C07:WordList.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Display a list of words used in a document
//{L} ../TestSuite/Test
#include "../require.h"
#include <string>
#include <cstring>
#include <set>
#include <iostream>
#include <fstream>
using namespace std;

const char* delimiters =
  " \t;()\"<>:{}[]+-=&*#.,/\\~";

int main(int argc, char* argv[]) {
  char* fname = "WordList.cpp";
  if(argc > 1) fname = argv[1];
  ifstream in(fname);
  assure(in, fname);
  set<string> wordlist;
  string line;
  while(getline(in, line)) {
    // Capture individual words:
    char* s = // Cast probably won't crash:
      strtok((char*)line.c_str(), delimiters);
    while(s) {
      // Automatic type conversion:
      wordlist.insert(s); 
      s = strtok(0, delimiters);
    }
  }
  // Output results:
  copy(wordlist.begin(), wordlist.end(),
       ostream_iterator<string>(cout, "\n"));
} ///:~
