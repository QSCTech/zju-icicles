//: C10:Oof.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Second file
//{L} Out
#include <fstream>
extern std::ofstream out;
class Oof {
public:
  Oof() { out << "ouch"; }
} oof;
int main() {} ///:~
