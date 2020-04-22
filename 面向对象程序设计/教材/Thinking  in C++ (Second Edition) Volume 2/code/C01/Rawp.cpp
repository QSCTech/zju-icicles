//: C01:Rawp.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Naked pointers
//{L} ../TestSuite/Test
#include <fstream>
#include <cstdlib>
using namespace std;
ofstream out("rawp.out");

class Cat {
public:
  Cat() { out << "Cat()" << endl; }
  ~Cat() { out << "~Cat()" << endl; }
};

class Dog {
public:
  void* operator new(size_t sz) {
    out << "allocating a Dog" << endl;
    throw int(47);
  }
  void operator delete(void* p) {
    out << "deallocating a Dog" << endl;
    ::delete p;
  }
};

class UseResources {
  Cat* bp;
  Dog* op;
public:
  UseResources(int count = 1) {
    out << "UseResources()" << endl;
    bp = new Cat[count];
    op = new Dog;
  }
  ~UseResources() {
    out << "~UseResources()" << endl;
    delete []bp; // Array delete
    delete op;
  }
};

int main() {
  try {
    UseResources ur(3);
  } catch(int) {
    out << "inside handler" << endl;
  }
} ///:~
