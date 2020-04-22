//: C07:AnonymousUnion.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
int main() {
  union { 
    int i; 
    float f; 
  };
  // Access members without using qualifiers:
  i = 12;
  f = 1.22;
} ///:~
