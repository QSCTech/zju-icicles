/*
 * File: graphics.c
 * Version: 3.1
 * Last modified on Thu Feb 23 13:39:32 1995 by eroberts
 * -----------------------------------------------------
 * This file implements the graphics.h and extgraph.h interfaces
 * for the Borland/Windows platform.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <wincon.h>
#include <Windows.h>

#include "../include/genlib.h"
#include "../include/gcalloc.h"
#include "../include/strlib.h"
#include "../include/extgraph.h"

/*
 * Parameters
 * ----------
 * DesiredWidth    -- Desired width of the graphics window
 * DesiredHeight   -- Desired height of the graphics window
 * DefaultSize     -- Default point size
 * MaxTitle        -- Maximum window title length
 * MaxFontName     -- Maximum font name length
 * MaxFonts        -- Maximum number of fonts
 * LeftMargin      -- Margin from left of screen to both windows
 * RightMargin     -- Minimum margin to right of windows
 * TopMargin       -- Margin from top of screen to graphics window
 * BottomMargin    -- Minimum margin from bottom of screen to console window
 * WindowSep       -- Separation between graphics and console windows
 * ConsoleHeight   -- Height of the console window (pixels)
 * MinConsoleScale -- Smallest acceptable scale factor for the console
 * PStartSize      -- Starting size for polygon (must be greater than 1)
 * MaxColors       -- Maximum number of color names allowed
 * MinColors       -- Minimum number of colors the device must support
 * GWClassName     -- Class name of the graphics window
 * DefaultFont     -- Font that serves as the "Default" font
 */

#define DesiredWidth       10.0
#define DesiredHeight      7.0
#define DefaultSize       12
#define MaxTitle          75
#define MaxFontName       50
#define MaxFonts         100
#define LeftMargin        0/*10*/
#define RightMargin       25
#define TopMargin          0
#define BottomMargin      30
#define WindowSep          5
#define ConsoleHeight    110
#define MinConsoleScale    0.8
#define PStartSize        50
#define MaxColors        256
#define MinColors         16

#define GWClassName "Graphics Window"
#define DefaultFont "System"

/*
 * Other constants
 * ---------------
 * LargeInt  -- Integer too large for a coordinate value
 * Epsilon   -- Small arithmetic offset to reduce aliasing/banding
 * Pi        -- Mathematical constant pi
 * AnyButton -- Union of all mouse buttons
 */

#define LargeInt 16000
#define Epsilon  0.00000000001
#define Pi       3.1415926535

#define AnyButton (MK_LBUTTON | MK_RBUTTON | MK_MBUTTON)

KeyboardEventCallback g_keyboard = NULL;
MouseEventCallback g_mouse = NULL;
TimerEventCallback g_timer = NULL;
CharEventCallback g_char = NULL;

/*
 * Type: graphicsStateT
 * --------------------
 * This structure holds the variables that make up the graphics state.
 */

typedef struct graphicsStateT {
    double cx, cy;
    string font;
    int size;
    int style;
    bool erase;
    int color;
    struct graphicsStateT *link;
} *graphicsStateT;

/*
 * Type: fontEntryT
 * ----------------
 * This structure holds the data for a font.
 */

typedef struct {
    string name;
    int size, style;
    int points, ascent, descent, height;
    HFONT font;
} fontEntryT;

/*
 * Type: regionStateT
 * ------------------
 * The region assembly process has the character of a finite state
 * machine with the following four states:
 *
 *   NoRegion       Region has not yet been started
 *   RegionStarting Region is started but no line segments yet
 *   RegionActive   First line segment appears
 *   PenHasMoved    Pen has moved during definition
 *
 * The current state determines whether other operations are legal
 * at that point.
 */

typedef enum {
    NoRegion, RegionStarting, RegionActive, PenHasMoved
} regionStateT;

/*
 * Type: colorEntryT
 * -----------------
 * This type is used for the entries in the color table.
 */

typedef struct {
    string name;
    double red, green, blue;
} colorEntryT;

/*
 * Static table: fillList
 * ----------------------
 * This table contains the bitmap patterns for the various density
 * values.  Adding more patterns to this list increases the
 * precision with which the client can control fill patterns.
 * Note that this bitmap is inverted from that used on most
 * systems, with 0 indicating foreground and 1 indicating background.
 */

