#include <stdio.h>
#define TOTAL_FLIGHTS 100

/* Structure definition */
struct flightType {
  char flightNum[7];  /* Max 6 characters        */
  int altitude;       /* in meters               */
  int longitude;      /* in tenths of degrees    */
  int latitude;       /* in tenths of degrees    */
  int heading;        /* in tenths of degrees    */
  double airSpeed;    /* in kilometers/hour      */
};

typedef struct flightType Flight;

int  Collide(Flight *planeA, Flight *planeB);
void PotentialCollisions(Flight planes[]);

int Collide(Flight *planeA, Flight *planeB)
{
  if (planeA->altitude == planeB->altitude) {
 
    /** More logic to detect collision goes here **/
  }
  else
    return 0;
}

void PotentialCollisions(Flight planes[])
{
  int i;
  int j;

  for (i = 0; i < TOTAL_FLIGHTS; i++) {
    for (j = 0; j < TOTAL_FLIGHTS; j++) {
      if (Collide(&planes[i], &planes[j]))
        printf("Flights %s and %s are on collision course!\n",
               planes[i].flightNum, planes[j].flightNum);
    }
  }
}
