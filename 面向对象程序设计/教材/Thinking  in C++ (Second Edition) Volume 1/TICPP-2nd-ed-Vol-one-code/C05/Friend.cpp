//: C05:Friend.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Friend allows special access

// Declaration (incomplete type specification):
struct X;

struct Y {
  void f(X*);
};

struct X { // Definition
private:
  int i;
public:
  void initialize();
  friend void g(X*, int); // Global friend
  friend void Y::f(X*);  // Struct member friend
  friend struct Z; // Entire struct is a friend
  friend void h();
};

void X::initialize() { 
  i = 0; 
}

void g(X* x, int i) { 
  x->i = i; 
}

void Y::f(X* x) { 
  x->i = 47; 
}

struct Z {
private:
  int j;
public:
  void initialize();
  void g(X* x);
};

void Z::initialize() { 
  j = 99;
}

void Z::g(X* x) { 
  x->i += j; 
}

void h() {
  X x;
  x.i = 100; // Direct data manipulation
}

int main() {
  X x;
  Z z;
  z.g(&x);
} ///:~