static short fillList[][8] = {
    { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
    { 0x77, 0xDD, 0x77, 0xDD, 0x77, 0xDD, 0x77, 0xDD },
    { 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA },
    { 0x88, 0x22, 0x88, 0x22, 0x88, 0x22, 0x88, 0x22 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
};

#define NFills (sizeof fillList / sizeof fillList[0])

/*
 * Global variables
 * ----------------
 * initialized    -- TRUE if initialization has been done
 * pauseOnExit    -- TRUE if library should pause when exiting
 * consoleWindow  -- Window handle for console window
 * graphicsWindow -- Window handoe for graphics window
 * gdc            -- Graphics DC (screen)
 * osdc           -- Offscreen DC (memory backup)
 * osbits         -- Offscreen bitmap
 * drawPen        -- Pen used for drawing
 * erasePen       -- Pen used for erasing
 * nullPen        -- Pen used for filling
 * drawColor      -- Color used for drawing
 * eraseColor     -- Color used for erasing
 * windowTitle    -- Current window title (initialized statically)
 * xResolution    -- Horizontal resolution of screen (dots per inch)
 * yResolution    -- Vertical resolution of screen (dots per inch)
 * windowWidth    -- Width of graphics window (inches)
 * windowHeight   -- Height of graphics window (inches)
 * pixelWidth     -- Width of graphics window (pixels)
 * pixelHeight    -- Height of graphics window (pixels)
 * fontTable      -- Table of stored fonts
 * nFonts         -- Number of fonts in fontTable
 * currentFont    -- Index of current font in fontTable
 * regionState    -- Current state of the region
 * regionDensity  -- Fill density to apply to region
 * polygonPoints  -- Array of points used in current region
 * nPolygonPoints -- Number of active points
 * polygonSize    -- Number of allocated points
 * polygonBounds  -- Bounding box of polygon
 * colorTable     -- Table of defined colors
 * nColors        -- Number of defined colors
 * previousColor  -- Last color index set
 * stateStack     -- Stack of graphicStateT blocks
 * cx, cy         -- Current coordinates     | These
 * eraseMode      -- Setting of erase flag   | variables
 * textFont       -- Current font            | consititute
 * textStyle      -- Current style           | the current
 * pointSize      -- Current point size      | graphics
 * penColor       -- Color of pen            | state
 */

static int penSize = 1;

static bool initialized = FALSE;
static bool pauseOnExit = TRUE;

static HWND consoleWindow, graphicsWindow;
static HDC gdc, osdc;
static HBITMAP osBits;
static HPEN drawPen, erasePen, nullPen;
static COLORREF drawColor, eraseColor;
static PAINTSTRUCT ps;
static string windowTitle = "Graphics Window";

static double xResolution, yResolution;
static double windowWidth = DesiredWidth;
static double windowHeight = DesiredHeight;
static int pixelWidth, pixelHeight;

static fontEntryT fontTable[MaxFonts];
static int nFonts;
static int currentFont;

static regionStateT regionState;
static double regionDensity;
static POINT *polygonPoints;
static int nPolygonPoints;
static int polygonSize;
static RECT polygonBounds;
static HBITMAP fillBitmaps[NFills];

static colorEntryT colorTable[MaxColors];
static int nColors;
static int previousColor;

static graphicsStateT stateStack;

static double cx, cy;
static bool eraseMode;
static string textFont;
static int textStyle;
static int pointSize;
static int penColor;

static int mouseX, mouseY;
static bool mouseButton = FALSE;

/* Private function prototypes */

static void InitCheck(void);
static void InitGraphicsState(void);
static void InitDisplay(void);
static void InitDrawingTools(void);
static void DisplayExit(void);
static HWND FindConsoleWindow(void);
static BOOL CALLBACK EnumerateProc(HWND window, LPARAM clientData);
static void RegisterWindowClass(void);
static LONG FAR PASCAL GraphicsEventProc(HWND w, UINT msg,
                                         WPARAM p1, LPARAM p2);
static void CheckEvents(void);
static void DoUpdate(void);
static void DisplayClear(void);
static void PrepareToDraw(void);
static void DisplayLine(double x, double y, double dx, double dy);
static void DisplayArc(double xc, double yc, double rx, double ry,
                       double start, double sweep);
static void RenderArc(double x, double y, double rx, double ry,
                      double start, double sweep);
static void DisplayText(double x, double y, string text);
static void DisplayFont(string font, int size, int style);
static int FindExistingFont(string name, int size, int style);
static void SetLineBB(RECT *rp, double x, double y, double dx, double dy);
static void SetArcBB(RECT *rp, double xc, double yc,
                     double rx, double ry, double start, double sweep);
static void SetTextBB(RECT *rp, double x, double y, string text);
static void StartPolygon(void);
static void AddSegment(int x0, int y0, int x1, int y1);
static void DisplayPolygon(void);
static void AddPolygonPoint(int x, int y);
static void InitColors(void);
static int FindColorName(string name);

static bool StringMatch(string s1, string s2);
static bool PrefixMatch(string prefix, string str);
static int RectWidth(RECT *rp);
static int RectHeight(RECT *rp);
static void SetRectFromSize(RECT *rp, int x, int y, int width, int height);
static double Radians(double degrees);
static int Round(double x);
static double InchesX(int x);
static double InchesY(int y);
static int PixelsX(double x);
static int PixelsY(double y);
static int ScaleX(double x);
static int ScaleY(double y);
static int Min(int x, int y);
static int Max(int x, int y);

/* Exported entries */

/* Section 1 -- Basic functions from graphics.h */

void InitGraphics(void)
{
    if (!initialized) {
        initialized = TRUE;
        ProtectVariable(stateStack);
        ProtectVariable(windowTitle);
        ProtectVariable(textFont);
        InitColors();
        InitDisplay();
    }
    DisplayClear();
    InitGraphicsState();

}

void MovePen(double x, double y)
{
    InitCheck();
    if (regionState == RegionActive) regionState = PenHasMoved;
    cx = x;
    cy = y;
}

void DrawLine(double dx, double dy)
{
    InitCheck();
    switch (regionState) {
      case NoRegion:
        DisplayLine(cx, cy, dx, dy);
        break;
      case RegionStarting: case RegionActive:
        DisplayLine(cx, cy, dx, dy);
        regionState = RegionActive;
        break;
      case PenHasMoved:
        Error("Region segments must be contiguous");
    }
    cx += dx;
    cy += dy;
}

void DrawArc(double r, double start, double sweep)
{
    DrawEllipticalArc(r, r, start, sweep);
}

double GetWindowWidth(void)
{
    InitCheck();
    return (windowWidth);
}

double GetWindowHeight(void)
{
    InitCheck();
    return (windowHeight);
}

double GetCurrentX(void)
{
    InitCheck();
    return (cx);
}

double GetCurrentY(void)
{
    InitCheck();
    return (cy);
}

/* Section 2 -- Elliptical arcs */

void DrawEllipticalArc(double rx, double ry,
                       double start, double sweep)
{
    double x, y;

    InitCheck();
    x = cx + rx * cos(Radians(start + 180));
    y = cy + ry * sin(Radians(start + 180));
    switch (regionState) {
      case NoRegion:
        DisplayArc(x, y, rx, ry, start, sweep);
        break;
      case RegionStarting: case RegionActive:
        RenderArc(x, y, rx, ry, start, sweep);
        regionState = RegionActive;
        break;
      case PenHasMoved:
        Error("Region segments must be contiguous");
    }
    cx = x + rx * cos(Radians(start + sweep));
    cy = y + ry * sin(Radians(start + sweep));
}

/* Section 3 -- Graphical structures */

void StartFilledRegion(double grayScale)
{
    InitCheck();
    if (regionState != NoRegion) {
        Error("Region is already in progress");
    }
    if (grayScale < 0 || grayScale > 1) {
        Error("Gray scale for regions must be between 0 and 1");
    }
    regionState = RegionStarting;
    regionDensity = grayScale;
    StartPolygon();
}

void EndFilledRegion(void)
{
    InitCheck();
    if (regionState == NoRegion) {
        Error("EndFilledRegion without StartFilledRegion");
    }
    DisplayPolygon();
    regionState = NoRegion;
}

/* Section 4 -- String functions */

void DrawTextString(string text)
{
    InitCheck();
    if (regionState != NoRegion) {
        Error("Text strings are illegal inside a region");
    }
    DisplayText(cx, cy, text);
    cx += TextStringWidth(text);
}

double TextStringWidth(string text)
{
    RECT r;

    InitCheck();
    SetTextBB(&r, cx, cy, text);
    return (InchesX(RectWidth(&r)));
}

void SetFont(string font)
{
    InitCheck();
    DisplayFont(font, pointSize, textStyle);
}

string GetFont(void)
{
    InitCheck();
    return (CopyString(textFont));
}

void SetPointSize(int size)
{
    InitCheck();
    DisplayFont(textFont, size, textStyle);
}

int GetPointSize(void)
{
    InitCheck();
    return (pointSize);
}

void SetStyle(int style)
{
    InitCheck();
    DisplayFont(textFont, pointSize, style);
}

int GetStyle(void)
{
    InitCheck();
    return (textStyle);
}

double GetFontAscent(void)
{
    InitCheck();
    return (InchesY(fontTable[currentFont].ascent));
}

double GetFontDescent(void)
{
    InitCheck();
    return (InchesY(fontTable[currentFont].descent));
}

double GetFontHeight(void)
{
    InitCheck();
    return (InchesY(fontTable[currentFont].height));
}

/* Section 5 -- Mouse support */

double GetMouseX(void)
{
    InitCheck();
    CheckEvents();
    return (InchesX(mouseX));
}

double GetMouseY(void)
{
    InitCheck();
    CheckEvents();
    return (windowHeight - InchesY(mouseY));
}

bool MouseButtonIsDown(void)
{
    InitCheck();
    CheckEvents();
    return (mouseButton);
}

void WaitForMouseDown(void)
{
    MSG msg;

    UpdateDisplay();
    while (!mouseButton) {
        if (GetMessage(&msg, graphicsWindow, 0, 0) == 0) exit(0);
        DispatchMessage(&msg);
    }
}

void WaitForMouseUp(void)
{
    MSG msg;

    UpdateDisplay();
    while (mouseButton) {
        if (GetMessage(&msg, graphicsWindow, 0, 0) == 0) exit(0);
        DispatchMessage(&msg);
    }
}

/* Section 6 -- Color support */

bool HasColor(void)
{
    InitCheck();
    return (GetDeviceCaps(gdc, NUMCOLORS) >= MinColors);
}

void SetPenColor(string color)
{
    int cindex;

    InitCheck();
    cindex = FindColorName(color);
    if (cindex == -1) Error("Undefined color: %s", color);
    penColor = cindex;
}

string GetPenColor(void)
{
    InitCheck();
    return (CopyString(colorTable[penColor].name));
}

void DefineColor(string name,
                 double red, double green, double blue)
{
    int cindex;

    InitCheck();
    if (red < 0 || red > 1 || green < 0 || green > 1 || blue < 0 || blue > 1) {
        Error("DefineColor: All color intensities must be between 0 and 1");
    }
    cindex = FindColorName(name);
    if (cindex == -1) {
        if (nColors == MaxColors) Error("DefineColor: Too many colors");
        cindex = nColors++;
    }
    colorTable[cindex].name = CopyString(name);
    colorTable[cindex].red = red;
    colorTable[cindex].green = green;
    colorTable[cindex].blue = blue;
}

/* Section 7 -- Miscellaneous functions */

void SetPenSize(int size)
{
    penSize = size;
}

int GetPenSize(void)
{
 	return penSize;
}

void SetEraseMode(bool mode)
{
    InitCheck();
    eraseMode = mode;
}

bool GetEraseMode(void)
{
    InitCheck();
    return (eraseMode);
}

void SetWindowTitle(string title)
{
    windowTitle = CopyString(title);
    if (initialized) {
        SetWindowText(graphicsWindow, windowTitle);
    }
}

string GetWindowTitle(void)
{
    return (CopyString(windowTitle));
}

void UpdateDisplay(void)
{
    InitCheck();
    CheckEvents();
    DoUpdate();
}

void Pause(double seconds)
{
    double finish;

    UpdateDisplay();
    finish = (double) clock() / CLK_TCK + seconds;
    while (((double) clock() / CLK_TCK) < finish);
}

void ExitGraphics(void)
{
    pauseOnExit = FALSE;
    exit(0);
}

void SaveGraphicsState(void)
{
    graphicsStateT sb;

    InitCheck();
    sb = New(graphicsStateT);
    sb->cx = cx;
    sb->cy = cy;
    sb->font = textFont;
    sb->size = pointSize;
    sb->style = textStyle;
    sb->erase = eraseMode;
    sb->color = penColor;
    sb->link = stateStack;
    stateStack = sb;
}

void RestoreGraphicsState(void)
{
    graphicsStateT sb;

    InitCheck();
    if (stateStack == NULL) {
        Error("RestoreGraphicsState called before SaveGraphicsState");
    }
    sb = stateStack;
    cx = sb->cx;
    cy = sb->cy;
    textFont = sb->font;
    pointSize = sb->size;
    textStyle = sb->style;
    eraseMode = sb->erase;
    penColor = sb->color;
    DisplayFont(textFont, pointSize, textStyle);
    stateStack = sb->link;
    FreeBlock(sb);
}

double GetFullScreenWidth(void)
{
    HWND desktop;
    RECT bounds;

    desktop = GetDesktopWindow();
    GetWindowRect(desktop, &bounds);
    return ((double) RectWidth(&bounds) / GetXResolution());
}

double GetFullScreenHeight(void)
{
    HWND desktop;
    RECT bounds;

    desktop = GetDesktopWindow();
    GetWindowRect(desktop, &bounds);
    return ((double) RectHeight(&bounds) / GetYResolution());
}

void SetWindowSize(double width, double height)
{
    if (initialized) return;
    windowWidth = width;
    windowHeight = height;
}

double GetXResolution(void)
{
    HWND desktop;
    HDC dc;
    int xdpi;

    if (initialized) return (xResolution);
    desktop = GetDesktopWindow();
    dc = GetDC(desktop);
    xdpi = GetDeviceCaps(dc, LOGPIXELSX);
    ReleaseDC(desktop, dc);
    return (xdpi);
}

double GetYResolution(void)
{
    HWND desktop;
    HDC dc;
    int ydpi;

    if (initialized) return (yResolution);
    desktop = GetDesktopWindow();
    dc = GetDC(desktop);
    ydpi = GetDeviceCaps(dc, LOGPIXELSY);
    ReleaseDC(desktop, dc);
    return (ydpi);
}

/* Private functions */

/*
 * Function: InitCheck
 * Usage: InitCheck();
 * -------------------
 * This function merely ensures that the package has been
 * initialized before the client functions are called.
 */

static void InitCheck(void)
{
    if (!initialized) Error("InitGraphics has not been called");
}

/*
 * Function: InitGraphicsState
 * Usage: InitGraphicsState();
 * ---------------------------
 * This function initializes the graphics state elements to
 * their default values.  Because the erase mode and font
 * information are also maintained in the display state,
 * InitGraphicsState must call functions to ensure that these
 * values are initialized there as well.
 */

static void InitGraphicsState(void)
{
    cx = cy = 0;
    eraseMode = FALSE;
    textFont = "Default";
    pointSize = DefaultSize;
    textStyle = Normal;
    stateStack = NULL;
    regionState = NoRegion;
    DisplayFont(textFont, pointSize, textStyle);
}

void InitConsole(void)
{
    AllocConsole();
    freopen("CONIN$", "r+t", stdin);
    freopen("CONOUT$", "w+t", stdout);
}

void repaint()
{
    InvalidateRect(graphicsWindow, NULL, 1);
    UpdateWindow(graphicsWindow);
}


/*
 * Function: InitDisplay
 * Usage: InitDisplay();
 * ---------------------
 * This function does everything necessary to initialize the display.
 * In this implementation, the graphics window is created as an
 * overlapping child of the console window, which has been created
 * by EasyWin.  As a child of the console, the window automatically
 * gets events whenever the console window is waiting for events,
 * simplifying the logic of the implementation considerably.  Most
 * of the InitDisplay implementation is concerned with calculating
 * the new tiling geometry, after which the function creates the
 * new window and an offscreen bitmap to use as a target for any
 * rendering.  When the window gets a Paint event in the event
 * procedure GraphicsEventProc, all it has to do is copy the
 * bits from the offscreen bitmap onto the screen.
 */

static void InitDisplay(void)
{
    RECT bounds, consoleRect, graphicsRect;
    double screenHeight, screenWidth, xSpace, ySpace;
    double xScale, yScale, scaleFactor;
    DWORD style;
    int top, dx, dy, cWidth;

    /*clrscr();*/
    system("cls");
    atexit(DisplayExit);
/*    RegisterWindowClass();*/
    consoleWindow = FindConsoleWindow();
    initialized = FALSE;
    xResolution = GetXResolution();
    yResolution = GetYResolution();
    initialized = TRUE;
    screenWidth = GetFullScreenWidth();
    screenHeight = GetFullScreenHeight();
    xSpace = screenWidth - InchesX(LeftMargin + RightMargin);
    ySpace = screenHeight - InchesX(TopMargin + BottomMargin) - InchesX(ConsoleHeight + WindowSep);
    xScale = yScale = 1.0;
    if (windowWidth > xSpace) xScale = xSpace / windowWidth;
    if (windowHeight > ySpace) yScale = ySpace / windowHeight;
    scaleFactor = (xScale < yScale) ? xScale : yScale;
    if (scaleFactor > MinConsoleScale) {
        cWidth = PixelsX(DesiredWidth * scaleFactor);
    } else {
        cWidth = PixelsX(DesiredWidth * MinConsoleScale);
    }
    xResolution *= scaleFactor;
    yResolution *= scaleFactor;
    SetRectFromSize(&graphicsRect, LeftMargin, TopMargin,
                    PixelsX(windowWidth), PixelsY(windowHeight));
    style = WS_OVERLAPPEDWINDOW & ~(WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
    
    g_keyboard = NULL;
	g_mouse = NULL;
	g_timer = NULL;
    
    WNDCLASS wndcls;
    wndcls.cbClsExtra = 0;
    wndcls.cbWndExtra = 0;
    wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndcls.hInstance = NULL;
    wndcls.lpfnWndProc = GraphicsEventProc;
    wndcls.lpszClassName = "Graphics Window";
    wndcls.lpszMenuName = NULL;
    wndcls.style = CS_HREDRAW | CS_VREDRAW;
    
    RegisterClass(&wndcls);
    
    graphicsWindow = CreateWindow(
      GWClassName,
      windowTitle, 
      style,
      graphicsRect.left, 
      graphicsRect.top,
      RectWidth(&graphicsRect), 
      RectHeight(&graphicsRect),
      /*consoleWindow*/ NULL, 
      (HMENU) NULL, 
      (HINSTANCE) NULL,
      (LPSTR) NULL);
      
    if (graphicsWindow == NULL) {
        printf("InitGraphics: CreateGraphicsWindow failed.\n");
    }
    GetClientRect(graphicsWindow, &bounds);
    dx = RectWidth(&graphicsRect) - RectWidth(&bounds);
    dy = RectHeight(&graphicsRect) - RectHeight(&bounds);
    SetWindowPos(graphicsWindow, HWND_TOP,
                 graphicsRect.left, graphicsRect.top,
                 RectWidth(&graphicsRect) + dx,
                 RectHeight(&graphicsRect) + dy, 0);
    gdc = GetDC(graphicsWindow);
    GetClientRect(graphicsWindow, &bounds);
    pixelWidth = RectWidth(&bounds);
    pixelHeight = RectHeight(&bounds);
    
    ShowWindow(graphicsWindow, SW_SHOWNORMAL);
    
    UpdateWindow(graphicsWindow);
    
    osdc = CreateCompatibleDC(gdc);
    
    if (osdc == NULL) {
        Error("Internal error: Can't create offscreen device");
    }
    osBits = CreateCompatibleBitmap(gdc, pixelWidth, pixelHeight);
    if (osBits == NULL) {
        Error("Internal error: Can't create offscreen bitmap");
    }
    (void) SelectObject(osdc, osBits);
    
    top = TopMargin + WindowSep + PixelsY(windowHeight) + dy;
    /*
    SetRectFromSize(&consoleRect, LeftMargin, top,
                    cWidth + dx, ConsoleHeight);
    SetWindowText(consoleWindow, "Console Window");
    SetWindowPos(consoleWindow, HWND_TOP,
                 consoleRect.left, consoleRect.top,
                 RectWidth(&consoleRect), RectHeight(&consoleRect), 0);
    */

    InitDrawingTools();
}



/*
 * Function: InitDrawingTools
 * Usage: InitDrawingTools();
 * --------------------------
 * This function initializes all of the standard objects used for
 * drawing except for fonts, which are initialized dynamically by
 * the DisplayFont procedure.  This function creates the
 * foreground/background colors, the drawing pens, and the brushes
 * for filled regions.
 */

static void InitDrawingTools(void)
{
    int i;

    nFonts = 0;
    previousColor = 0;
    drawColor = RGB(0, 0, 0);
    eraseColor = RGB(255, 255, 255);
    drawPen = (HPEN) CreatePen(PS_SOLID, penSize, drawColor);
    erasePen = (HPEN) CreatePen(PS_SOLID, penSize, eraseColor);
    nullPen = (HPEN) GetStockObject(NULL_PEN);
    if (drawPen == NULL || erasePen == NULL || nullPen == NULL) {
        Error("Internal error: Can't initialize pens");
    }
    for (i = 0; i < NFills; i++) {
        fillBitmaps[i] = CreateBitmap(8, 8, 1, 1, fillList[i]);
    }
    SelectObject(osdc, drawPen);
}

/*
 * Function: DisplayExit
 * Usage: DisplayExit();
 * ---------------------
 * This function is called when the program exits and waits for the
 * user to type a carriage return.  After reading and ignoring the
 * return key, this function frees the window system handles and
 * destroys the console window, thereby exiting the program.
 */

static void DisplayExit(void)
{
    int i;

    if (pauseOnExit) (void) getchar();
    DeleteDC(osdc);
    DeleteDC(gdc);
    DestroyWindow(consoleWindow);
    DestroyWindow(graphicsWindow);
    DeleteObject(drawPen);
    DeleteObject(erasePen);
    DeleteObject(nullPen);
    for (i = 0; i < nFonts; i++) {
        DeleteObject(fontTable[i].font);
    }
    for (i = 0; i < NFills; i++) {
        DeleteObject(fillBitmaps[i]);
    }
}

/*
 * Function: FindConsoleWindow
 * Usage: window = FindConsoleWindow();
 * ------------------------------------
 * The EasyWin package makes almost everything about the graphics
 * package easy in the Borland world.  The only thing that is hard
 * is getting the handle of the window used for the console in the
 * first place.  This function finds the console window handle by
 * enumerating the windows and looking for the first one whose
 * title ends with .EXE, which the EasyWin package puts there.
 */

static HWND FindConsoleWindow(void)
{
    HWND result;

    EnumWindows(EnumerateProc, (LPARAM) &result);
    return (result);
}

/*
 * Function: EnumerateProc
 * Usage: Not called directly
 * --------------------------
 * This callback procedure is used by the FindConsoleWindow
 * call to find the window whose title ends with .EXE.
 */

static BOOL CALLBACK EnumerateProc(HWND window, LPARAM clientData)
{
    HWND *wptr;
    char title[MaxTitle];
    bool ok;

    wptr = (HWND *) clientData;
    ok = GetWindowText(window, title, MaxTitle-1);
    if (ok && strcmp(title + strlen(title) - 4, ".EXE")==0) {
        *wptr = window;
        return (0);
    }
    return (1);
}

/*
 * Function: RegisterWindowClass
 * Usage: RegisterWindowClass();
 * -----------------------------
 * This function registers the window class used for the graphics
 * window.
 */

static void RegisterWindowClass(void)
{
    WNDCLASS wcApp;

    wcApp.lpszClassName = GWClassName;
    wcApp.hInstance = NULL;
    wcApp.lpfnWndProc = GraphicsEventProc;
    wcApp.hCursor = NULL;
    wcApp.hIcon = NULL;
    wcApp.lpszMenuName = NULL;
    wcApp.hbrBackground = GetStockObject(WHITE_BRUSH);
    wcApp.style = CS_HREDRAW | CS_VREDRAW;
    wcApp.cbClsExtra = wcApp.cbWndExtra = 0;
    if (!RegisterClass(&wcApp)) {
        Error("Internal error: RegisterClass failed\n");
    }
}

/*
 * Function: GraphicsEventProc
 * Usage: Not called directly
 * --------------------------
 * This function is called when an event is received for the
 * graphics window.  The only event this package needs to handle
 * is the paint event, which forces a screen update.
 */

static LONG FAR PASCAL GraphicsEventProc(HWND hwnd, UINT msg,
                                         WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_PAINT:
             DoUpdate();
             return 0;
             
        case WM_CHAR:
    		if (g_char != NULL)
    			g_char((char) wParam);
    		return 0;

    	case WM_KEYDOWN:
    		if (g_keyboard != NULL)
    			g_keyboard((int) wParam,KEY_DOWN);
    		return 0;
    
    	case WM_KEYUP:
    		if(g_keyboard != NULL)
    			g_keyboard((int) wParam,KEY_UP);
    		return 0;
    
    	case WM_LBUTTONDOWN:
    		if (g_mouse != NULL)
    			g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), LEFT_BUTTON, BUTTON_DOWN);
    		return 0;
    
    	case WM_LBUTTONUP:
    		if (g_mouse != NULL)
    			g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), LEFT_BUTTON, BUTTON_UP);
    		return 0;
    
    	case WM_LBUTTONDBLCLK:
    		if (g_mouse != NULL)
    			g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), LEFT_BUTTON, BUTTON_DOUBLECLICK);
    		return 0;
    
    	case WM_MBUTTONDOWN:
    		if (g_mouse != NULL)
    			g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), MIDDLE_BUTTON, BUTTON_DOWN);
    		return 0;
    
    	case WM_MBUTTONUP:
    		if (g_mouse != NULL)
    			g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), MIDDLE_BUTTON, BUTTON_UP);
    		return 0;
    
    	case WM_MBUTTONDBLCLK:
    		if (g_mouse != NULL)
    			g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), MIDDLE_BUTTON, BUTTON_DOUBLECLICK);
    		return 0;
    
    	case WM_RBUTTONDOWN:
    		if (g_mouse != NULL)
    			g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), RIGHT_BUTTON, BUTTON_DOWN);
    		return 0;
    
    	case WM_RBUTTONUP:
    		if (g_mouse != NULL)
    			g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), RIGHT_BUTTON, BUTTON_UP);
    		return 0;
    
    	case WM_RBUTTONDBLCLK:
    		if (g_mouse != NULL)
    			g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), RIGHT_BUTTON, BUTTON_DOUBLECLICK);
    		return 0;
    
    	case WM_MOUSEMOVE:
    		if(g_mouse != NULL)
    			g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), MOUSEMOVE, MOUSEMOVE);
    		return 0;
    
    	case WM_MOUSEWHEEL:
    		if(g_mouse == NULL)
    			return 0;
    		if(HIWORD(wParam) == 120)
    			g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam),MIDDLE_BUTTON,ROLL_UP);
    		else if(HIWORD(wParam)==65416)
    			g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam),MIDDLE_BUTTON,ROLL_DOWN);
    		return 0;
    
    	case WM_TIMER:
    		if (g_timer != NULL)
    			g_timer(wParam);
    		return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;   
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }                                     

