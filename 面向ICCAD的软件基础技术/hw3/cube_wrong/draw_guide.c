/* draw_guide() to draw the direction guide
 */

#include "all.h"

void draw_guide(Window win,GC gc,Display *display,
		int screen,XColor red,XColor green,int flag)
{
	static struct listnode node1,node2,node3;
	float 	x1,y1,x2,y2;
	float 	xx,yy,zz,u;

	/* node1/2/3 is the line from (0,0,0) to tip point of x/y/z axis */
	node1.line1.p1.x=0;
	node1.line1.p1.y=0;
	node1.line1.p1.z=0;	
	node1.line1.p2.x=1.7;
	node1.line1.p2.y=0;
	node1.line1.p2.z=0;

	node2.line1.p1.x=0;
	node2.line1.p1.y=0;
	node2.line1.p1.z=0;
	node2.line1.p2.x=0;
	node2.line1.p2.y=1.5;
	node2.line1.p2.z=0;
	
	node3.line1.p1.x=0;
	node3.line1.p1.y=0;
	node3.line1.p1.z=0;
	node3.line1.p2.x=0;
	node3.line1.p2.y=0;
	node3.line1.p2.z=1.5;

	if (flag){	
	/* if flag==0, we use last time's user coordination, which means to erase old guide lines. */
	/* last time's coordinates are kept in static node1/node2/node3. */
	/* if flag==1, we renew the user coordination of guide lines, and really draw them. */
		node1.line2.p1=plane_cast(node1.line1.p1);
		node1.line2.p2=plane_cast(node1.line1.p2);
	
		node2.line2.p1=plane_cast(node2.line1.p1);
		node2.line2.p2=plane_cast(node2.line1.p2);
		
		node3.line2.p1=plane_cast(node3.line1.p1);
		node3.line2.p2=plane_cast(node3.line1.p2);
	
		node1.line2.p1=toview(node1.line2.p1);
		node1.line2.p2=toview(node1.line2.p2);
		
		node2.line2.p1=toview(node2.line2.p1);
		node2.line2.p2=toview(node2.line2.p2);
		
		node3.line2.p1=toview(node3.line2.p1);
		node3.line2.p2=toview(node3.line2.p2);
	}

	x1=node1.line2.p1.x;
	y1=node1.line2.p1.y;
	x2=node1.line2.p2.x;
	y2=node1.line2.p2.y;
	XSetForeground(display,gc,red.pixel);
	XDrawLine(display,win,gc,(int)x1,(int)y1,(int)x2,(int)y2);
	XSetForeground(display,gc,green.pixel);	
	XDrawString(display,win,gc,(int)x1,(int)y1,"0",1);
	XDrawString(display,win,gc,(int)x2,(int)y2,"x",1);
	
	x1=node2.line2.p1.x;
	y1=node2.line2.p1.y;
	x2=node2.line2.p2.x;
	y2=node2.line2.p2.y;
	XSetForeground(display,gc,red.pixel);
	XDrawLine(display,win,gc,(int)x1,(int)y1,(int)x2,(int)y2);
	XSetForeground(display,gc,green.pixel);
	XDrawString(display,win,gc,(int)x2,(int)y2,"y",1);

	x1=node3.line2.p1.x;
	y1=node3.line2.p1.y;
	x2=node3.line2.p2.x;
	y2=node3.line2.p2.y;
	XSetForeground(display,gc,red.pixel);
	XDrawLine(display,win,gc,(int)x1,(int)y1,(int)x2,(int)y2);
	XSetForeground(display,gc,green.pixel);
	XDrawString(display,win,gc,(int)x2,(int)y2,"z",1);
}
