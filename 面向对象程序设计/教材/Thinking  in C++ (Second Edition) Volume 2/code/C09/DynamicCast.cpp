//: C09:DynamicCast.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Using the standard dynamic_cast operation
//{L} ../TestSuite/Test
#include <cassert>
#include <typeinfo>
using namespace std;

class D1 { 
public:
  virtual void func() {} 
  virtual ~D1() {}
};

class D2 { 
public:
  virtual void bar() {} 
};

class MI : public D1, public D2 {};
class Mi2 : public MI {};

int main() {
  D2* d2 = new Mi2;
  Mi2* mi2 = dynamic_cast<Mi2*>(d2);
  MI* mi = dynamic_cast<MI*>(d2);
  D1* d1 = dynamic_cast<D1*>(d2);
  assert(typeid(d2) != typeid(Mi2*));
  assert(typeid(d2) == typeid(D2*));
} ///:~
