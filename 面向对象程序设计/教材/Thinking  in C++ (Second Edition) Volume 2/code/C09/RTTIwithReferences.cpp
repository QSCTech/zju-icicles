//: C09:RTTIwithReferences.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
//{L} ../TestSuite/Test
#include <cassert>
#include <typeinfo>
using namespace std;

class B {
public:
  virtual float f() { return 1.0;}
  virtual ~B() {}
};

class D : public B { /* ... */ };

int main() {
  B* p = new D;
  B& r = *p;
  assert(typeid(p) == typeid(B*));
  assert(typeid(p) != typeid(D*));
  assert(typeid(r) == typeid(D));
  assert(typeid(*p) == typeid(D));
  assert(typeid(*p) != typeid(B));
  assert(typeid(&r) == typeid(B*));
  assert(typeid(&r) != typeid(D*));
  assert(typeid(r.f()) == typeid(float));
} ///:~
