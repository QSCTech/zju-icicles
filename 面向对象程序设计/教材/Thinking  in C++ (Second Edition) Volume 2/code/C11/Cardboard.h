//: C11:Cardboard.h
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// The Cardboard class with prototyping
#ifndef CARDBOARD_H
#define CARDBOARD_H
#include "Trash.h"

class Cardboard : public Trash {
  static double val;
protected:
  Cardboard() {}
  friend class TrashProtoInit;
public:
  Cardboard(double wt) : Trash(wt) {}
  double value() const { return val; }
  static void value(double newVal) {
    val = newVal;
  }
  std::string id() { return "Cardboard"; }
  Trash* clone(const Info& info) {
    return new Cardboard(info.data());
  }
};
#endif // CARDBOARD_H ///:~
