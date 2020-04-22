//: C07:BitSet.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Exercising the bitset class
//{L} ../TestSuite/Test
//{-bor}
//{-g++295}
//{-g++3}
#include <iostream>
#include <bitset>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <string>
using namespace std;
const int sz = 32;
typedef bitset<sz> BS;

template<int bits>
bitset<bits> randBitset() {
  bitset<bits> r(rand());
  for(int i = 0; i < bits/16 - 1; i++) {
    r <<= 16;
    // "OR" together with a new lower 16 bits:
    r |= bitset<bits>(rand()); 
  }
  return r;
}  

int main() {
  srand(time(0));
  cout << "sizeof(bitset<16>) = " 
    << sizeof(bitset<16>) << endl;
  cout << "sizeof(bitset<32>) = " 
    << sizeof(bitset<32>) << endl;
  cout << "sizeof(bitset<48>) = " 
    << sizeof(bitset<48>) << endl;
  cout << "sizeof(bitset<64>) = " 
    << sizeof(bitset<64>) << endl;
  cout << "sizeof(bitset<65>) = " 
    << sizeof(bitset<65>) << endl;
  BS a(randBitset<sz>()), b(randBitset<sz>());
  // Converting from a bitset:
  unsigned long ul = a.to_ulong();
  string s = b.to_string();
  // Converting a string to a bitset:
  char* cbits = "111011010110111";
  cout << "char* cbits = " << cbits <<endl;
  cout << BS(cbits) << " [BS(cbits)]" << endl;
  cout << BS(cbits, 2) 
    << " [BS(cbits, 2)]" << endl;
  cout << BS(cbits, 2, 11)
    << " [BS(cbits, 2, 11)]" << endl;
  cout << a << " [a]" << endl;
  cout << b << " [b]"<< endl;
  // Bitwise AND:
  cout << (a & b) << " [a & b]" << endl;
  cout << (BS(a) &= b) << " [a &= b]" << endl;
  // Bitwise OR:
  cout << (a | b) << " [a | b]" << endl;
  cout << (BS(a) |= b) << " [a |= b]" << endl;
  // Exclusive OR:
  cout << (a ^ b) << " [a ^ b]" << endl;
  cout << (BS(a) ^= b) << " [a ^= b]" << endl;
  cout << a << " [a]" << endl; // For reference
  // Logical left shift (fill with zeros):
  cout << (BS(a) <<= sz/2) 
    << " [a <<= (sz/2)]" << endl;
  cout << (a << sz/2) << endl;
  cout << a << " [a]" << endl; // For reference
  // Logical right shift (fill with zeros):
  cout << (BS(a) >>= sz/2) 
    << " [a >>= (sz/2)]" << endl;
  cout << (a >> sz/2) << endl;
  cout << a << " [a]" << endl; // For reference
  cout << BS(a).set() << " [a.set()]" << endl;
  for(int i = 0; i < sz; i++)
    if(!a.test(i)) {
      cout << BS(a).set(i) 
        << " [a.set(" << i <<")]" << endl;
      break; // Just do one example of this
    }
  cout << BS(a).reset() << " [a.reset()]"<< endl;
  for(int j = 0; j < sz; j++)
    if(a.test(j)) {
      cout << BS(a).reset(j) 
        << " [a.reset(" << j <<")]" << endl;
      break; // Just do one example of this
    }
  cout << BS(a).flip() << " [a.flip()]" << endl;
  cout << ~a << " [~a]" << endl;  
  cout << a << " [a]" << endl; // For reference
  cout << BS(a).flip(1) << " [a.flip(1)]"<< endl;
  BS c;
  cout << c << " [c]" << endl;
  cout << "c.count() = " << c.count() << endl;
  cout << "c.any() = " 
    << (c.any() ? "true" : "false") << endl;
  cout << "c.none() = " 
    << (c.none() ? "true" : "false") << endl;
  c[1].flip(); c[2].flip();
  cout << c << " [c]" << endl;
  cout << "c.count() = " << c.count() << endl;
  cout << "c.any() = " 
    << (c.any() ? "true" : "false") << endl;
  cout << "c.none() = " 
    << (c.none() ? "true" : "false") << endl;
  // Array indexing operations:
  c.reset();
  for(int k = 0; k < c.size(); k++)
    if(k % 2 == 0)
      c[k].flip();
  cout << c << " [c]" << endl;
  c.reset();
  // Assignment to bool:
  for(int ii = 0; ii < c.size(); ii++)
    c[ii] = (rand() % 100) < 25;
  cout << c << " [c]" << endl;
  // bool test:
  if(c[1] == true) 
    cout << "c[1] == true"; 
  else 
    cout << "c[1] == false" << endl;
} ///:~
