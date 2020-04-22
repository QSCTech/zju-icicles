//: C03:Forward.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Forward function & data declarations
#include <iostream>
using namespace std;

// This is not actually external, but the 
// compiler must be told it exists somewhere:
extern int i; 
extern void func();
int main() {
  i = 0;
  func();
}
int i; // The data definition
void func() {
  i++;
  cout << i;
} ///:~
