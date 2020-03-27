
/*main.c the main function of the program. It opens display, and draws a cube.*/

#include "all.h"

void main()
{
	Display		     *display;
	int		         screen;
	Window		     win;
	XColor		     blue,green,red;
	unsigned int	 width=800;
	unsigned int	 height=600;
	XFontStruct      *font_info;
	GC		         gc;
	Colormap	     cmap;
	XEvent		     x_event;
	XGCValues	     values;
	XButtonEvent	 *but_event;

	if((display=XOpenDisplay(NULL))==NULL)
	{
		perror("Could not open X display");
		exit(-1);
	}
	screen=DefaultScreen(display);	
	win=XCreateSimpleWindow(display,RootWindow(display,screen),0,0,width,height,5, BlackPixel(display,screen), WhitePixel(display,screen));
	
	cmap=DefaultColormap(display,screen);
	
	XParseColor(display,cmap,"blue",&blue);
	XParseColor(display,cmap,"green",&green);
	XParseColor(display,cmap,"red",&red);
	
	XAllocColor(display,cmap,&blue);
	XAllocColor(display,cmap,&green);
	XAllocColor(display,cmap,&red);
	
	
	if ((font_info = XLoadQueryFont(display,"9x15"))==NULL)
	{
		perror("Use fixed font\n");
		font_info=XLoadQueryFont(display,"fixed");
	}
	gc=XCreateGC(display,win,(unsigned long)0,&values);
	XSetFunction(display,gc,9);
	XSetFont(display,gc,font_info->fid);
	XSetStandardProperties(display,win,"The cube display",NULL,None,NULL,0,NULL);
	XSelectInput(display,win,ExposureMask|ButtonPressMask|KeyPressMask|KeyReleaseMask);
	XMapWindow(display,win);

	init(); // initialize global variables and translate all coordinates

/*	
	 the 6 lines below draw a cube and stop, maybe used for debugging	
	XNextEvent(display,&x_event); // dispose an event
	XSetForeground(display,gc,blue.pixel);
	draw_line(win,gc,display,screen,blue);
	draw_guide(win,gc,display,screen,red,green,1);
	XFlush(display);
	getchar();
*/

	while(1)
	{
		XNextEvent(display,&x_event);
		switch(x_event.type){
			case Expose:
                draw_line(win,gc,display,screen,blue);				
				draw_guide(win,gc,display,screen,red,green,1);
			break;
			case KeyPress:// +, -, h, j, k, l 
				switch(x_event.xkey.keycode){
				case 21: //+
					draw_guide(win,gc,display,screen,red,green,0);
					XSetForeground(display,gc,blue.pixel);
					draw_line(win,gc,display,screen,blue);					
					distance+=1.0;
					if (distance>13)
						distance=13;

					viewpoint.z=5*sin(beta/180*Pi);
					viewpoint.y=5*cos(beta/180*Pi)*sin(alpha/180*Pi);
					viewpoint.x=5*cos(beta/180*Pi)*cos(alpha/180*Pi);

					translate();
					XSetForeground(display,gc,blue.pixel);
					draw_line(win,gc,display,screen,blue);					
					draw_guide(win,gc,display,screen,red,green,1);
				break;
				case 20: //-
					distance-=1.0;
					draw_guide(win,gc,display,screen,red,green,0);
					XSetForeground(display,gc,blue.pixel);

					draw_line(win,gc,display,screen,blue);										
					if (distance<7)
						distance=7;

					viewpoint.z=5*sin(beta/180*Pi);
					viewpoint.y=5*cos(beta/180*Pi)*sin(alpha/180*Pi);
					viewpoint.x=5*cos(beta/180*Pi)*cos(alpha/180*Pi);

					translate();

                    XSetForeground(display,gc,blue.pixel);
					draw_line(win,gc,display,screen,blue);					
					draw_guide(win,gc,display,screen,red,green,1);
				break;
				case 43: // for H, J, K, L
					draw_guide(win,gc,display,screen,red,green,0);
					XSetForeground(display,gc,blue.pixel);

					draw_line(win,gc,display,screen,blue);					
					XSetForeground(display,gc,blue.pixel);
					beta+=5.0;
					if(beta>90)
						beta=90;
					viewpoint.z=5*sin(beta/180*Pi);
					viewpoint.y=5*cos(beta/180*Pi)*sin(alpha/180*Pi);
					viewpoint.x=5*cos(beta/180*Pi)*cos(alpha/180*Pi);

					translate();
					XSetForeground(display,gc,blue.pixel);
				    draw_line(win,gc,display,screen,blue);
					draw_guide(win,gc,display,screen,red,green,1);
				break;
				case 44:
					draw_guide(win,gc,display,screen,red,green,0);
					XSetForeground(display,gc,blue.pixel);

				    draw_line(win,gc,display,screen,blue);
					beta-=5.0;
					if(beta<-90)
						beta=-90;
					viewpoint.z=5*sin(beta/180*Pi);
					viewpoint.y=5*cos(beta/180*Pi)*sin(alpha/180*Pi);
					viewpoint.x=5*cos(beta/180*Pi)*cos(alpha/180*Pi);

					translate();
					XSetForeground(display,gc,blue.pixel);					
					draw_line(win,gc,display,screen,blue);
					draw_guide(win,gc,display,screen,red,green,1);
				break;
				case 45:
					draw_guide(win,gc,display,screen,red,green,0);
					XSetForeground(display,gc,blue.pixel);					
					draw_line(win,gc,display,screen,blue);
					alpha-=10;
					if(alpha<-360)
						alpha=0;
					viewpoint.z=5*sin(beta/180*Pi);
					viewpoint.y=5*cos(beta/180*Pi)*sin(alpha/180*Pi);
					viewpoint.x=5*cos(beta/180*Pi)*cos(alpha/180*Pi);
					translate();
					XSetForeground(display,gc,blue.pixel);					
					draw_line(win,gc,display,screen,blue);
					draw_guide(win,gc,display,screen,red,green,1);
				break;
				case 46:
					draw_guide(win,gc,display,screen,red,green,0);
					XSetForeground(display,gc,blue.pixel);					
					draw_line(win,gc,display,screen,blue);
					alpha+=10;
					if(alpha>360)
						alpha=0;
					viewpoint.z=5*sin(beta/180*Pi);
					viewpoint.y=5*cos(beta/180*Pi)*sin(alpha/180*Pi);
					viewpoint.x=5*cos(beta/180*Pi)*cos(alpha/180*Pi);

					translate();
					XSetForeground(display,gc,blue.pixel);					
					draw_line(win,gc,display,screen,blue);
					draw_guide(win,gc,display,screen,red,green,1);
				break;
				default:
				break;
				}
			break;
			case ButtonPressMask:
				but_event = (XButtonEvent *) &x_event;
				if (but_event->window == win && but_event->button == Button3)
				{
					XCloseDisplay(display);
					exit(0);
				}
			break;
			default:
			break;
		}
	}
}
