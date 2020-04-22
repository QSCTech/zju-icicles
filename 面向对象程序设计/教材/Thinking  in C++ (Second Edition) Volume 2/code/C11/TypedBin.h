//: C11:TypedBin.h
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
#ifndef TYPEDBIN_H
#define TYPEDBIN_H
#include "Trash.h"
#include "Aluminum.h"
#include "Paper.h"
#include "Glass.h"
#include "Cardboard.h"
#include <vector>

// Template to generate double-dispatching
// trash types by inheriting from originals:
template<class TrashType> 
class DD : public TrashType {
protected:
  DD() : TrashType(0) {}
  friend class TrashProtoInit;
public:
  DD(double wt) : TrashType(wt) {}
  bool addToBin(std::vector<TypedBin*>& tb) {
    for(int i = 0; i < tb.size(); i++)
      if(tb[i]->add(this))
        return true;
    return false;
  }
  // Override clone() to create this new type:
  Trash* clone(const Trash::Info& info) {
    return new DD(info.data());
  }
};

// vector<Trash*> that knows how to 
// grab the right type
class TypedBin : public std::vector<Trash*> {
protected:
  bool addIt(Trash* t) {
    push_back(t);
    return true;
  }
public:
  virtual bool add(DD<Aluminum>*) {
    return false;
  }
  virtual bool add(DD<Paper>*) {
    return false;
  }
  virtual bool add(DD<Glass>*) {
    return false;
  }
  virtual bool add(DD<Cardboard>*) {
    return false;
  }
};

// Template to generate specific TypedBins:
template<class TrashType>
class BinOf : public TypedBin {
public:
  // Only overrides add() for this specific type:
  bool add(TrashType* t) { return addIt(t); }
};
#endif // TYPEDBIN_H ///:~
