//: C10:FriendInjection.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
namespace Me {
  class Us {
    //...
    friend void you();
  };
} 
int main() {} ///:~