/*
    if (msg == WM_PAINT) {
        DoUpdate();
        return (0L);
    }
    
    if (msg >= WM_MOUSEFIRST && msg <= WM_MOUSELAST) {
        mouseX = LOWORD(lParam);
        mouseY = HIWORD(lParam);
        mouseButton = (wParam & AnyButton) != 0;  
        return (0L);
    }
    
    
    if(msg == WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0;   
    }
    return (DefWindowProc(hwnd, msg, wParam, lParam));
    */
}

/*
 * Function: CheckEvents
 * Usage: CheckEvents();
 * ---------------------
 * This function is called from inside the mouse query functions to
 * ensure that pending events are processed.
 */

static void CheckEvents(void)
{
    MSG msg;

    while (PeekMessage(&msg, graphicsWindow, 0, 0, PM_REMOVE) != 0) {
        DispatchMessage(&msg);
    }
}

/*
 * Function: DoUpdate
 * Usage: DoUpdate();
 * ------------------
 * This function redraws the graphics window by copying bits from
 * the offscreen bitmap behind the osdc device context into the
 * actual display context.
 */

static void DoUpdate(void)
{
    HDC dc;

    dc = BeginPaint(graphicsWindow, &ps);
    BitBlt(dc, 0, 0, pixelWidth, pixelHeight, osdc, 0, 0, SRCCOPY);
    EndPaint(graphicsWindow, &ps);
}

