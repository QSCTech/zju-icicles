//: C01:Catchref.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Why catch by reference?
//{L} ../TestSuite/Test
#include <iostream>
using namespace std;

class Base {
public:
  virtual void what() {
    cout << "Base" << endl;
  }
};

class Derived : public Base {
public:
  void what() {
    cout << "Derived" << endl;
  }
};

void f() { throw Derived(); }

int main() {
  try {
    f();
  } catch(Base b) {
    b.what();
  }
  try {
    f();
  } catch(Base& b) {
    b.what();
  }
} ///:~
