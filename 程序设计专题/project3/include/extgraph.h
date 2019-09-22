/*
 * File: extgraph.h
 * Version: 3.0
 * Last modified on Tue Oct  4 11:24:41 1994 by eroberts
 * -----------------------------------------------------
 * This interface is the extended graphics interface.
 * It includes all of the facilities in graphics.h, plus
 * several additional functions that are designed to
 * support more sophisticated, interactive graphics.
 */

#ifndef _extgraph_h
#define _extgraph_h

#include "genlib.h"

/* Exported functions */

/* Section 1 -- Basic functions from graphics.h */

#include "graphics.h"

/* Section 2 -- Elliptical arcs */

/*
 * Function: DrawEllipticalArc
 * Usage: DrawEllipticalArc(rx, ry, start, sweep);
 * -----------------------------------------------
 * This procedure draws an elliptical arc.  It is exactly
 * the same in its operation as DrawArc in the graphics.h
 * interface, except that the radius is different along the
 * two axes.
 */

void DrawEllipticalArc(double rx, double ry,
                       double start, double sweep);

/* Section 3 -- Graphical regions*/

/*
 * Functions: StartFilledRegion, EndFilledRegion
 * Usage: StartFilledRegion(density);
 *        . . . other calls . . .
 *        EndFilledRegion();
 * ------------------------------
 * These calls make it possible to draw filled shapes on the
 * display.  After calling StartFilledRegion, any calls to
 * DrawLine and DrawArc are used to create a shape definition
 * and do not appear on the screen until EndFilledRegion is
 * called.  The lines and arcs must be consecutive, in the
 * sense that each new element must start where the last
 * one ended.  MovePen calls may occur at the beginning
 * or the end of the region, but not in the interior. When
 * EndFilledRegion is called, the entire region appears on the
 * screen, with its interior filled in.  The density parameter
 * is a number between 0 and 1 and indicates how the dot density
 * to be used for the fill pattern.  If density is 1, the shape
 * will be filled in a solid color; if it is 0, the fill will be
 * invisible.  In between, the implementation will use a dot
 * pattern that colors some of the screen dots but not others.
 */

void StartFilledRegion(double density);
void EndFilledRegion(void);

/* Section 4 -- String functions */

/*
 * Function: DrawTextString
 * Usage: DrawTextString(text);
 * ----------------------------
 * This function displays the string text at the current point
 * in the current font and size.  The current point is updated
 * so that the next DrawTextString command would continue from
 * the next character position.  The string may not include the
 * newline character.
 */

void DrawTextString(string text);

/*
 * Function: TextStringWidth
 * Usage: w = TextStringWidth(text);
 * ---------------------------------
 * This function returns the width of the text string if displayed
 * at the current font and size.
 */

double TextStringWidth(string text);

/*
 * Function: SetFont
 * Usage: SetFont(font);
 * ---------------------
 * This function sets a new font according to the font string,
 * which is case-independent.  Different systems support different
 * fonts, although common ones like "Times" and "Courier" are often
 * supported.  Initially, the font is set to "Default" which is
 * always supported, although the underlying font is system
 * dependent.  If the font name is unrecognized, no error is
 * generated, and the font remains unchanged.  If you need to
 * detect this condition, you can call GetFont to see if the
 * change took effect.  By not generating an error in this case,
 * programs become more portable.
 */

void SetFont(string font);

/*
 * Function: GetFont
 * Usage: font = GetFont();
 * ------------------------
 * This function returns the current font name as a string.
 */

string GetFont(void);

/*
 * Function: SetPointSize
 * Usage: SetPointSize(size);
 * --------------------------
 * This function sets a new point size.  If the point size is
 * not supported for a particular font, the closest existing
 * size is selected.
 */

void SetPointSize(int size);

/*
 * Function: GetPointSize
 * Usage: size = GetPointSize();
 * -----------------------------
 * This function returns the current point size.
 */

int GetPointSize(void);

/*
 * Text style constants
 * --------------------
 * The constants Bold and Italic are used in the SetStyle
 * command to specify the desired text style.  They may also
 * be used in combination by adding these constants together,
 * as in Bold + Italic.  The constant Normal indicates the
 * default style.
 */

#define Normal  0
#define Bold    1
#define Italic  2

/*
 * Function: SetStyle
 * Usage: SetStyle(style);
 * -----------------------
 * This function establishes the current style properties
 * for text based on the parameter style, which is an integer
 * representing the sum of any of the text style constants.
 */

void SetStyle(int style);

/*
 * Function: GetStyle
 * Usage: style = GetStyle();
 * --------------------------
 * This function returns the current style.
 */

int GetStyle(void);

