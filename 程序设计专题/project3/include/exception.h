/*
 * File: exception.h
 * Version: 1.0
 * Last modified on Sun Jul 24 10:26:20 1994 by eroberts
 * -----------------------------------------------------
 * The exception package provides a general exception
 * handling mechanism for use with C that is portable
 * across a variety of compilers and operating systems.
 */

#ifndef _exception_h
#define _exception_h

/*
 * Overview:
 * --------
 * The exception package makes it possible for clients to
 * specify a handler for an exceptional conditions in a
 * syntactically readable way.  As a client, your first step
 * is to declare an exception condition name by declaring
 * a variable of type exception, as in
 *
 *       exception MyException;
 *
 * Normal visibility rules apply, so that you should declare
 * the exception variable at the appropriate level.  For
 * example, if an exception is local to an implementation,
 * it should be declared statically within that module.  If
 * an exception condition is shared by many modules, the
 * exception variable should be declared in an interface
 * and exported to all clients that need it.  This package
 * defines and exports the exception ErrorException, which
 * is likely to be sufficient for many clients.
 *
 * The basic functionality of exceptions is that one piece
 * of code can "raise" an exception so that it can then be
 * "handled" by special code in a dynamically enclosing
 * section of the program.  Exceptions are raised by calling
 * the pseudo-function raise with the exception name, as in
 *
 *     raise(MyException);
 *
 * Exceptions are handled using the "try" statement
 * (actually implemented using macros), which has the form:
 *
 *     try {
 *        . . . statements in the body of the block . . .
 *     except(exception1)
 *        . . . statements to handle exception 1 . . .
 *     except(exception2)
 *        . . . statements to handle exception 2 . . .
 *     except(ANY)
 *        . . . statements to handle any exception . . .
 *     } endtry
 *
 * Any number of except clauses may appear (up to a
 * maximum defined by the constant MaxExceptionsPerScope),
 * and the ANY clause is optional.
 *
 * When the program encounters the "try" statement, the
 * statements in the body are executed.  If no exception
 * conditions are raised during that execution, either
 * in this block or by a function call nested inside
 * this block, control passes to the end of the "try"
 * statement when the last statement in the block is
 * executed.  If an exception is raised during the
 * dynamic execution of the block, control immediately
 * passes to the statements in the appropriate except
 * clause.  Only the statements in that clause are
 * executed; no break statement is required to exit
 * the block.  If no handler for the raised exception
 * appears anywhere in the control history, the program
 * exits with an error.
 *
 * Examples of use:
 *
 * 1.  Catching errors.
 *
 * The following code fragment traps calls to Error, so
 * that the program does not quit but instead returns
 * to the top-level read-and-execute loop.
 *
 *     while (TRUE) {
 *         try {
 *             printf("> ");
 *             cmd = ReadCommand();
 *             ExecuteCommand(cmd);
 *         except(ErrorException)
 *             -- additional handling code, if any --
 *         } endtry
 *     }
 *
 * If either ReadCommand or ExecuteCommand calls Error,
 * control will be passed back to the main loop, after
 * executing any additional handler code.  (The error
 * message is printed by the Error routine, so it is
 * often the case that no additional work is needed.)
 *
 * 2.  Handling control-C
 *
 * The following code extends the example above so that
 * typing ^C also returns to top-level.
 *
 *     #include <signal.h>
 *
 *     static exception ControlCException;
 *     static int errorCount = 0;
 *     static int ControlCHandler();
 *
 *     main()
 *     {
 *         string cmd;
 *
 *         signal(SIGINT, ControlCHandler);
 *         while (TRUE) {
 *             try {
 *                 printf("> ");
 *                 cmd = ReadCommand();
 *                 ExecuteCommand(cmd);
 *             except(ControlCException);
 *                 printf("^C\n");
 *                 signal(SIGINT, ControlCHandler);
 *             except(ErrorException)
 *                 errorCount++;
 *             } endtry
 *         }
 *     }
 *
 *     static int ControlCHandler()
 *     {
 *         raise(ControlCException);
 *     }
 */

/*
 * Actual interface specification
 * ------------------------------
 * Most of the implementation of the exception mechanism is
 * actually done in the macros defined by this file.
 * Clients should ordinarily be able to read the description
 * above and ignore the detailed code below.
 */

#include <setjmp.h>
#include <string.h>
#include "genlib.h"

/* Define parameters and error status indicators */

#define MaxExceptionsPerScope 10
#define ETooManyExceptClauses 101
#define EUnhandledException 102

/* Codes to keep track of the state of the try handler */

#define ES_Initialize 0
#define ES_EvalBody 1
#define ES_Exception 2

/*
 * Type: exception
 * ---------------
 * Exceptions are specified by their address, so that the
 * actual structure does not matter.  Strings are used here
 * so that exporters of exceptions can store the exception
 * name for the use of debuggers and other tools.
 */

typedef struct { string name; } exception;

/*
 * Type: context_block
 * -------------------
 * This structure is used internally to maintain a chain of
 * exception scopes on the control stack.
 */

typedef struct ctx_block {
    jmp_buf jmp;
    int nx;
    exception *array[MaxExceptionsPerScope];
    exception *id;
    void *value;
    string name;
    struct ctx_block *link;
} context_block;

/* Declare the built-in exceptions */

extern exception ErrorException;
extern exception ANY;

/* Declare a global pointer to the context stack */

extern context_block *exceptionStack;

/*
 * Function: RaiseException
 * Usage: RaiseException(&e, name, value);
 * ---------------------------------------
 * This function is called by the raise macro and does the
 * work necessary to raise the exception.  See the exception.c file
 * for details.  Clients do not ordinarily call this directly.
 */

void RaiseException(exception *e, string name, void *value);

/*
 * Function: HandlerExists
 * Usage: if (HandlerExists(&e)) ...
 * ---------------------------------
 * Determines whether a handler exists for an exception in
 * the dynamically enclosing scope.  Intended only for use
 * by special clients, such as the Error package.
 */

bool HandlerExists(exception *e);

/* Define the pseudo-functions for raise and try */

#define raise(e) RaiseException(&e, #e, NULL)

#define try \
      { \
          jmp_buf _tmpbuf; \
          context_block _ctx; \
          volatile int _es; \
          _es = ES_Initialize; \
          _ctx.nx = 0; \
          _ctx.link = exceptionStack; \
          exceptionStack = (context_block *) &_ctx; \
          if (setjmp(_tmpbuf) != 0) _es = ES_Exception; \
          memcpy((void *) _ctx.jmp, (void *) _tmpbuf, sizeof(jmp_buf)); \
          while (1) { \
              if (_es == ES_EvalBody)

#define except(e) \
                  if (_es == ES_EvalBody) exceptionStack = _ctx.link; \
                  break; \
              } \
              if (_es == ES_Initialize) { \
                  if (_ctx.nx >= MaxExceptionsPerScope) \
                      exit(ETooManyExceptClauses); \
                  _ctx.array[_ctx.nx++] = &e; \
              } else if (_ctx.id == &e || &e == &ANY) { \
                  exceptionStack = _ctx.link;

#define endtry \
              if (_es != ES_Initialize) break; \
              _es = ES_EvalBody; \
          } \
      }

#define GetExceptionName() _ctx.name
#define GetExceptionValue() _ctx.value
#define GetCurrentException() _ctx.id

#endif
