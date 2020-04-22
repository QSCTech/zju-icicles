//: C11:Bicycle.cpp {O}
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Bicycle implementation
#include "Bicycle.h"
#include <map>
#include <algorithm>
#include <cassert>
using namespace std;

// Static member definitions:
LeakChecker BicyclePart::lc;
int Bicycle::counter = 0;

Bicycle::Bicycle() : id(counter++) {
  BicyclePart *bp[] = {
    new Part<Frame>, 
    new Part<Wheel>, new Part<Wheel>, 
    new Part<Seat>, new Part<HandleBar>,
    new Part<Sprocket>,  new Part<Deraileur>,
  };
  const int bplen = sizeof bp / sizeof *bp;
  parts = VBP(bp, bp + bplen);
}

Bicycle::Bicycle(const Bicycle& old) 
  : parts(old.parts.begin(), old.parts.end()) {
  for(int i = 0; i < parts.size(); i++)
    parts[i] = parts[i]->clone();
}

Bicycle& Bicycle::operator=(const Bicycle& old) {
  purge(); // Remove old lvalues
  parts.resize(old.parts.size());
  copy(old.parts.begin(), 
    old.parts.end(), parts.begin());
  for(int i = 0; i < parts.size(); i++)
    parts[i] = parts[i]->clone();
  return *this;
}

void Bicycle::purge() {
  for(VBP::iterator it = parts.begin();
    it != parts.end(); it++) {
      delete *it;
      *it = 0; // Prevent multiple deletes
  }
}

ostream& operator<<(ostream& os, Bicycle* b) {
  copy(b->parts.begin(), b->parts.end(),
    ostream_iterator<BicyclePart*>(os, "\n"));
  os << "--------" << endl;
  return os;
}

void Bicycle::print(vector<Bicycle*>& vb, 
  ostream& os) {
  copy(vb.begin(), vb.end(),
    ostream_iterator<Bicycle*>(os, "\n"));
  cout << "--------" << endl;
} ///:~
