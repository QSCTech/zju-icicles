//: C07:TokenIterator.h
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
#ifndef TOKENITERATOR_H
#define TOKENITERATOR_H
#include <string>
#include <iterator>
#include <algorithm>
#include <cctype>

struct Isalpha { 
  bool operator()(char c) { 
    using namespace std; //[[For a compiler bug]]
    return isalpha(c); 
  }
};

class Delimiters {
  std::string exclude;
public:
  Delimiters() {}
  Delimiters(const std::string& excl) 
    : exclude(excl) {}
  bool operator()(char c) {
    return exclude.find(c) == std::string::npos;
  }
};

template <class InputIter, class Pred = Isalpha>
class TokenIterator: public std::iterator<
  std::input_iterator_tag,std::string,ptrdiff_t>{
  InputIter first;
  InputIter last;
  std::string word;
  Pred predicate;
public:
  TokenIterator(InputIter begin, InputIter end, 
    Pred pred = Pred()) 
    : first(begin), last(end), predicate(pred) {
      ++*this; 
  }
  TokenIterator() {} // End sentinel
  // Prefix increment:
  TokenIterator& operator++() {
    word.resize(0);
    first = std::find_if(first, last, predicate);
    while (first != last && predicate(*first))
      word += *first++;
    return *this;
  }
  // Postfix increment
  class Proxy { 
    std::string word;
  public:
    Proxy(const std::string& w) : word(w) {}
    std::string operator*() { return word; } 
  };
  Proxy operator++(int) { 
    Proxy d(word);
    ++*this; 
    return d; 
  }
  // Produce the actual value:
  std::string operator*() const { return word; }
  std::string* operator->() const {
    return &(operator*()); 
  }
  // Compare iterators:
  bool operator==(const TokenIterator&) { 
    return word.size() == 0 && first == last; 
  }
  bool operator!=(const TokenIterator& rv) { 
    return !(*this == rv);
  }
};
#endif // TOKENITERATOR_H ///:~
