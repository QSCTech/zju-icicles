//: C07:StreamTokenizer.h
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// C++ Replacement for Standard C strtok()
#ifndef STREAMTOKENIZER_H
#define STREAMTOKENIZER_H
#include <string>
#include <iostream>
#include <iterator>
  
class StreamTokenizer {
  typedef std::istreambuf_iterator<char> It;
  It p, end;
  std::string delimiters;
  bool isDelimiter(char c) {
    return 
      delimiters.find(c) != std::string::npos;
  }
public:
  StreamTokenizer(std::istream& is, 
    std::string delim = " \t\n;()\"<>:{}[]+-=&*#"
    ".,/\\~!0123456789") : p(is), end(It()),
    delimiters(delim) {}
  std::string next(); // Get next token
};
#endif STREAMTOKENIZER_H ///:~
