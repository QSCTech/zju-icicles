//: C11:Trash.h
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Base class for Trash recycling examples
#ifndef TRASH_H
#define TRASH_H
#include <iostream>
#include <exception>
#include <vector>
#include <string>

class TypedBin; // For a later example
class Visitor; // For a later example

class Trash {
  double _weight;
  void operator=(const Trash&);
  Trash(const Trash&);
public:
  Trash(double wt) : _weight(wt) {}
  virtual double value() const = 0;
  double weight() const { return _weight; }
  virtual ~Trash() {}
  class Info {
    std::string _id;
    double _data;
  public:
    Info(std::string ident, double dat)
      : _id(ident), _data(dat) {}
    double data() const { return _data; }
    std::string id() const { return _id; }
    friend std::ostream& operator<<(
      std::ostream& os, const Info& info) {
      return os << info._id << ':' << info._data;
    }
  };
protected:
  // Remainder of class provides support for
  // prototyping:
  static std::vector<Trash*> prototypes;
  friend class TrashProtoInit;
  Trash() : _weight(0) {}
public:
  static Trash* factory(const Info& info);
  virtual std::string id() = 0;  // type ident
  virtual Trash* clone(const Info&) = 0;
  // Stubs, inserted for later use:
  virtual bool 
  addToBin(std::vector<TypedBin*>&) { 
    return false; 
  }
  virtual void accept(Visitor&) {};
};
#endif // TRASH_H ///:~
