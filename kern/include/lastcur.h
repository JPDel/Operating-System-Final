#ifndef _LASTCUR_H_
#define _LASTCUR_H_

/*
 * The current thread.
 *
 * This is in its own header file (instead of thread.h) to reduce the
 * number of things that get recompiled when you change thread.h.
 */

struct thread;

extern struct thread *lastcur;

#endif /* _LASTCUR_H_ */
