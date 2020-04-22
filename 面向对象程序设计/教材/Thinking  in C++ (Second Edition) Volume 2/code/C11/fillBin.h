//: C11:fillBin.h
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Open a file and parse its contents into
// Trash objects, placing each into a vector
#ifndef FILLBIN_H
#define FILLBIN_H
#include "Fillablevector.h"
#include <vector>
#include <string>

void 
fillBin(std::string filename, Fillable& bin);

// Special case to handle vector:
inline void fillBin(std::string filename, 
  std::vector<Trash*>& bin) {
  Fillablevector fv(bin);
  fillBin(filename, fv);
}
#endif // FILLBIN_H ///:~
