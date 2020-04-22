//: C10:SimpleStaticMemberFunction.cpp 
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
class X {
public:
  static void f(){};
};

int main() {
  X::f();
} ///:~
