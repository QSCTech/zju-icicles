#include "person.h"
void printPerson(person P)//handy for printing Person, used in queries
{
     printf("%s %d %d\n",P->name,P->age,P->worth);
}
int compareName(char * I,char * J)//name non-decreasing alphabetical order, dictionary order
{
    int i;
    for(i=0;I[i]==J[i];i++);//find the first different char
    return I[i]-J[i]<0;
}
int comparePerson(person I,person J)//if Order(I)>Order(J), return 1; else return 0.
{
    if(I->worth>J->worth){return 1;}//I is richer than J
    else if(I->worth<J->worth){return 0;}
    else
    {//the same worth, compare age non-decreasing
        if(I->age<J->age){return 1;}
        else if(I->age>J->age){return 0;}
        else{return compareName(I->name,J->name);}//the same age, compare name non-decreasing
    }
}