/*
 * Function: DisplayClear
 * Usage: DisplayClear();
 * ----------------------
 * This function clears all the bits in the offscreen bitmap.
 */

static void DisplayClear(void)
{
    RECT r;

    SetRect(&r, 0, 0, pixelWidth, pixelHeight);
    InvalidateRect(graphicsWindow, &r, TRUE);
    BitBlt(osdc, 0, 0, pixelWidth, pixelHeight, osdc, 0, 0, WHITENESS);
}

/*
 * Function: PrepareToDraw
 * Usage: PrepareToDraw();
 * -----------------------
 * This function must be called before any rendering operation
 * to ensure the pen modes and colors are correctly set.
 */

static void PrepareToDraw(void)
{
    int red, green, blue;
/*
    HPEN oldPen;
*/

    if (eraseMode) {
        DeleteObject(erasePen);
        erasePen = (HPEN) CreatePen(PS_SOLID, penSize, eraseColor);
        (void) SelectObject(osdc, erasePen);
        SetTextColor(osdc, eraseColor);
    } else {
        if (penColor != previousColor) {
            red = colorTable[penColor].red * 256 - Epsilon;
            green = colorTable[penColor].green * 256 - Epsilon;
            blue = colorTable[penColor].blue * 256 - Epsilon;
            drawColor = RGB(red, green, blue);
            previousColor = penColor;
        }
        DeleteObject(drawPen);
		drawPen = (HPEN) CreatePen(PS_SOLID, penSize, drawColor);
        (void) SelectObject(osdc, drawPen);
        (void) SetTextColor(osdc, drawColor);
    }
}

