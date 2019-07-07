/*
 * File: genlib.h
 * Version: 1.0
 * Last modified on Sun Jul 24 10:32:49 1994 by eroberts
 * -----------------------------------------------------
 * This file contains several definitions that form the
 * core of a general-purpose ANSI C library developed by Eric
 * Roberts.  The goal of this library is to provide a basic
 * set of tools and conventions that increase the readability
 * of C programs, particularly as they are used in a teaching
 * environment.
 *
 * The basic definitions provided by genlib.h are:
 *
 *    1.  Declarations for several new "primitive" types
 *        (most importantly bool and string) that are
 *        used throughout the other libraries and
 *        applications as fundamental types.
 *
 *    2.  A new set of functions for memory allocation.
 *
 *    3.  A function for error handling.
 *
 *    4.  A repeat statement for loops with interior exits.
 */

#ifndef _genlib_h
#define _genlib_h

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/* Section 1 -- Define new "primitive" types */

/*
 * Type: bool
 * ----------
 * This type has two values, FALSE and TRUE, which are equal to 0
 * and 1, respectively.  Most of the advantage of defining this type
 * comes from readability because it allows the programmer to
 * provide documentation that a variable will take on only one of
 * these two values.  Designing a portable representation, however,
 * is surprisingly hard, because many libraries and some compilers
 * define these names.  The definitions are usually compatible but
 * may still be flagged as errors.
 */

#ifdef THINK_C
   typedef int bool;
#else
#  ifdef TRUE
#    ifndef bool
#      define bool int
#    endif
#  else
#    ifdef bool
#      define FALSE 0
#      define TRUE 1
#    else
       typedef enum {FALSE, TRUE} bool;
#    endif
#  endif
#endif

/*
 * Type: string
 * ------------
 * The type string is identical to the type char *, which is
 * traditionally used in C programs.  The main point of defining a
 * new type is to improve program readability.   At the abstraction
 * levels at which the type string is used, it is usually not
 * important to take the string apart into its component characters.
 * Declaring it as a string emphasizes this atomicity.
 */

typedef char *string;

/*
 * Type: stream
 * ------------
 * Like string, the stream type is used to provide additional
 * readability and is defined to be equivalent to FILE *
 * (which is particularly confusing because it violates
 * standard case conventions).  This type is not used in
 * the text but is preserved in genlib.h, so it is possible
 * to teach all of CS1 without exposing any pointers.
 */

typedef FILE *stream;

/*
 * Constant: UNDEFINED
 * -------------------
 * Besides NULL, the only other constant of pointer type is
 * UNDEFINED, which is used in certain packages as a special
 * sentinel to indicate an undefined pointer value.  In many
 * such contexts, NULL is a legitimate data value and is
 * therefore inappropriate as a sentinel.
 */

#define UNDEFINED ((void *) undefined_object)

extern char undefined_object[];

/* Section 2 -- Memory allocation */

/*
 * General notes:
 * --------------
 * These functions provide a common interface for memory
 * allocation.  All functions in the library that allocate
 * memory do so using GetBlock and FreeBlock.  Even though
 * the ANSI standard defines malloc and free for the same
 * purpose, using GetBlock and FreeBlock provides greater
 * compatibility with non-ANSI implementations, automatic
 * out-of-memory error detection, and the possibility of
 * substituting a garbage-collecting allocator.
 */

/*
 * Function: GetBlock
 * Usage: ptr = (type) GetBlock(nbytes);
 * -------------------------------------
 * GetBlock allocates a block of memory of the given size.  If
 * no memory is available, GetBlock generates an error.
 */

void *GetBlock(size_t nbytes);

/*
 * Function: FreeBlock
 * Usage: FreeBlock(ptr);
 * ----------------------
 * FreeBlock frees the memory associated with ptr, which must
 * have been allocated using GetBlock, New, or NewArray.
 */

void FreeBlock(void *ptr);

/*
 * Macro: New
 * Usage: p = New(pointer-type);
 * -----------------------------
 * The New pseudofunction allocates enough space to hold an
 * object of the type to which pointer-type points and returns
 * a pointer to the newly allocated pointer.  Note that
 * "New" is different from the "new" operator used in C++;
 * the former takes a pointer type and the latter takes the
 * target type.
 */

#define New(type) ((type) GetBlock(sizeof *((type) NULL)))

/*
 * Macro: NewArray
 * Usage: p = NewArray(n, element-type);
 * -------------------------------------
 * NewArray allocates enough space to hold an array of n
 * values of the specified element type.
 */

#define NewArray(n, type) ((type *) GetBlock((n) * sizeof (type)))

/* Section 3 -- Basic error handling */

/*
 * Function: Error
 * Usage: Error(msg, ...)
 * ----------------------
 * Error generates an error string, expanding % constructions
 * appearing in the error message string just as printf does.
 * If an error handler exception has been introduced (see the
 * "exception.h" facility), the ErrorException exception is
 * raised with the expanded error string as argument.  If
 * there is no ErrorException defined, the program exits
 * with a status code indicating failure (as given by the
 * constant ErrorExitStatus).  The length of the error
 * message string following expansion must not exceed
 * MaxErrorMessage, and it is the client's responsibility
 * to ensure this.
 */

void Error(string msg, ...);

/* Section 4 -- The repeat pseudo-statement */

/*
 * Statement form: repeat { ... }
 * ------------------------------
 * Some instructors who have taught CS1 using this library
 * have found that using
 *
 *     while (TRUE)
 *
 * to initiate a loop with an interior exit is confusing to
 * students, particularly when it comes at the beginning of
 * the course.  This macro defines "repeat" as an infinite
 * loop construct for instructors who find it easier to
 * explain, although it is not used in the text.   Similar
 * macro definitions are common in industry.
 */

#define repeat for (;;)

#endif
