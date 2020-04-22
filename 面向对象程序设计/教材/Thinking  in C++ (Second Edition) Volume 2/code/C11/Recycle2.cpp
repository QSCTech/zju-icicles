//: C11:Recycle2.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Adding a factory method
//{L} ../TestSuite/Test
#include "sumValue.h"
#include "../purge.h"
#include <fstream>
#include <vector>
#include <typeinfo>
#include <cstdlib>
#include <ctime>
using namespace std;
ofstream out("Recycle2.out");

class Trash {
  double _weight;
  void operator=(const Trash&);
  Trash(const Trash&);
public:
  Trash(double wt) : _weight(wt) { }
  virtual double value() const = 0;
  double weight() const { return _weight; }
  virtual ~Trash() {}
  // Nested class because it's tightly coupled
  // to Trash:
  class Info {
    int type;
    // Must change this to add another type:
    enum { maxnum = 3 };
    double data;
    friend class Trash;
  public:
    Info(int typeNum, double dat)
      : type(typeNum % maxnum), data(dat) {}
  };
  static Trash* factory(const Info& info);
};

class Aluminum : public Trash {
  static double val;
public:
  Aluminum(double wt) : Trash(wt) {}
  double value() const { return val; }
  static void value(double newval) {
    val = newval;
  }
  ~Aluminum() { out << "~Aluminum\n"; }
};

double Aluminum::val = 1.67F;

class Paper : public Trash {
  static double val;
public:
  Paper(double wt) : Trash(wt) {}
  double value() const { return val; }
  static void value(double newval) {
    val = newval;
  }
  ~Paper() { out << "~Paper\n"; }
};

double Paper::val = 0.10F;

class Glass : public Trash {
  static double val;
public:
  Glass(double wt) : Trash(wt) {}
  double value() const { return val; }
  static void value(double newval) {
    val = newval;
  }
  ~Glass() { out << "~Glass\n"; }
};

double Glass::val = 0.23F;

// Definition of the factory method. It must know
// all the types, so is defined after all the
// subtypes are defined:
Trash* Trash::factory(const Info& info) {
  switch(info.type) {
    default: // In case of overrun
    case 0:
      return new Aluminum(info.data);
    case 1:
      return new Paper(info.data);
    case 2:
      return new Glass(info.data);
  }
}

// Generator for Info objects:
class InfoGen {
  int typeQuantity;
  int maxWeight;
public:
  InfoGen(int typeQuant, int maxWt)
    : typeQuantity(typeQuant), maxWeight(maxWt) {
    srand(time(0)); 
  }
  Trash::Info operator()() {
    return Trash::Info(rand() % typeQuantity, 
      static_cast<double>(rand() % maxWeight));
  }
};

int main() {
  vector<Trash*> bin;
  // Fill up the Trash bin:
  InfoGen infoGen(3, 100);
  for(int i = 0; i < 30; i++)
    bin.push_back(Trash::factory(infoGen()));
  vector<Aluminum*> alBin;
  vector<Paper*> paperBin;
  vector<Glass*> glassBin;
  vector<Trash*>::iterator sorter = bin.begin();
  // Sort the Trash:
  while(sorter != bin.end()) {
    Aluminum* ap = 
      dynamic_cast<Aluminum*>(*sorter);
    Paper* pp = dynamic_cast<Paper*>(*sorter);
    Glass* gp = dynamic_cast<Glass*>(*sorter);
    if(ap) alBin.push_back(ap);
    if(pp) paperBin.push_back(pp);
    if(gp) glassBin.push_back(gp);
    sorter++;
  }
  sumValue(alBin);
  sumValue(paperBin);
  sumValue(glassBin);
  sumValue(bin);
  purge(bin); // Cleanup
} ///:~