/*
 * Functions: GetFontAscent, GetFontDescent, GetFontHeight
 * Usage: ascent = GetFontAscent();
 *        descent = GetFontDescent();
 *        height = GetFontHeight();
 * -------------------------------------------------------
 * These functions return properties of the current font that are
 * used to calculate how to position text vertically on the page.
 * The ascent of a font is the distance from the baseline to the
 * top of the largest character; the descent is the maximum
 * distance any character extends below the baseline.  The height
 * is the total distance between two lines of text, including the
 * interline space (which is called leading).
 *
 * Examples:
 *   To change the value of y so that it indicates the next text
 *   line, you need to execute
 *
 *        y -= GetFontHeight();
 *
 *   To center text vertically around the coordinate y, you need
 *   to start the pen at
 *
 *       y - GetFontAscent() / 2
 */

double GetFontAscent(void);
double GetFontDescent(void);
double GetFontHeight(void);

/* Section 5 -- Mouse support */

/*
 * Functions: GetMouseX, GetMouseY
 * Usage: x = GetMouseX();
 *        y = GetMouseY();
 * -------------------------------
 * These functions return the x and y coordinates of the mouse,
 * respectively.  The coordinate values are real numbers measured
 * in inches from the origin and therefore match the drawing
 * coordinates.
 */

double GetMouseX(void);
double GetMouseY(void);

/*
 * Functions: MouseButtonIsDown
 * Usage: if (MouseButtonIsDown()) . . .
 * -------------------------------------
 * This function returns TRUE if the mouse button is currently
 * down.  For maximum compatibility among implementations, the
 * mouse is assumed to have one button.  If the mouse has more
 * than one button, this function returns TRUE if any button
 * is down.
 */

bool MouseButtonIsDown(void);

/*
 * Functions: WaitForMouseDown, WaitForMouseUp
 * Usage: WaitForMouseDown();
 *        WaitForMouseUp();
 * -------------------------------------------
 * The WaitForMouseDown function waits until the mouse button
 * is pressed and then returns.  WaitForMouseUp waits for the
 * button to be released.
 */

void WaitForMouseDown(void);
void WaitForMouseUp(void);

/* Section 6 -- Color support */

/*
 * Function: HasColor
 * Usage: if (HasColor()) . . .
 * ----------------------------
 * This function returns TRUE if the graphics window can display a
 * color image.  Note that this condition is stronger than simply
 * checking whether a color display is available.  Because color
 * windows require more memory than black and white ones, this
 * function will return FALSE with a color screen if there is
 * not enough memory to store a colored image.  On the Macintosh,
 * for example, it is usually necessary to increase the partition
 * size to at least 1MB before color windows can be created.
 */

bool HasColor(void);

/*
 * Function: SetPenColor
 * Usage: SetPenColor(color);
 * --------------------------
 * This function sets the color of the pen used for any drawing,
 * including lines, text, and filled regions.  The color is a
 * string, which will ordinarily be one of the following
 * predefined color names:
 *
 *    Black, Dark Gray, Gray, Light Gray, White,
 *    Red, Yellow, Green, Cyan, Blue, Magenta
 *
 * The first line corresponds to standard gray scales and the
 * second to the primary and secondary colors of light.  The
 * built-in set is limited to these colors because they are
 * likely to be the same on all hardware devices.  For finer
 * color control, you can use the DefineColor function to
 * create new color names as well.
 */

void SetPenColor(string color);

/*
 * Function: GetPenColor
 * Usage: color = GetPenColor();
 * -----------------------------
 * This function returns the current pen color as a string.
 */

string GetPenColor(void);

/*
 * Function: SetPenSize
 * Usage: SetPenSize(size);
 * -----------------------------------------
 * This function sets the size(in pixels) of the pen used for any drawing.
 */

void SetPenSize(int size);

/*
 * Function: GetPenSize
 * Usage: size = GetPenSize();
 * -----------------------------------------
 * This function returns the size(in pixels) of the pen used for any drawing.
 */

int GetPenSize(void);

/*
 * Function: DefineColor
 * Usage: DefineColor(name, red, green, blue);
 * -------------------------------------------
 * This function allows the client to define a new color name
 * by supplying intensity levels for the colors red, green,
 * and blue, which are the primary colors of light.  The
 * color values are provided as real numbers between 0 and 1,
 * indicating the intensity of that color.  For example,
 * the predefined color Magenta has full intensity red and
 * blue but no green and is therefore defined as:
 *
 *      DefineColor("Magenta", 1, 0, 1);
 *
 * DefineColor allows you to create intermediate colors on
 * many displays, although the results vary significantly
 * depending on the hardware.  For example, the following
 * usually gives a reasonable approximation of brown:
 *
 *      DefineColor("Brown", .35, .20, .05);
 */

