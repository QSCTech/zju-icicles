/*
 * File: genlib.c
 * Version: 1.0
 * Last modified on Sun Jul 24 10:29:46 1994 by eroberts
 * -----------------------------------------------------
 * This file implements the general C library package.  See the
 * interface description in genlib.h for details.
 */

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdarg.h>

#include "../include/genlib.h"
#include "../include/gcalloc.h"
#include "../include/exception.h"

/*
 * Constants:
 * ----------
 * ErrorExitStatus -- Status value used in exit call
 * MaxErrorMessage -- Longest error message allowed
 */

#define ErrorExitStatus 1
#define MaxErrorMessage 500

/* Section 1 -- Define new "primitive" types */

/*
 * Constant: UNDEFINED
 * -------------------
 * This entry defines the target of the UNDEFINED constant.
 */

char undefined_object[] = "UNDEFINED";

/* Section 2 -- Memory allocation */

/*
 * Implementation notes:
 * ---------------------
 * The code for the memory allocator is divided between
 * genlib.c and gcalloc.c, and the division strategy may at
 * first seem unnatural, since the function ProtectBlock is
 * declared in gcalloc.h but defined here in genlib.c.  The
 * intention is to minimize the size of object files
 * produced by linkers that search a library for modules
 * that are actually referenced.  The libraries themselves
 * need to call ProtectBlock (usually through the macro
 * ProtectVariable), but will not require the actual code
 * for the allocator unless InitGCAllocator is explicitly
 * called.
 */

/*
 * Global variable: _acb
 * ---------------------
 * This variable is used to hold a method suite that makes it
 * easy to substitute a garbage-collecting allocator for the
 * ANSI allocator.
 */

_GCControlBlock _acb = NULL;

/* Memory allocation implementation */

void *GetBlock(size_t nbytes)
{
    void *result;

    if (_acb == NULL) {
        result = malloc(nbytes);
    } else {
        result = _acb->allocMethod(nbytes);
    }
    if (result == NULL) Error("No memory available");
    return (result);
}

void FreeBlock(void *ptr)
{
    if (_acb == NULL) {
        free(ptr);
    } else {
        _acb->freeMethod(ptr);
    }
}

void ProtectBlock(void *ptr, size_t nbytes)
{
    if (_acb != NULL) _acb->protectMethod(ptr, nbytes);
}

/* Section 3 -- Basic error handling */

/*
 * Implementation notes: Error
 * ---------------------------
 * Writing the Error function requires some care, since it is
 * called in circumstances in which parts of the system may be
 * broken.  In particular, it is not acceptable for Error to
 * call GetBlock, since the error condition may be that the
 * system is out of memory, in which case calling GetBlock would
 * fail.  The error string should be allocated dynamically,
 * so that this function can be used in reentrant code.
 * Note that it is critical to exit if the length bound for
 * an error message is exceeded, since this error almost
 * certainly corrupts the stack.
 */

void Error(string msg, ...)
{
    va_list args;
    char errbuf[MaxErrorMessage + 1];
    string errmsg;
    int errlen;

    va_start(args, msg);
    vsprintf(errbuf, msg, args);
    va_end(args);
    errlen = strlen(errbuf);
    if (errlen > MaxErrorMessage) {
        fprintf(stderr, "Error: Error Message too long\n");
        exit(ErrorExitStatus);
    }
    if (_acb == NULL) {
        errmsg = malloc(errlen + 1);
    } else {
        errmsg = _acb->allocMethod(errlen + 1);
    }
    if (errmsg == NULL) {
        errmsg = "No memory available";
    } else {
        strcpy(errmsg, errbuf);
    }
    if (HandlerExists(&ErrorException)) {
        RaiseException(&ErrorException, "ErrorException", errmsg);
    } else {
        fprintf(stderr, "Error: %s\n", errmsg);
        exit(ErrorExitStatus);
    }
}
