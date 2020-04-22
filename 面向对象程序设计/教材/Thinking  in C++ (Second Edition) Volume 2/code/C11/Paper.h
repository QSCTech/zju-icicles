//: C11:Paper.h
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// The Paper class with prototyping
#ifndef PAPER_H
#define PAPER_H
#include "Trash.h"

class Paper : public Trash {
  static double val;
protected:
  Paper() {}
  friend class TrashProtoInit;
public:
  Paper(double wt) : Trash(wt) {}
  double value() const { return val; }
  static void value(double newVal) {
    val = newVal;
  }
  std::string id() { return "Paper"; }
  Trash* clone(const Info& info) {
    return new Paper(info.data());
  }
};
#endif // PAPER_H ///:~