void DefineColor(string name,
                 double red, double green, double blue);

/* Section 7 -- Miscellaneous functions */

/*
 * Function: SetEraseMode
 * Usage: SetEraseMode(TRUE);
 *        SetEraseMode(FALSE);
 * ---------------------------
 * The SetEraseMode function sets the value of the internal
 * erasing flag.  Setting this flag is similar to setting the
 * color to "White" in its effect but does not affect the
 * current color setting.  When erase mode is set to FALSE,
 * normal drawing is restored, using the current color.
 */

void SetEraseMode(bool mode);

/*
 * Function: GetEraseMode
 * Usage: mode = GetEraseMode();
 * -----------------------------
 * This function returns the current state of the erase mode flag.
 */

bool GetEraseMode(void);

/*
 * Function: SetWindowTitle
 * Usage: SetWindowTitle(title);
 * -----------------------------
 * This function sets the title of the graphics window, if such
 * an operation is possible on the display.  If it is not possible
 * for a particular implementation, the call is simply ignored.
 * This function may be called prior to the InitGraphics call to
 * set the initial name of the window.
 */

void SetWindowTitle(string title);

/*
 * Function: GetWindowTitle
 * Usage: title = GetWindowTitle();
 * --------------------------------
 * This function returns the title of the graphics window.  If the
 * implementation does not support titles, this call returns the
 * empty string.
 */

string GetWindowTitle(void);

/*
 * Function: UpdateDisplay
 * Usage: UpdateDisplay();
 * -----------------------
 * This function initiates an immediate update of the graphics
 * window and is necessary for animation.  Ordinarily, the
 * graphics window is updated only when the program waits for
 * user input.
 */

void UpdateDisplay(void);

/*
 * Function: Pause
 * Usage: Pause(seconds);
 * ----------------------
 * The Pause function updates the graphics window and then
 * pauses for the indicated number of seconds.  This function
 * is useful for animation where the motion would otherwise
 * be too fast.
 */

void Pause(double seconds);

/*
 * Function: ExitGraphics
 * Usage: ExitGraphics();
 * ----------------------
 * The ExitGraphics function closes the graphics window and
 * exits from the application without waiting for any additional
 * user interaction.
 */

void ExitGraphics(void);

/*
 * Functions: SaveGraphicsState, RestoreGraphicsState
 * Usage: SaveGraphicsState();
 *        . . . graphical operations . . .
 *        RestoreGraphicsState();
 * ---------------------------------------------------
 * The SaveGraphicsState function saves the current graphics
 * state (the current pen position, the font, the point size,
 * and the erase mode flag) internally, so that they can be
 * restored by the next RestoreGraphicsState call.  These two
 * functions must be used in pairs but may be nested to any depth.
 */

void SaveGraphicsState(void);
void RestoreGraphicsState(void);

/*
 * Functions: GetFullScreenWidth, GetFullScreenHeight
 * Usage: width = GetFullScreenWidth();
 *        height = GetFullScreenHeight();
 * --------------------------------------
 * These functions return the height and width of the entire
 * display screen, not the graphics window.  Their only
 * significant use is for applications that need to adjust
 * the size of the graphics window based on available screen
 * space.  These functions may be called before InitGraphics
 * has been called.
 */

double GetFullScreenWidth(void);
double GetFullScreenHeight(void);

/*
 * Functions: SetWindowSize
 * Usage: SetWindowSize(width, height);
 * ------------------------------------
 * This function sets the window size to the indicated dimensions,
 * if possible.  This function should be called before the graphics
 * window is created by InitGraphics.  Attempts to change the size
 * of an existing window are ignored by most implementations.  This
 * function should be used sparingly because it reduces the
 * portability of applications, particularly if the client
 * requests more space than is available on the screen.
 */

void SetWindowSize(double width, double height);

/*
 * Functions: GetXResolution, GetYResolution
 * Usage: xres = GetXResolution();
 *        yres = GetYResolution();
 * -----------------------------------------
 * These functions return the number of pixels per inch along
 * each of the coordinate directions and are useful for applications
 * in which it is important for short distances to be represented
 * uniformly in terms of dot spacing.  Even though the x and y
 * resolutions are the same for most displays, clients should
 * not rely on this property.
 *
 * Note: Lines in the graphics library are one pixel unit wide and
 * have a length that is always one pixel longer than you might
 * expect.  For example, the function call
 *
 *     DrawLine(2 / GetXResolution(), 0);
 *
 * draws a line from the current point to the point two pixels
 * further right, which results in a line of three pixels.
 */
 
double GetXResolution(void);
double GetYResolution(void);
 
/*pixels to inches*/
double ScaleXInches(int x);
double ScaleYInches(int y);

#endif
