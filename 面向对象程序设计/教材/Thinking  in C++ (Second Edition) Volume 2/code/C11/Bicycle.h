//: C11:Bicycle.h
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Complex class involving dynamic aggregation
#ifndef BICYCLE_H
#define BICYCLE_H
#include <vector>
#include <string>
#include <iostream>
#include <typeinfo>

class LeakChecker {
  int count;
public:
  LeakChecker() : count(0) {}
  void print() {
    std::cout << count << std::endl; 
  }
  ~LeakChecker() { print(); }
  void operator++(int) { count++; }
  void operator--(int) { count--; }
};

class BicyclePart {
  static LeakChecker lc;
public:
  BicyclePart() { lc++; }
  virtual BicyclePart* clone() = 0;
  virtual ~BicyclePart() { lc--; }
  friend std::ostream& 
  operator<<(std::ostream& os, BicyclePart* bp) {
    return os << typeid(*bp).name();
  }
  friend class Bicycle;
};

enum BPart {
  Frame, Wheel, Seat, HandleBar, 
  Sprocket, Deraileur,
};

template<BPart id> 
class Part : public BicyclePart {
public:
  BicyclePart* clone() { return new Part<id>; }
};

class Bicycle {
public:
  typedef std::vector<BicyclePart*> VBP;
  Bicycle();
  Bicycle(const Bicycle& old);
  Bicycle& operator=(const Bicycle& old);
  // [Other operators as needed go here:]
  // [...]
  // [...]
  ~Bicycle() { purge(); }
  // So you can change parts on a bike (but be 
  // careful: you must clean up any objects you
  // remove from the bicycle!)
  VBP& bikeParts() { return parts; }
  friend std::ostream& 
  operator<<(std::ostream& os, Bicycle* b);
  static void print(std::vector<Bicycle*>& vb, 
    std::ostream& os = std::cout);
private:
  static int counter;
  int id;
  VBP parts;
  void purge();
};

// Both the Bicycle and the generator should 
// provide more variety than this. But this gives
// you the idea.
struct BicycleGenerator {
  Bicycle* operator()() {
    return new Bicycle;
  }
}; 
#endif // BICYCLE_H ///:~
