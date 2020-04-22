//: C11:Aluminum.h
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// The Aluminum class with prototyping
#ifndef ALUMINUM_H
#define ALUMINUM_H
#include "Trash.h"

class Aluminum : public Trash {
  static double val;
protected:
  Aluminum() {}
  friend class TrashProtoInit;
public:
  Aluminum(double wt) : Trash(wt) {}
  double value() const { return val; }
  static void value(double newVal) {
    val = newVal;
  }
  std::string id() { return "Aluminum"; }
  Trash* clone(const Info& info) {
    return new Aluminum(info.data());
  }
};
#endif // ALUMINUM_H ///:~
