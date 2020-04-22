//: C03:FileStatic.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// File scope demonstration. Compiling and 
// linking this file with FileStatic2.cpp
// will cause a linker error

// File scope means only available in this file:
static int fs; 

int main() {
  fs = 1;
} ///:~
