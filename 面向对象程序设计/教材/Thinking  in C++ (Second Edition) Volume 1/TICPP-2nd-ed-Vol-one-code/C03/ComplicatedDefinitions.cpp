//: C03:ComplicatedDefinitions.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt

/* 1. */     void * (*(*fp1)(int))[10];

/* 2. */     float (*(*fp2)(int,int,float))(int);

/* 3. */     typedef double (*(*(*fp3)())[10])();
             fp3 a;

/* 4. */     int (*(*f4())[10])();

int main() {} ///:~
