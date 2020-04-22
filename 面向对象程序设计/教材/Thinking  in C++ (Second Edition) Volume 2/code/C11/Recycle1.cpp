//: C11:Recycle1.cpp 
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Recycling with RTTI
//{L} ../TestSuite/Test
#include "sumValue.h"
#include "../purge.h"
#include <fstream>
#include <vector>
#include <typeinfo>
#include <cstdlib>
#include <ctime>
using namespace std;
ofstream out("Recycle1.out");

class Trash {
  double _weight;
  static int _count; // # created
  static int _dcount; // # destroyed
  // disallow automatic creation of
  // assignment & copy-constructor:
  void operator=(const Trash&);
  Trash(const Trash&);
public:
  Trash(double wt) : _weight(wt) { 
    _count++; 
  }
  virtual double value() const = 0;
  double weight() const { return _weight; }
  static int count() { return _count; }
  static int dcount() { return _dcount;}
  virtual ~Trash() { _dcount++; }
};

int Trash::_count = 0;
int Trash::_dcount = 0;

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

class TrashGen {
public:
  TrashGen() { srand(time(0)); }
  static double frand(int mod) {
    return static_cast<double>(rand() % mod);
  }
  Trash* operator()() {
    for(int i = 0; i < 30; i++)
      switch(rand() % 3) {
        case 0 :
          return new Aluminum(frand(100));
        case 1 :
          return new Paper(frand(100));
        case 2 :
          return new Glass(frand(100));
      }
    return new Aluminum(0);
    // Or throw exeception...
  }
};

int main() {
  vector<Trash*> bin;
  // Fill up the Trash bin:
  generate_n(back_inserter(bin), 30, TrashGen());
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
  out << "total created = "
      << Trash::count() << endl;
  purge(bin);
  out << "total destroyed = "
      << Trash::dcount() << endl;
} ///:~
