//: C09:Selfrtti.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Your own RTTI system
//{L} ../TestSuite/Test
#include "../purge.h"
#include <iostream>
#include <vector>
using namespace std;

class Security {
protected:
  enum { baseID = 1000 };
public:
  virtual int dynamic_type(int id) {
    if(id == baseID) return 1;
    return 0;
  }
};

class Stock : public Security {
protected:
  enum { typeID = baseID + 1 };
public:
  int dynamic_type(int id) {
    if(id == typeID) return 1;
    return Security::dynamic_type(id);
  }
  static Stock* dynacast(Security* s) {
    if(s->dynamic_type(typeID))
      return (Stock*)s;
    return 0;
  }
};

class Bond : public Security {
protected:
  enum { typeID = baseID + 2 };
public:
  int dynamic_type(int id) {
    if(id == typeID) return 1;
    return Security::dynamic_type(id);
  }
  static Bond* dynacast(Security* s) {
    if(s->dynamic_type(typeID))
      return (Bond*)s;
    return 0;
  }
};

class Commodity : public Security {
protected:
  enum { typeID = baseID + 3 };
public:
  int dynamic_type(int id) {
    if(id == typeID) return 1;
    return Security::dynamic_type(id);
  }
  static Commodity* dynacast(Security* s) {
    if(s->dynamic_type(typeID))
      return (Commodity*)s;
    return 0;
  }
  void special() {
    cout << "special Commodity function\n";
  }
};

class Metal : public Commodity {
protected:
  enum { typeID = baseID + 4 };
public:
  int dynamic_type(int id) {
    if(id == typeID) return 1;
    return Commodity::dynamic_type(id);
  }
  static Metal* dynacast(Security* s) {
    if(s->dynamic_type(typeID))
      return (Metal*)s;
    return 0;
  }
};

int main() {
  vector<Security*> portfolio;
  portfolio.push_back(new Metal);
  portfolio.push_back(new Commodity);
  portfolio.push_back(new Bond);
  portfolio.push_back(new Stock);
  vector<Security*>::iterator it = 
    portfolio.begin();
  while(it != portfolio.end()) {
    Commodity* cm = Commodity::dynacast(*it);
    if(cm) cm->special();
    else cout << "not a Commodity" << endl;
    it++;
  }
  cout << "cast from intermediate pointer:\n";
  Security* sp = new Metal;
  Commodity* cp = Commodity::dynacast(sp);
  if(cp) cout << "it's a Commodity\n";
  Metal* mp = Metal::dynacast(sp);
  if(mp) cout << "it's a Metal too!\n";
  purge(portfolio);
} ///:~
