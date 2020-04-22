//: C03:AllDefinitions.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// All possible combinations of basic data types, 
// specifiers, pointers and references
#include <iostream>
using namespace std;

void f1(char c, int i, float f, double d);
void f2(short int si, long int li, long double ld);
void f3(unsigned char uc, unsigned int ui, 
  unsigned short int usi, unsigned long int uli);
void f4(char* cp, int* ip, float* fp, double* dp);
void f5(short int* sip, long int* lip, 
  long double* ldp);
void f6(unsigned char* ucp, unsigned int* uip, 
  unsigned short int* usip, 
  unsigned long int* ulip);
void f7(char& cr, int& ir, float& fr, double& dr);
void f8(short int& sir, long int& lir, 
  long double& ldr);
void f9(unsigned char& ucr, unsigned int& uir, 
  unsigned short int& usir, 
  unsigned long int& ulir);

int main() {} ///:~
