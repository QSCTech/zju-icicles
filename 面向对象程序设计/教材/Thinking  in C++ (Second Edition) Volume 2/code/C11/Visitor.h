//: C11:Visitor.h
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// The base interface for visitors
// and template for visitable Trash types
#ifndef VISITOR_H
#define VISITOR_H
#include "Trash.h"
#include "Aluminum.h"
#include "Paper.h"
#include "Glass.h"
#include "Cardboard.h"

class Visitor {
public:
  virtual void visit(Aluminum* a) = 0;
  virtual void visit(Paper* p) = 0;
  virtual void visit(Glass* g) = 0;
  virtual void visit(Cardboard* c) = 0;
};

// Template to generate visitable 
// trash types by inheriting from originals:
template<class TrashType> 
class Visitable : public TrashType {
protected:
  Visitable () : TrashType(0) {}
  friend class TrashProtoInit;
public:
  Visitable(double wt) : TrashType(wt) {}
  // Remember "this" is pointer to current type:
  void accept(Visitor& v) { v.visit(this); }
  // Override clone() to create this new type:
  Trash* clone(const Trash::Info& info) {
    return new Visitable(info.data());
  }
};
#endif // VISITOR_H ///:~
