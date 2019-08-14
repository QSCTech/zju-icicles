/*
 * File: simpio.c
 * Version: 3.0
 * Last modified on Tue Oct  4 11:24:40 1994 by eroberts
 * -----------------------------------------------------
 * This file implements the simpio.h interface.
 */

#include <stdio.h>
#include <string.h>

#include "../include/genlib.h"
#include "../include/strlib.h"
#include "../include/simpio.h"

/*
 * Constants:
 * ----------
 * InitialBufferSize -- Initial buffer size for ReadLine
 */

#define InitialBufferSize 120

/* Exported entries */

/*
 * Functions: GetInteger, GetLong, GetReal
 * ---------------------------------------
 * These functions first read a line and then call sscanf to
 * translate the number.  Reading an entire line is essential to
 * good error recovery, because the characters after the point of
 * error would otherwise remain in the input buffer and confuse
 * subsequent input operations.  The sscanf line allows white space
 * before and after the number but no other extraneous characters.
 */

int GetInteger(void)
{
    string line;
    int value;
    char termch;

    while (TRUE) {
        line = GetLine();
        if (line == NULL) Error("GetInteger: unexpected end of file");
        switch (sscanf(line, " %d %c", &value, &termch)) {
          case 1:
            FreeBlock(line);
            return (value);
          case 2:
            printf("Unexpected character: '%c'\n", termch);
            break;
          default:
            printf("Please enter an integer\n");
            break;
        }
        FreeBlock(line);
        printf("Retry: ");
    }
}

long GetLong(void)
{
    string line;
    long value;
    char termch;

    while (TRUE) {
        line = GetLine();
        if (line == NULL) Error("GetLong: unexpected end of file");
        switch (sscanf(line, " %ld %c", &value, &termch)) {
          case 1:
            FreeBlock(line);
            return (value);
          case 2:
            printf("Unexpected character: '%c'\n", termch);
            break;
          default:
            printf("Please enter an integer\n");
            break;
        }
        FreeBlock(line);
        printf("Retry: ");
    }
}

double GetReal(void)
{
    string line;
    double value;
    char termch;

    while (TRUE) {
        line = GetLine();
        if (line == NULL) Error("GetReal: unexpected end of file");
        switch (sscanf(line, " %lf %c", &value, &termch)) {
          case 1:
            FreeBlock(line);
            return (value);
          case 2:
            printf("Unexpected character: '%c'\n", termch);
            break;
          default:
            printf("Please enter a real number\n");
            break;
        }
        FreeBlock(line);
        printf("Retry: ");
    }
}

/*
 * Function: GetLine
 * -----------------
 * This function is a simple wrapper; all the work is done by
 * ReadLine.
 */

string GetLine(void)
{
    return (ReadLine(stdin));
}

/*
 * Function: ReadLine
 * ------------------
 * This function operates by reading characters from the file
 * into a dynamically allocated buffer.  If the buffer becomes
 * full before the end of the line is reached, a new buffer
 * twice the size of the previous one is allocated.
 */

string ReadLine(FILE *infile)
{
    string line, nline;
    int n, ch, size;

    n = 0;
    size = InitialBufferSize;
    line = GetBlock(size + 1);
    while ((ch = getc(infile)) != '\n' && ch != EOF) {
        if (n == size) {
            size *= 2;
            nline = (string) GetBlock(size + 1);
            strncpy(nline, line, n);
            FreeBlock(line);
            line = nline;
        }
        line[n++] = ch;
    }
    if (n == 0 && ch == EOF) {
        FreeBlock(line);
        return (NULL);
    }
    line[n] = '\0';
    nline = (string) GetBlock(n + 1);
    strcpy(nline, line);
    FreeBlock(line);
    return (nline);
}
