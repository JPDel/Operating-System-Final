#ifndef _PIDARRAY_H_
#define _PIDARRAY_H_

/*
 * The current thread.
 *
 * This is in its own header file (instead of thread.h) to reduce the
 * number of things that get recompiled when you change thread.h.
 */


int pidArray[512];

#endif /* _PIDARRAY_H_ */
