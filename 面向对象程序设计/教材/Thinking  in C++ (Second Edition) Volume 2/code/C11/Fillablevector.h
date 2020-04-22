//: C11:Fillablevector.h
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Adapter that makes a vector<Trash*> Fillable
#ifndef FILLABLEVECTOR_H
#define FILLABLEVECTOR_H
#include "Trash.h"
#include "Fillable.h"
#include <vector>

class Fillablevector : public Fillable {
  std::vector<Trash*>& v;
public:
  Fillablevector(std::vector<Trash*>& vv) 
    : v(vv) {}
  void addTrash(Trash* t) { v.push_back(t); }
};
#endif // FILLABLEVECTOR_H ///:~
