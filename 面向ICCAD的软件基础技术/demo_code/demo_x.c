#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ctype.h>
#include <X11/Xos.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>

/* X stuff */
Display       *theDisp;
int           theScreen;
Window        rootW, mainW;

static void HandleEvent(XEvent *);

int main(argc, argv)
     int   argc;
     char *argv[];
{
  XEvent event;
  XSetWindowAttributes xswa;
  unsigned long xswamask;
  XSizeHints hints;

  if ( (theDisp=XOpenDisplay(NULL)) == NULL) {
    fprintf(stderr, "%s", "can't open display\n");
    exit(0);
  }
  theScreen = DefaultScreen(theDisp);
  rootW     = RootWindow(theDisp,theScreen);

  hints.width  = 100; hints.height = 100;
  hints.max_width  = 600; hints.max_height = 600;
  hints.min_width  = 16; hints.min_height = 16;
  hints.width_inc = hints.height_inc = 16;
  hints.flags |= PMaxSize | PMinSize | PResizeInc;
  xswa.cursor = XCreateFontCursor (theDisp, XC_umbrella);
  xswamask = CWCursor;

  mainW = XCreateWindow(theDisp,rootW,0,0,(unsigned int) 100,
    (unsigned int) 100, 2, 0,
    (unsigned int) CopyFromParent,
    CopyFromParent, xswamask, &xswa);

  XSetStandardProperties(theDisp,mainW, "x_try", "x_try",
    None,argv,argc,&hints);

  XSelectInput(theDisp, mainW, ExposureMask
           | StructureNotifyMask | ButtonPressMask);
  XMapWindow(theDisp,mainW);
  /**************** Main loop *****************/
  while (1) {
    XNextEvent(theDisp, &event);
    HandleEvent(&event);
  }
}

static void HandleEvent(event)
     XEvent *event;
{
  switch (event->type) {
  case Expose: {
    XExposeEvent *exp_event = (XExposeEvent *) event;
//    if (exp_event->window==mainW) {should redraw the window}
  }
    break;
  case ButtonPress: {
    XButtonEvent *but_event = (XButtonEvent *) event;
    if (but_event->window == mainW && but_event->button == Button1)
      printf("mouse on %d, %d\n", but_event->x, but_event->y);
  }
    break;
  case ConfigureNotify: {
    XConfigureEvent *conf_event = (XConfigureEvent *) event;
//    if (exp_event->window==mainW) {should redraw the window}
  }
    break;
  case CirculateNotify:
  case MapNotify:
  case DestroyNotify:
  case GravityNotify:
  case ReparentNotify:
  case UnmapNotify:
  case MappingNotify:
  case ClientMessage:         break;
  default:      /* ignore unexpected events */
    break;
  }  /* end of switch */
}
