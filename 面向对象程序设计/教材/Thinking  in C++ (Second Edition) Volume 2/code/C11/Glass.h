//: C11:Glass.h
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// The Glass class with prototyping
#ifndef GLASS_H
#define GLASS_H
#include "Trash.h"

class Glass : public Trash {
  static double val;
protected:
  Glass() {}
  friend class TrashProtoInit;
public:
  Glass(double wt) : Trash(wt) {}
  double value() const { return val; }
  static void value(double newVal) {
    val = newVal;
  }
  std::string id() { return "Glass"; }
  Trash* clone(const Info& info) {
    return new Glass(info.data());
  }
};
#endif // GLASS_H ///:~
