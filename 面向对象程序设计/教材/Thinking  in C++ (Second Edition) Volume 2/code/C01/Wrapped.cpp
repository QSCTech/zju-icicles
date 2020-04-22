//: C01:Wrapped.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Safe, atomic pointers
//{L} ../TestSuite/Test
#include <fstream>
#include <cstdlib>
using namespace std;
ofstream out("wrapped.out");

// Simplified. Yours may have other arguments.
template<class T, int sz = 1> class PWrap {
  T* ptr;
public:
  class RangeError {}; // Exception class
  PWrap() {
    ptr = new T[sz];
    out << "PWrap constructor" << endl;
  }
  ~PWrap() {
    delete []ptr;
    out << "PWrap destructor" << endl;
  }
  T& operator[](int i) throw(RangeError) {
    if(i >= 0 && i < sz) return ptr[i];
    throw RangeError();
  }
};

class Cat {
public:
  Cat() { out << "Cat()" << endl; }
  ~Cat() { out << "~Cat()" << endl; }
  void g() {}
};

class Dog {
public:
  void* operator new[](size_t sz) {
    out << "allocating an Dog" << endl;
    throw int(47);
  }
  void operator delete[](void* p) {
    out << "deallocating an Dog" << endl;
    ::delete p;
  }
};

class UseResources {
  PWrap<Cat, 3> Bonk;
  PWrap<Dog> Og;
public:
  UseResources() : Bonk(), Og() {
    out << "UseResources()" << endl;
  }
  ~UseResources() {
    out << "~UseResources()" << endl;
  }
  void f() { Bonk[1].g(); }
};

int main() {
  try {
    UseResources ur;
  } catch(int) {
    out << "inside handler" << endl;
  } catch(...) {
    out << "inside catch(...)" << endl;
  }
} ///:~
