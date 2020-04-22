//: C10:Vendor.cpp {O}
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Implementation of VENDOR.H
// This is compiled and unavailable to you
#include "Vendor.h"
#include <fstream>
using namespace std;

extern ofstream out; // For trace info

void Vendor::v() const {
  out << "Vendor::v()\n";
}

void Vendor::f() const {
  out << "Vendor::f()\n";
}

Vendor::~Vendor() {
  out << "~Vendor()\n";
}

void Vendor1::v() const {
  out << "Vendor1::v()\n";
}

void Vendor1::f() const {
  out << "Vendor1::f()\n";
}

Vendor1::~Vendor1() {
  out << "~Vendor1()\n";
}

void A(const Vendor& V) {
  // ...
  V.v();
  V.f();
  //..
}

void B(const Vendor& V) {
  // ...
  V.v();
  V.f();
  //..
} ///:~
