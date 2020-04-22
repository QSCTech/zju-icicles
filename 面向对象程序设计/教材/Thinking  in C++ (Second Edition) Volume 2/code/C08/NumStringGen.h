//: C08:NumStringGen.h
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// A random number generator that produces 
// strings representing floating-point numbers
#ifndef NUMSTRINGGEN_H
#define NUMSTRINGGEN_H
#include <string>
#include <cstdlib>
#include <ctime>

class NumStringGen {
  const int sz; // Number of digits to make
public:
  NumStringGen(int ssz = 5) : sz(ssz) { 
    std::srand(std::time(0)); 
  }
  std::string operator()() {
    static char n[] = "0123456789";
    const int nsz = 10;
    std::string r(sz, ' ');
    for(int i = 0; i < sz; i++)
      if(i == sz/2)
        r[i] = '.'; // Insert a decimal point
      else
        r[i] = n[std::rand() % nsz];
    return r;
  }
};
#endif // NUMSTRINGGEN_H ///:~
