/* draw.h -- to define the types used in my program.
 */

/* d3point -- the cube is composed of the 3d vertex points and the lines 
 *            that join the points together.
 *            The points are in the user's coordination usually. 
 */

struct d3point{
	float x;
	float y;
	float z;
};	

/* d2point -- the 2d graphics are composed of 2 dimension points and the lines 
 *			that links them.
 */
struct d2point{
	float x;
	float y;
};

/* line -- the line that join tht two points.*/
struct line{
	struct d2point p1;
	struct d2point p2;
};

/* d3line -- the line that join two d3points.*/
struct d3line{
	struct d3point p1;
	struct d3point p2;
};

/*  listnode -- the linklist that contain the line that composes the graphics */
struct listnode{
	struct d3line line1;	/* to store the original line */	
	struct line line2;	/* to store the line after translating.*/
	int	off;		/* is it out of the window?*/
	struct listnode *next;  /* next node in the list */
};
