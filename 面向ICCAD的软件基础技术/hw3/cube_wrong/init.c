/* init.c -- init() to set the first values to the global variables.
 */
#include "all.h"

struct d3point viewpoint; /* the viewpoint*/
float distance;	/* the distance from viewpoint to plane */
struct d2point winlt;
struct d2point winrb;
struct d2point viewlt;
struct d2point viewrb;
struct listnode	*listhead;
int lineNum;
float alpha,beta;

void init()
{
	listhead=NULL;
	readline(); /* read in data */
	
	alpha=60.0;
	beta=45.0;
	viewpoint.z=5*sin(beta/180*Pi);
	viewpoint.y=5*cos(beta/180*Pi)*sin(alpha/180*Pi);
	viewpoint.x=5*cos(beta/180*Pi)*cos(alpha/180*Pi);
	
	distance=12;
	winlt.x=-5;
	winlt.y=5;
	winrb.x=5;
	winrb.y=-5;

	viewlt.x=0;
	viewlt.y=0;
	viewrb.x=500;
	viewrb.y=500;
	
	translate();
}