/*
 * Function: DisplayLine
 * Usage: DisplayLine(x, y, dx, dy);
 * ---------------------------------
 * This function renders a line into the offscreen bitmap.  If the
 * region is started, it adds the line to the developing polygonal
 * region instead.
 */

static void DisplayLine(double x, double y, double dx, double dy)
{
    int x0, y0, x1, y1;
    RECT r;

    PrepareToDraw();
    x0 = ScaleX(x);
    y0 = ScaleY(y);
    x1 = ScaleX(x + dx);
    y1 = ScaleY(y + dy);
    if (regionState == NoRegion) {
        SetLineBB(&r, x, y, dx, dy);
        InvalidateRect(graphicsWindow, &r, TRUE);
        MoveToEx(osdc, x0, y0, NULL);
        LineTo(osdc, x1, y1);
    } else {
        AddSegment(x0, y0, x1, y1);
    }
}

/*
 * Function: DisplayArc
 * Usage: DisplayArc(xc, yc, rx, ry, start, sweep);
 * ------------------------------------------------
 * This function is used to draw an arc.  The arguments are slightly
 * different from those in the client interface because xc and yc
 * designate the center.  This function is only called if a region
 * is not being assembled; if it is, the package calls RenderArc
 * instead.
 */

static void DisplayArc(double xc, double yc, double rx, double ry,
                       double start, double sweep)
{
    RECT r;
    int xmax, xmin, ymax, ymin;
    int ix0, iy0, ix1, iy1;

    PrepareToDraw();
    SetArcBB(&r, xc, yc, rx, ry, start, sweep);
    InvalidateRect(graphicsWindow, &r, TRUE);
    xmin = ScaleX(xc - rx);
    ymin = ScaleY(yc + ry);
    xmax = xmin + PixelsX(2 * rx);
    ymax = ymin + PixelsX(2 * ry);
    if (sweep < 0) {
        start += sweep;
        sweep = -sweep;
    }
    if (start < 0) {
        start = 360 - fmod(-start, 360);
    } else {
        start = fmod(start, 360);
    }
    ix0 = ScaleX(xc + rx * cos(Radians(start)));
    iy0 = ScaleY(yc + ry * sin(Radians(start)));
    ix1 = ScaleX(xc + rx * cos(Radians(start + sweep)));
    iy1 = ScaleY(yc + ry * sin(Radians(start + sweep)));
    Arc(osdc, xmin, ymin, xmax, ymax, ix0, iy0, ix1, iy1);
}

