//: C09:RTTIWithoutPolymorphism.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
//{L} ../TestSuite/Test
#include <cassert>
#include <typeinfo>
using namespace std;

class X {
 int i; 
public:
  // ...
};

class Y : public X { 
  int j;
public:
  // ...
};

int main() {
  X* xp = new Y;
  assert(typeid(*xp) == typeid(X));
  assert(typeid(*xp) != typeid(Y));
} ///:~
