//: C03:Global2.cpp {O}
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Accessing external global variables
extern int globe;  
// (The linker resolves the reference)
void func() {
  globe = 47;
} ///:~
