/*
 * File: random.c
 * Version: 1.0
 * Last modified on Mon Sep 13 10:42:45 1993 by eroberts
 * -----------------------------------------------------
 * This file implements the random.h interface.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/genlib.h"
#include "../include/random.h"

/*
 * Function: Randomize
 * -------------------
 * This function operates by setting the random number
 * seed to the current time.  The srand function is
 * provided by the <stdlib.h> library and requires an
 * integer argument.  The time function is provided
 * by <time.h>.
 */

void Randomize(void)
{
    srand((int) time(NULL));
}

/*
 * Function: RandomInteger
 * -----------------------
 * This function first obtains a random integer in
 * the range [0..RAND_MAX] by applying four steps:
 * (1) Generate a real number between 0 and 1.
 * (2) Scale it to the appropriate range size.
 * (3) Truncate the value to an integer.
 * (4) Translate it to the appropriate starting point.
 */

int RandomInteger(int low, int high)
{
    int k;
    double d;

    d = (double) rand() / ((double) RAND_MAX + 1);
    k = (int) (d * (high - low + 1));
    return (low + k);
}

/*
 * Function: RandomReal
 * --------------------
 * The implementation of RandomReal is similar to that
 * of RandomInteger, without the truncation step.
 */

double RandomReal(double low, double high)
{
    double d;

    d = (double) rand() / ((double) RAND_MAX + 1);
    return (low + d * (high - low));
}

/*
 * Function: RandomChance
 * ----------------------
 * This function uses RandomReal to generate a number
 * between 0 and 100, which it then compares to p.
 */

bool RandomChance(double p)
{
    return (RandomReal(0, 1) < p);
}
