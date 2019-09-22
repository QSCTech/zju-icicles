/*
 * File: gcalloc.h
 * Version: 1.0
 * Last modified on Wed Sep 21 16:21:37 1994 by eroberts
 * -----------------------------------------------------
 * This file is a stub version of the interface for a
 * garbage-collecting allocator that will be part of
 * a future library release.  When the garbage-collecting
 * allocator is in use, the memory returned by the GetBlock
 * and FreeBlock functions in genlib.h can be traced and
 * collected automatically when it is no longer accessible.
 *
 * The garbage-collecting allocator is not part of the
 * current cslib distribution.  Even so, functions in the
 * other libraries call the ProtectVariable and ProtectBlock
 * functions, so that they will continue to work when the
 * full library is released.  Those functions are implemented
 * in genlib.c.
 */

#ifndef _gcalloc_h
#define _gcalloc_h

/*
 * Macro: ProtectVariable
 * Usage: ProtectVariable(v);
 * --------------------------
 * This macro registers a global variable with the allocation
 * system, so that the variable is traced when the garbage
 * collector is used.  This operation needs is implemented
 * in genlib.c so that code can be written to function correctly
 * whether or not the garbage-collecting allocator is loaded.
 */

#define ProtectVariable(v) ProtectBlock(&v, sizeof v)

/*
 * Function: ProtectBlock
 * Usage: ProtectBlock(ptr, nbytes);
 * ---------------------------------
 * This function is not usually called by clients (who will
 * ordinarily use ProtectVariable instead), but has the
 * effect of protecting the block of memory beginning at
 * ptr and extending for nbytes from the garbage collector.
 */

void ProtectBlock(void *ptr, size_t nbytes);

/*
 * Global linkage variable: _acb
 * -----------------------------
 * This variable is used to hold the allocation control block
 * that provides the linkage between this package and the
 * dynamic allocator.  The reason for using the structure
 * as a linkage is so that the garbage-collecting allocator
 * need not even be loaded if it is not explicitly called.
 */

typedef struct {
    void *(*allocMethod)(size_t nbytes);
    void (*freeMethod)(void *ptr);
    void (*protectMethod)(void *ptr, size_t nbytes);
} *_GCControlBlock;

extern _GCControlBlock _acb;

#endif
