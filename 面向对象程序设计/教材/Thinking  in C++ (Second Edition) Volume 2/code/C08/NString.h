//: C08:NString.h
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// A "numbered string" that indicates which
// occurrence this is of a particular word
#ifndef NSTRING_H
#define NSTRING_H
#include <string>
#include <map>
#include <iostream>

class NString {
  std::string s;
  int occurrence;
  struct Counter {
    int i;
    Counter() : i(0) {}
    Counter& operator++(int) { 
      i++;
      return *this;
    } // Post-incr
    operator int() { return i; }
  };
  // Keep track of the number of occurrences:
  typedef std::map<std::string, Counter> csmap;
  static csmap occurMap;
public:
  NString() : occurrence(0) {}
  NString(const std::string& x) 
    : s(x), occurrence(occurMap[s]++) {}
  NString(const char* x) 
    : s(x), occurrence(occurMap[s]++) {}
  // The synthesized operator= and 
  // copy-constructor are OK here
  friend std::ostream& operator<<(
    std::ostream& os, const NString& ns) {
    return os << ns.s << " [" 
      << ns.occurrence << "]";
  }
  // Need this for sorting. Notice it only 
  // compares strings, not occurrences:
  friend bool 
  operator<(const NString& l, const NString& r) {
    return l.s < r.s;
  }
  // For sorting with greater<NString>:
  friend bool 
  operator>(const NString& l, const NString& r) {
    return l.s > r.s;
  }
  // To get at the string directly:
  operator const std::string&() const {return s;}
};

// Allocate static member object. Done here for
// brevity, but should actually be done in a 
// separate cpp file:
NString::csmap NString::occurMap;
#endif // NSTRING_H ///:~
