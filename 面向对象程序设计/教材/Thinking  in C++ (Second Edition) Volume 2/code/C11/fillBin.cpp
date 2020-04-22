//: C11:fillBin.cpp {O}
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Implementation of fillBin()
#include "fillBin.h"
#include "Fillable.h"
#include "../C04/trim.h"
#include "../require.h"
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

void fillBin(string filename, Fillable& bin) {
  ifstream in(filename.c_str());
  assure(in, filename.c_str());
  string s;
  while(getline(in, s)) {
    int comma = s.find(',');
    // Parse each line into entries:
    while(comma != string::npos) {
      string e = trim(s.substr(0,comma));
      // Parse each entry:
      int colon = e.find(':');
      string type = e.substr(0, colon);
      double weight = 
        atof(e.substr(colon + 1).c_str());
      bin.addTrash(
        Trash::factory(
          Trash::Info(type, weight)));
      // Move to next part of line:
      s = s.substr(comma + 1);
      comma = s.find(',');
    }
  }
} ///:~
