//: C11:TrashVisitor.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
//{L} VisitorTrashPInit ../TestSuite/Test
//{L} fillBin Trash TrashStat 
//{-msc}
// The "visitor" pattern
#include "Visitor.h"
#include "fillBin.h"
#include "../purge.h"
#include <iostream>
#include <fstream>
using namespace std;
ofstream out("TrashVisitor.out");

// Specific group of algorithms packaged
// in each implementation of Visitor:
class PriceVisitor : public Visitor {
  double alSum; // Aluminum
  double pSum; // Paper
  double gSum; // Glass
  double cSum; // Cardboard
public:
  void visit(Aluminum* al) {
    double v = al->weight() * al->value();
    out << "value of Aluminum= " << v << endl;
    alSum += v;
  }
  void visit(Paper* p) {
    double v = p->weight() * p->value();
    out << 
      "value of Paper= " << v << endl;
    pSum += v;
  }
  void visit(Glass* g) {
    double v = g->weight() * g->value();
    out << 
      "value of Glass= " << v << endl;
    gSum += v;
  }
  void visit(Cardboard* c) {
    double v = c->weight() * c->value();
    out << 
      "value of Cardboard = " << v << endl;
    cSum += v;
  }
  void total(ostream& os) {
    os <<
      "Total Aluminum: $" << alSum << "\n" <<
      "Total Paper: $" << pSum << "\n" <<
      "Total Glass: $" << gSum << "\n" <<
      "Total Cardboard: $" << cSum << endl;
  }
};

class WeightVisitor : public Visitor {
  double alSum; // Aluminum
  double pSum; // Paper
  double gSum; // Glass
  double cSum; // Cardboard
public:
  void visit(Aluminum* al) {
    alSum += al->weight();
    out << "weight of Aluminum = "
        << al->weight() << endl;
  }
  void visit(Paper* p) {
    pSum += p->weight();
    out << "weight of Paper = " 
      << p->weight() << endl;
  }
  void visit(Glass* g) {
    gSum += g->weight();
    out << "weight of Glass = "
        << g->weight() << endl;
  }
  void visit(Cardboard* c) {
    cSum += c->weight();
    out << "weight of Cardboard = "
        << c->weight() << endl;
  }
  void total(ostream& os) {
    os << "Total weight Aluminum:"
       << alSum << endl;
    os << "Total weight Paper:"
       << pSum << endl;
    os << "Total weight Glass:"
       << gSum << endl;
    os << "Total weight Cardboard:" 
       << cSum << endl;
  }
};

int main() {
  vector<Trash*> bin;
  // fillBin() still works, without changes, but
  // different objects are prototyped:
  fillBin("Trash.dat", bin);
  // You could even iterate through
  // a list of visitors!
  PriceVisitor pv;
  WeightVisitor wv;
  vector<Trash*>::iterator it = bin.begin();
  while(it != bin.end()) {
    (*it)->accept(pv);
    (*it)->accept(wv);
    it++;
  }
  pv.total(out);
  wv.total(out);
  purge(bin);
} ///:~