/*
 * Function: RenderArc
 * Usage: RenderArc(xc, yc, rx, ry, start, sweep);
 * -----------------------------------------------
 * This function is identical to DisplayArc except that, instead
 * of calling the Arc function, RenderArc simulates the arc by
 * constructing a path of consecutive segments, which are added
 * to the current polygonal region.
 */

static void RenderArc(double x, double y, double rx, double ry,
                      double start, double sweep)
{
    double t, mint, maxt, dt, maxd;
    int ix0, iy0, ix1, iy1;

    PrepareToDraw();
    if (sweep < 0) {
        start += sweep;
        sweep = -sweep;
    }
    if (fabs(rx) > fabs(ry)) {
        maxd = fabs(rx);
    } else {
        maxd = fabs(rx);
    }
    dt = atan2(InchesY(1), maxd);
    mint = Radians(start);
    maxt = Radians(start + sweep);
    ix0 = ScaleX(x + rx * cos(mint));
    iy0 = ScaleY(y + ry * sin(mint));
    for (t = mint + dt; t < maxt; t += dt) {
        if (t > maxt - dt / 2) t = maxt;
        ix1 = ScaleX(x + rx * cos(t));
        iy1 = ScaleY(y + ry * sin(t));
        AddSegment(ix0, iy0, ix1, iy1);
        ix0 = ix1;
        iy0 = iy1;
    }
}

/*
 * Function: DisplayText
 * Usage: DisplayText(x, y, text);
 * -------------------------------
 * This function displays a text string at (x, y) in the current
 * font and size.  The hard work is done in DisplayFont.
 */

static void DisplayText(double x, double y, string text)
{
    RECT r;

    PrepareToDraw();
    SetTextBB(&r, x, y, text);
    InvalidateRect(graphicsWindow, &r, TRUE);
    SetBkMode(osdc, TRANSPARENT);
    TextOut(osdc, ScaleX(x), ScaleY(y) - fontTable[currentFont].ascent, text, strlen(text));
    SetBkMode(osdc, OPAQUE);
}

/*
 * Function: DisplayFont
 * Usage: DisplayFont(font, size, style);
 * --------------------------------------
 * This function updates the font information used for drawing
 * text.  The program first uses FindExistingFont to see
 * if the desired font/size pair has been entered in the table,
 * in which case the program uses the stored handle of the font.
 * If not, the program uses CreateFont to try to create an
 * appropriate font, accepting only those whose typeface
 * matches the desired font string.  If an acceptable font
 * is found, its data is entered into the font table.
 */

static void DisplayFont(string font, int size, int style)
{
    char fontBuffer[MaxFontName + 1];
    char faceName[MaxFontName + 1];
    string fontName;
    HFONT newFont, oldFont;
    TEXTMETRIC metrics;
    int i, fontIndex;

    for (i = 0; (fontBuffer[i] = tolower(font[i])) != '\0'; i++);
    if (StringEqual("default", fontBuffer)) {
        fontName = DefaultFont;
    } else {
        fontName = fontBuffer;
    }
    fontIndex = FindExistingFont(fontName, size, style);
    if (fontIndex == -1) {
        newFont =
          CreateFont(-size, 0, 0, 0,
                     (style & Bold) ? FW_BOLD : FW_NORMAL,
                     (style & Italic) != 0,
                     0, 0, 0, 0, 0, 0, 0, fontName);
        if (newFont != NULL) {
            oldFont = (HFONT) SelectObject(osdc, newFont);
            GetTextFace(osdc, MaxFontName, faceName);
            if (PrefixMatch(fontName, faceName)
                && GetTextMetrics(osdc, &metrics)) {
                if (nFonts == MaxFonts) Error("Too many fonts loaded");
                fontIndex = nFonts++;
                fontTable[fontIndex].name = CopyString(fontName);
                fontTable[fontIndex].size = size;
                fontTable[fontIndex].style = style;
                fontTable[fontIndex].font = newFont;
                fontTable[fontIndex].ascent = metrics.tmAscent;
                fontTable[fontIndex].descent = metrics.tmDescent;
                fontTable[fontIndex].height =
                  metrics.tmHeight + metrics.tmExternalLeading;
                fontTable[fontIndex].points =
                  metrics.tmHeight - metrics.tmInternalLeading;
                currentFont = fontIndex;
                textFont = CopyString(font);
                pointSize = fontTable[fontIndex].points;
                textStyle = style;
            } else {
                (void) SelectObject(osdc, oldFont);
            }
        }
    } else {
        (void) SelectObject(osdc, fontTable[fontIndex].font);
        currentFont = fontIndex;
        textFont = CopyString(font);
        pointSize = fontTable[fontIndex].points;
        textStyle = style;
    }
}

