//: C11:sumValue.h
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Sums the value of Trash in any type of STL
// container of any specific type of Trash:
#ifndef SUMVALUE_H
#define SUMVALUE_H
#include <typeinfo>
#include <vector>

template<typename Cont>
void sumValue(const Cont& bin) {
  double val = 0.0f;
  typename 
    Cont::const_iterator tally = bin.begin();
  while(tally != bin.end()) {
    val +=(*tally)->weight() * (*tally)->value();
    out << "weight of "
        << typeid(*(*tally)).name()
        << " = " << (*tally)->weight() 
        << endl;
    tally++;
  }
  out << "Total value = " << val << endl;
}
#endif // SUMVALUE_H ///:~
