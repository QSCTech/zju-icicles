#ifndef person_h
#define person_h

#include <stdio.h>
#include <stdlib.h>
#define NAMEMAX 8
typedef struct {
    char name[NAMEMAX+1];
    int age;
    int worth;
}_person;
typedef _person * person;
void printPerson(person P);
int comparePerson(person I,person J);

#endif