/*
 * Function: FindExistingFont
 * Usage: fontIndex = FindExistingFont(name, size, style);
 * -------------------------------------------------------
 * This function searches the font table for a matching font
 * entry.  The function returns the matching table index or -1 if
 * no match is found, The caller has already converted the name
 * to lower case to preserve the case-insensitivity requirement.
 */

static int FindExistingFont(string name, int size, int style)
{
    int i;

    for (i = 0; i < nFonts; i++) {
        if (StringEqual(name, fontTable[i].name)
            && size == fontTable[i].size
            && style == fontTable[i].style) return (i);
    }
    return (-1);
}

/*
 * Function: SetLineBB
 * Usage: SetLineBB(&rect, x, y, dx, dy);
 * --------------------------------------
 * This function sets the rectangle dimensions to the bounding
 * box of the line.
 */

static void SetLineBB(RECT *rp, double x, double y, double dx, double dy)
{
    int x0, y0, x1, y1;

    x0 = ScaleX(x);
    y0 = ScaleY(y);
    x1 = ScaleX(x + dx);
    y1 = ScaleY(y + dy);
    rp->top = Min(y0, y1);
    rp->bottom = Max(y0, y1) + 1;
    rp->left = Min(x0, x1);
    rp->right = Max(x0, x1) + 1;
}

/*
 * Function: SetArcBB
 * Usage: SetArcBB(&rect, xc, yc, rx, ry, start, sweep);
 * -----------------------------------------------------
 * This function sets the rectangle dimensions to the bounding
 * box of the arc segment specified by the remaining arguments.
 */

static void SetArcBB(RECT *rp, double xc, double yc,
                     double rx, double ry, double start, double sweep)
{
    int xmax, xmin, ymax, ymin;
    int xl, xr, yt, yb;
    int ix0, iy0, ix1, iy1;

    xmin = ScaleX(xc - rx);
    ymin = ScaleY(yc + ry);
    xmax = xmin + PixelsX(2 * rx);
    ymax = ymin + PixelsX(2 * ry);
    if (sweep < 0) {
        start += sweep;
        sweep = -sweep;
    }
    if (sweep >= 360) {
        SetRect(rp, xmin, ymin, xmax, ymax);
        return;
    }
    if (start < 0) {
        start = 360 - fmod(-start, 360);
    } else {
        start = fmod(start, 360);
    }
    ix0 = ScaleX(xc + rx * cos(Radians(start)));
    iy0 = ScaleY(yc + ry * sin(Radians(start)));
    ix1 = ScaleX(xc + rx * cos(Radians(start + sweep)));
    iy1 = ScaleY(yc + ry * sin(Radians(start + sweep)));
    if (start + sweep > 360) {
        xr = xmax;
    } else {
        xr = Max(ix0, ix1);
    }
    start = fmod(start + 270, 360);
    if (start + sweep > 360) {
        yt = ymin;
    } else {
        yt = Min(iy0, iy1);
    }
    start = fmod(start + 270, 360);
    if (start + sweep > 360) {
        xl = xmin;
    } else {
        xl = Min(ix0, ix1);
    }
    start = fmod(start + 270, 360);
    if (start + sweep > 360) {
        yb = ymax;
    } else {
        yb = Max(iy0, iy1);
    }
    SetRect(rp, xl, yt, xr, yb);
}

/*
 * Function: SetTextBB
 * Usage: SetTextBB(&rect, x, y, text);
 * -------------------------------------
 * This function sets the rectangle dimensions to the bounding
 * box of the text string using the current font and size.
 */

static void SetTextBB(RECT *rp, double x, double y, string text)
{
    SIZE textSize;
    int ix, iy;

    if (!GetTextExtentPoint(osdc, text, strlen(text), &textSize)) {
        Error("Internal error: Text size calculation failed");
    }
    ix = ScaleX(x);
    iy = ScaleY(y);
    SetRect(rp, ix, iy - textSize.cy + fontTable[currentFont].descent,
            ix + textSize.cx, iy + fontTable[currentFont].descent);
}

/*
 * Functions: StartPolygon, AddSegment, EndPolygon
 * Usage: StartPolygon();
 *        AddSegment(x0, y0, x1, y1);
 *        AddSegment(x1, y1, x2, y2);
 *        . . .
 *        DisplayPolygon();
 * ----------------------------------
 * These functions implement the notion of a region in the PC
 * world, where the easiest shape to fill is a polygon.  Calling
 * StartPolygon initializes the array polygonPoints so that
 * subsequent calls to AddSegment will add points to it.
 * The points in the polygon are assumed to be contiguous,
 * because the client interface checks for this property.
 * Because polygons involving arcs can be quite large, the
 * AddSegment code extends the polygonPoints list if needed
 * by doubling the size of the array.  All storage is freed
 * after calling DisplayPolygon.
 */

static void StartPolygon(void)
{
    polygonPoints = NewArray(PStartSize, POINT);
    polygonSize = PStartSize;
    nPolygonPoints = 0;
    SetRect(&polygonBounds, LargeInt, LargeInt, 0, 0);
}

static void AddSegment(int x0, int y0, int x1, int y1)
{
    if (nPolygonPoints == 0) AddPolygonPoint(x0, y0);
    AddPolygonPoint(x1, y1);
}

static void DisplayPolygon(void)
{
    int px;
    HBRUSH brush, oldBrush;
    HPEN oldPen, fillPen;

    PrepareToDraw();
    InvalidateRect(graphicsWindow, &polygonBounds, TRUE);
    if (eraseMode) {
        px = 0;
        fillPen = erasePen;
    } else {
        px = regionDensity * (NFills - 1) + 0.5 - Epsilon;
        fillPen = drawPen;
    }
    oldPen = (HPEN) SelectObject(osdc, fillPen);
    brush = CreatePatternBrush(fillBitmaps[px]);
    if (brush == NULL) {
        Error("Internal error: Can't load brush");
    }
    oldBrush = (HBRUSH) SelectObject(osdc, brush);
    Polygon(osdc, polygonPoints, nPolygonPoints);
    (void) SelectObject(osdc, oldPen);
    if (oldBrush != NULL) (void) SelectObject(osdc, oldBrush);
    FreeBlock(polygonPoints);
    DeleteObject(brush);
}

/*
 * Function: AddPolygonPoint
 * Usage: AddPolygonPoint(x, y);
 * -----------------------------
 * AddPolygonPoint acts as a helper function for AddSegment.  This
 * function does the work, but AddSegment has a more easily understood
 * interface.
 */

