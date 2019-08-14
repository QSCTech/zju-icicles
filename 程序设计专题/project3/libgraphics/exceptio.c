/*
 * File: exception.c
 * Version: 1.0
 * Last modified on Sun Jul 24 10:28:11 1994 by eroberts
 * -----------------------------------------------------
 * This file implements the C exception handler.  Much of the
 * real work is done in the exception.h header file.
 */

#include <stdio.h>
#include <stdarg.h>

#include "../include/genlib.h"
#include "../include/gcalloc.h"
#include "../include/exception.h"

/*
 * Constant: MaxUnhandledMessage
 * -----------------------------
 * This constant should be large enough to accommodate the
 * unhandled exception message, including the exception name.
 */

#define MaxUnhandledMessage 100

/* Publically accessible exceptions */

exception ANY = { "ANY" };
exception ErrorException = { "ErrorException" };

/*
 * Global variable: exceptionStack
 * -------------------------------
 * This variable is the head pointer to a linked list of
 * context blocks that act as the exception stack.  The chain
 * pointer is referenced by the macros in exception.h and must
 * therefore be exported, but clients should not reference it
 * directly.
 */

context_block *exceptionStack = NULL;

/* Private function prototypes */

static context_block *FindHandler(exception *e);

/* Public entries */

/*
 * Function: RaiseException
 * ------------------------
 * This function operates by finding an appropriate handler
 * and then using longjmp to return to the context stored
 * there after resetting the exception stack.  If no handler
 * exists, the function notes an unhandled exception.  Much
 * of the complexity comes from the fact that allocation
 * within the exception handler may fail.
 */

void RaiseException(exception *e, string name, void *value)
{
    context_block *cb;
    char errbuf[MaxUnhandledMessage + 1];
    string errmsg;
    int errlen;

    cb = FindHandler(e);
    if (cb == NULL) {
        sprintf(errbuf, "Unhandled exception (%.30s)", name);
        errlen = strlen(errbuf);
        if (_acb == NULL) {
            errmsg = malloc(errlen + 1);
        } else {
            errmsg = _acb->allocMethod(errlen + 1);
        }
        if (errmsg == NULL) {
            errmsg = "Unhandled exception: unknown";
        } else {
            strcpy(errmsg, errbuf);
        }
        Error(errmsg);
    }
    exceptionStack = cb;
    cb->id = e;
    cb->value = value;
    cb->name = name;
    longjmp(cb->jmp, ES_Exception);
}

/*
 * Function: HandlerExists
 * -----------------------
 * This public entry is used primarily by the Error function
 * to determine if ErrorException has been trapped, although
 * it is available to other clients as well.
 */

bool HandlerExists(exception *e)
{
    return (FindHandler(e) != NULL);
}

/* Private functions */

/*
 * Function: FindHandler
 * ---------------------
 * This function searches the exception stack to find the
 * first active handler for the indicated exception.  If a
 * match is found, the context block pointer is returned.
 * If not, FindHandler returns NULL.
 */

static context_block *FindHandler(exception *e)
{
    context_block *cb;
    exception *t;
    int i;

    for (cb = exceptionStack; cb != NULL; cb = cb->link) {
        for (i = 0; i < cb->nx; i++) {
            t = cb->array[i];
            if (t == e || t == &ANY) return (cb);
        }
    }
    return (NULL);
}
