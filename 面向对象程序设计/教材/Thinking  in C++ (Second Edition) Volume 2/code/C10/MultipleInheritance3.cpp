//: C10:MultipleInheritance3.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Virtual base initialization.
// Virtual base classes must always be
// Initialized by the "most-derived" class.
//{L} ../TestSuite/Test
#include "../purge.h"
#include <iostream>
#include <vector>
using namespace std;

class MBase {
public:
  MBase(int) {}
  virtual char* vf() const = 0;
  virtual ~MBase() {}
};

class D1 : virtual public MBase {
public:
  D1() : MBase(1) {}
  char* vf() const { return "D1"; }
};

class D2 : virtual public MBase {
public:
  D2() : MBase(2) {}
  char* vf() const { return "D2"; }
};

class MI : public D1, public D2 {
public:
  MI() : MBase(3) {}
  char* vf() const {
    return D1::vf(); // MUST disambiguate
  }
};

class X : public MI {
public:
  // You must ALWAYS init the virtual base:
  X() : MBase(4) {}
};

int main() {
  vector<MBase*> b;
  b.push_back(new D1);
  b.push_back(new D2);
  b.push_back(new MI); // OK
  b.push_back(new X);
  for(int i = 0; i < b.size(); i++)
    cout << b[i]->vf() << endl;
  purge(b);
} ///:~