static void AddPolygonPoint(int x, int y)
{
    POINT *newPolygon;
    int i;

    if (nPolygonPoints >= polygonSize) {
        polygonSize *= 2;
        newPolygon = NewArray(polygonSize, POINT);
        for (i = 0; i < nPolygonPoints; i++) {
            newPolygon[i] = polygonPoints[i];
        }
        FreeBlock(polygonPoints);
        polygonPoints = newPolygon;
    }
    polygonBounds.left = Min(polygonBounds.left, x);
    polygonBounds.right = Max(polygonBounds.right, x);
    polygonBounds.top = Min(polygonBounds.top, y);
    polygonBounds.bottom = Max(polygonBounds.bottom, y);
    polygonPoints[nPolygonPoints].x = x;
    polygonPoints[nPolygonPoints].y = y;
    nPolygonPoints++;
}

/*
 * Function: InitColors
 * Usage: InitColors();
 * --------------------
 * This function defines the built-in colors.
 */

static void InitColors(void)
{
    nColors = 0;
    DefineColor("Black", 0, 0, 0);
    DefineColor("Dark Gray", .35, .35, .35);
    DefineColor("Gray", .6, .6, .6);
    DefineColor("Light Gray", .75, .75, .75);
    DefineColor("White", 1, 1, 1);
    DefineColor("Brown", .35, .20, .05);
    DefineColor("Red", 1, 0, 0);
    DefineColor("Orange", 1, .40, .1);
    DefineColor("Yellow", 1, 1, 0);
    DefineColor("Green", 0, 1, 0);
    DefineColor("Blue", 0, 0, 1);
    DefineColor("Violet", .93, .5, .93);
    DefineColor("Magenta", 1, 0, 1);
    DefineColor("Cyan", 0, 1, 1);
}

/*
 * Function: FindColorName
 * Usage: index = FindColorName(name);
 * -----------------------------------
 * This function returns the index of the named color in the
 * color table, or -1 if the color does not exist.
 */

static int FindColorName(string name)
{
    int i;

    for (i = 0; i < nColors; i++) {
        if (StringMatch(name, colorTable[i].name)) return (i);
    }
    return (-1);
}

/*
 * Utility functions
 * -----------------
 * This section contains several extremely short utility functions
 * that improve the readability of the code.
 */

/*
 * Function: StringMatch
 * Usage: if (StringMatch(s1, s2)) . . .
 * -------------------------------------
 * This function returns TRUE if two strings are equal, ignoring
 * case distinctions.
 */

static bool StringMatch(string s1, string s2)
{
    register char *cp1, *cp2;

    cp1 = s1;
    cp2 = s2;
    while (tolower(*cp1) == tolower(*cp2)) {
        if (*cp1 == '\0') return (TRUE);
        cp1++;
        cp2++;
    }
    return (FALSE);
}

/*
 * Function: PrefixMatch
 * Usage: if (PrefixMatch(prefix, str)) . . .
 * -------------------------------------------------
 * This function returns TRUE if prefix is the initial substring
 * of str, ignoring differences in case.
 */

static bool PrefixMatch(char *prefix, char *str)
{
    while (*prefix != '\0') {
        if (tolower(*prefix++) != tolower(*str++)) return (FALSE);
    }
    return (TRUE);
}

/*
 * Functions: RectWidth, RectHeight
 * Usage: w = RectWidth(&r);
 *        h = RectHeight(&r);
 * --------------------------------
 * These functions return the width and height of a rectangle.
 */

static int RectWidth(RECT *rp)
{
    return (rp->right - rp->left);
}

static int RectHeight(RECT *rp)
{
    return (rp->bottom - rp->top);
}

/*
 * Functions: SetRectFromSize
 * Usage: SetRectFromSize(&r, x, y, width, height);
 * ------------------------------------------------
 * This function is similar to SetRect except that it takes width
 * and height parameters rather than right and bottom.
 */

static void SetRectFromSize(RECT *rp, int x, int y, int width, int height)
{
    SetRect(rp, x, y, x + width, y + height);
}

/*
 * Function: Radians
 * Usage: radians = Radians(degrees);
 * ----------------------------------
 * This functions convert an angle in degrees to radians.
 */

static double Radians(double degrees)
{
    return (degrees * Pi / 180);
}

/*
 * Function: Round
 * Usage: n = Round(x);
 * --------------------
 * This function rounds a double to the nearest integer.
 */

static int Round(double x)
{
    return ((int) floor(x + 0.5));
}

/*
 * Functions: InchesX, InchesY
 * Usage: inches = InchesX(pixels);
 *        inches = InchesY(pixels);
 * --------------------------------
 * These functions convert distances measured in pixels to inches.
 * Because the resolution may not be uniform in the horizontal and
 * vertical directions, the coordinates are treated separately.
 */

static double InchesX(int x)
{
    return ((double) x / xResolution);
}

static double InchesY(int y)
{
    return ((double) y / yResolution);
}

/*
 * Functions: PixelsX, PixelsY
 * Usage: pixels = PixelsX(inches);
 *        pixels = PixelsY(inches);
 * --------------------------------
 * These functions convert distances measured in inches to pixels.
 */

static int PixelsX(double x)
{
    return (Round(x * xResolution + Epsilon));
}

static int PixelsY(double y)
{
    return (Round(y * yResolution + Epsilon));
}

/*
 * Functions: ScaleX, ScaleY
 * Usage: pixels = ScaleX(inches);
 *        pixels = ScaleY(inches);
 * --------------------------------
 * These functions are like PixelsX and PixelsY but convert coordinates
 * rather than lengths.  The difference is that y-coordinate values must
 * be inverted top to bottom to support the cartesian coordinates of
 * the graphics.h model.
 */

static int ScaleX(double x)
{
    return (PixelsX(x));
}

static int ScaleY(double y)
{
    return (PixelsY(windowHeight - y));
}

/*
 * Functions: Min, Max
 * Usage: min = Min(x, y);
 *        max = Max(x, y);
 * -----------------------
 * These functions find the minimum and maximum of two integers.
 */

static int Min(int x, int y)
{
    return ((x < y) ? x : y);
}

static int Max(int x, int y)
{
    return ((x > y) ? x : y);
}


int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)

{
    MSG messages;            /* Here messages to the application are saved */
    
    Main();

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }
    FreeConsole();
    return messages.wParam;;
}

void registerKeyboardEvent(KeyboardEventCallback callback)
{
	g_keyboard = callback;
}

void registerCharEvent(CharEventCallback callback)
{
	g_char = callback;
}

void registerMouseEvent(MouseEventCallback callback)
{
	g_mouse = callback;
}

void registerTimerEvent(TimerEventCallback callback)
{
	g_timer = callback;
}

void cancelKeyboardEvent()
{
    g_keyboard = NULL;
}

void cancelCharEvent()
{
    g_char = NULL;
}

void cancelMouseEvent()
{
    g_mouse = NULL;
}

void cancelTimerEvent()
{
    g_timer = NULL;
}

void startTimer(int id,int timeinterval)
{
	SetTimer(graphicsWindow, id, timeinterval, NULL);
}

void cancelTimer(int id)
{
	KillTimer(graphicsWindow, id);
}

double ScaleXInches(int x) /*x coordinate from pixels to inches*/
{
 	  return (double)x/GetXResolution();
}
	   
double ScaleYInches(int y)/*y coordinate from pixels to inches*/
{
 	  return GetWindowHeight()-(double)y/GetYResolution();
} 	   
