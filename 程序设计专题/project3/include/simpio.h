/*
 * File: simpio.h
 * Version: 1.0
 * Last modified on Wed Apr 27 07:29:13 1994 by eroberts
 * -----------------------------------------------------
 * This interface provides access to a simple package of
 * functions that simplify the reading of input data.
 */

#ifndef _simpio_h
#define _simpio_h

#include "genlib.h"

/*
 * Function: GetInteger
 * Usage: i = GetInteger();
 * ------------------------
 * GetInteger reads a line of text from standard input and scans
 * it as an integer.  The integer value is returned.  If an
 * integer cannot be scanned or if more characters follow the
 * number, the user is given a chance to retry.
 */

int GetInteger(void);

/*
 * Function: GetLong
 * Usage: l = GetLong();
 * ---------------------
 * GetLong reads a line of text from standard input and scans
 * it as a long integer.  The value is returned as a long.
 * If an integer cannot be scanned or if more characters follow
 * the number, the user is given a chance to retry.
 */

long GetLong(void);

/*
 * Function: GetReal
 * Usage: x = GetReal();
 * ---------------------
 * GetReal reads a line of text from standard input and scans
 * it as a double.  If the number cannot be scanned or if extra
 * characters follow after the number ends, the user is given
 * a chance to reenter the value.
 */

double GetReal(void);

/*
 * Function: GetLine
 * Usage: s = GetLine();
 * ---------------------
 * GetLine reads a line of text from standard input and returns
 * the line as a string.  The newline character that terminates
 * the input is not stored as part of the string.
 */

string GetLine(void);

/*
 * Function: ReadLine
 * Usage: s = ReadLine(infile);
 * ----------------------------
 * ReadLine reads a line of text from the input file and
 * returns the line as a string.  The newline character
 * that terminates the input is not stored as part of the
 * string.  The ReadLine function returns NULL if infile
 * is at the end-of-file position.
 */

string ReadLine(FILE *infile);

#endif
