//: C08:PtrFun1.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Using ptr_fun() for single-argument functions
//{L} ../TestSuite/Test
//{-bor}
#include <algorithm>
#include <vector>
#include <iostream>
#include <functional>
using namespace std;

char* n[] = { "01.23", "91.370", "56.661",
  "023.230", "19.959", "1.0", "3.14159" };
const int nsz = sizeof n / sizeof *n;

template<typename InputIter>
void print(InputIter first, InputIter last) {
  while(first != last)
    cout << *first++ << "\t";
  cout << endl;
}

int main() {
  print(n, n + nsz);
  vector<double> vd;
  transform(n, n + nsz, back_inserter(vd), atof);
  print(vd.begin(), vd.end());
  transform(n,n + nsz,vd.begin(), ptr_fun(atof));
  print(vd.begin(), vd.end());
} ///:~
