//: C08:TransformNames.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// More use of transform()
//{L} ../TestSuite/Test
//{-g++295}
//{-msc}
#include "Inventory.h"
#include "PrintSequence.h"
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

struct NewImproved {
  Inventory operator()(const Inventory& inv) {
    return Inventory(toupper(inv.getItem()), 
      inv.getQuantity(), inv.getValue());
  }
};

int main() {
  vector<Inventory> vi;
  generate_n(back_inserter(vi), 15, InvenGen());
  print(vi, "vi");
  transform(vi.begin(), vi.end(), vi.begin(),
    NewImproved());
  print(vi, "vi");
} ///:~
