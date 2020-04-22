//: C05:Class.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Similarity of struct and class

struct A {
private:
  int i, j, k;
public:
  int f();
  void g();
};

int A::f() { 
  return i + j + k; 
}

void A::g() { 
  i = j = k = 0; 
}

// Identical results are produced with:

class B {
  int i, j, k;
public:
  int f();
  void g();
};

int B::f() { 
  return i + j + k; 
}

void B::g() { 
  i = j = k = 0; 
} 

int main() {
  A a;
  B b;
  a.f(); a.g();
  b.f(); b.g();
} ///:~
