//: C11:BikeTest.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
//{L} Bicycle ../TestSuite/Test
#include "Bicycle.h"
#include <algorithm>
using namespace std;

int main() {
  vector<Bicycle*> bikes;
  BicycleGenerator bg;
  generate_n(back_inserter(bikes), 12, bg);
  Bicycle::print(bikes);
} ///:~
