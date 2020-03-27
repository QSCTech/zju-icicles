#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <X11/Xlib.h>
//--------------------------------------
#include <X11/Xutil.h>
//--------------------------------------
#include "draw.h"
#include "global.h"

#define	Pi	3.14159

struct	d2point plane_cast(struct d3point user3d);
struct	d2point	toview(struct d2point);

int	    trip(struct line);

void	encode(float,float,int*);
void 	translate();
void	init();
void	draw_line(Window,GC,Display *,int,XColor blue);

void 	readline();
void 	draw_guide(Window,GC,Display *,int,XColor,XColor,int);
