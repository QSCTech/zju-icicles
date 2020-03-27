/* global.h -- contains the main global variables being used in my program.
 */

extern struct d3point viewpoint; /* the viewpoint of the observer.*/
extern float distance; /* the distance from the viewpoint to the cast plane.*/
extern struct d2point winlt; /* the left top of the 2 dimension window */
extern struct d2point winrb; /* the right buttom of the 2 dimension window */
extern struct d2point viewlt; /* the left top of the viewport */
extern struct d2point viewrb; /* the right buttom of the viewport */

extern char *fileName; /* the file contains the line data.*/
extern struct listnode *listhead; /* the head of the list.*/
extern int lineNum; /* how many lines should be drawn */
extern float alpha,beta; /* for rotating */
