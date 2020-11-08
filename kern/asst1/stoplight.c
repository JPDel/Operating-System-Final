/* 
 * stoplight.c
 *
 * 31-1-2003 : GWA : Stub functions created for CS161 Asst1.
 *
 * NB: You can use any synchronization primitives available to solve
 * the stoplight problem in this file.
 */


/*
 * 
 * Includes
 *
 */

#include <types.h>
#include <lib.h>
#include <test.h>
#include <thread.h>
#include <synch.h>
// sum is used to count number of cars that have passed the intersection
int sum = 0;
// the first 4 locks are the intersection locks, and the next four locks reperesent whos at the front of the line in each lane, and the finisher lock is used for synchnronization so the program does not end until all threads have left
struct lock *northwest, *northeast, *southwest, *southeast, *north, *south, *east, *west, *finisher;
/*
 *
 * Constants
 *
 */

/*
 * Number of cars created.
 */

#define NCARS 20


/*
 *
 * Function Definitions
 *
 */
// prints message when cars are appraoching intersection
static void printApproach(unsigned long carNumber, unsigned long carDirection, int carDestination, int turn){
	char cardinalDirection[] = {'N', 'E', 'S', 'W'};
	char turnDirection[] = {'L', 'S', 'R'};
	kprintf("Car number %lu approaching from %c and wants to go %c towards %c\n", carNumber, cardinalDirection[carDirection], turnDirection[turn], cardinalDirection[carDestination]);
}
// prints message when cars are entering intersection
static void printEnter(unsigned long carNumber, unsigned long carDirection, int carDestination, int turn){
	char cardinalDirection[] = {'N', 'E', 'S', 'W'};
	char turnDirection[] = {'L', 'S', 'R'};
	kprintf("Car number %lu entering the intersection from %c and is going %c towards %c\n", carNumber, cardinalDirection[carDirection], turnDirection[turn], cardinalDirection[carDestination]);
}
// prints message when cars are leaving intersection
static void printLeave(unsigned long carNumber, unsigned long carDirection, int carDestination, int turn){
	char cardinalDirection[] = {'N', 'E', 'S', 'W'};
	char turnDirection[] = {'L', 'S', 'R'};
	kprintf("Car number %lu has gone %c from %c and is traveling %c\n", carNumber, turnDirection[turn], cardinalDirection[carDirection], cardinalDirection[carDestination]);
}



/*
 * gostraight()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement passing straight through the
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
gostraight(unsigned long cardirection,
           unsigned long carnumber)
{
        /*
         * Avoid unused variable warnings.
         */
        
        (void) cardirection;
        (void) carnumber;


	if(cardirection == 0){ // arriving from the north
		 printApproach(carnumber, cardirection, 2, 1);
        	 lock_acquire(southwest);
        	 lock_acquire(northwest);
        	 printEnter(carnumber, cardirection, 2, 1);
        	 lock_release(northwest);
        	 lock_release(southwest);
        	 printLeave(carnumber, cardirection, 2, 1);
	}
	
	else  if(cardirection == 1){ // arriving from the east

		printApproach(carnumber, cardirection, 3,1 );
        	lock_acquire(northwest);
        	lock_acquire(northeast);
        	printEnter(carnumber, cardirection, 3, 1);
        	lock_release(northeast);
        	lock_release(northwest);
        	printLeave(carnumber, cardirection, 3, 1);
        }
	
	else  if(cardirection == 2){ // arriving from the south

		printApproach(carnumber, cardirection, 0 , 1);
        	lock_acquire(northeast);
        	lock_acquire(southeast);
        	printEnter(carnumber, cardirection, 0, 1);
        	lock_release(southeast);
        	lock_release(northeast);
        	printLeave(carnumber, cardirection, 0, 1);
        }

	 else{// arriving from the west

		printApproach(carnumber, cardirection, 1, 1);
        	lock_acquire(southeast);
        	lock_acquire(southwest);
        	printEnter(carnumber, cardirection, 1, 1);
        	lock_release(southwest);
        	lock_release(southeast);
        	printLeave(carnumber, cardirection, 1, 1);
        }

}


/*
 * turnleft()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement making a left turn through the 
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
turnleft(unsigned long cardirection,
         unsigned long carnumber)
{
        /*
         * Avoid unused variable warnings.
         */
	

        (void) cardirection;
        (void) carnumber;

	if(cardirection == 0){// arriving from the north

		printApproach(carnumber, cardirection, 1, 0);
        	lock_acquire(southeast);
        	lock_acquire(southwest);
        	lock_acquire(northwest);
        	printEnter(carnumber, cardirection, 1, 0);
        	lock_release(northwest);
        	lock_release(southwest);
        	lock_release(southeast);
        	printLeave(carnumber, cardirection, 1, 0);
	}

	else if(cardirection == 1){//arriving from the east

		printApproach(carnumber, cardirection, 2, 0);
        	lock_acquire(southwest);
        	lock_acquire(northwest);
        	lock_acquire(northeast);
        	printEnter(carnumber, cardirection, 2, 0);
        	lock_release(northeast);
        	lock_release(northwest);
        	lock_release(southwest);
        	printLeave(carnumber, cardirection, 2, 0);
        }

	else if(cardirection == 2){// arriving from south
	
		printApproach(carnumber, cardirection, 3, 0);
        	lock_acquire(northwest);
        	lock_acquire(northeast);
        	lock_acquire(southeast);
        	printEnter(carnumber, cardirection, 3, 0);
        	lock_release(southeast);
        	lock_release(northeast);
        	lock_release(northwest);
        	printLeave(carnumber, cardirection, 3, 0);
 
        }

	else{// arriving from west

		printApproach(carnumber, cardirection, 0,0);
       	 	lock_acquire(northeast);
        	lock_acquire(southeast);
        	lock_acquire(southwest);
        	printEnter(carnumber, cardirection, 0,0);
        	lock_release(southwest);
        	lock_release(southeast);
        	lock_release(northeast);
        	printLeave(carnumber, cardirection, 0,0);
        }


}


/*
 * turnright()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement making a right turn through the 
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
turnright(unsigned long cardirection,
          unsigned long carnumber)
{
        /*
         * Avoid unused variable warnings.
         */

        (void) cardirection;
        (void) carnumber;

	if(cardirection == 0){//arriving from north
		printApproach(carnumber, cardirection, 3,2);
		lock_acquire(northwest);
		printEnter(carnumber, cardirection, 3,2);
		lock_release(northwest);
		printLeave(carnumber, cardirection, 3,2);
	}

      else if(cardirection == 1){//arriving from east
		printApproach(carnumber, cardirection, 0,2);
                lock_acquire(northeast);
		printEnter(carnumber, cardirection, 0,2);
                lock_release(northeast);
		printLeave(carnumber, cardirection, 0,2);
        }

      else if(cardirection == 2){// arriving from south
		printApproach(carnumber, cardirection, 1,2);
                lock_acquire(southeast);
		printEnter(carnumber, cardirection, 1,2);
                lock_release(southeast);
		printLeave(carnumber, cardirection, 1,2);

        }

	else{// arriving from west
		printApproach(carnumber, cardirection, 2,2);
                lock_acquire(southwest);
		printEnter(carnumber, cardirection, 2,2);
                lock_release(southwest);
		printLeave(carnumber, cardirection, 2,2);
        }

}


/*
 * approachintersection()
 *
 * Arguments: 
 *      void * unusedpointer: currently unused.
 *      unsigned long carnumber: holds car id number.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      Change this function as necessary to implement your solution. These
 *      threads are created by createcars().  Each one must choose a direction
 *      randomly, approach the intersection, choose a turn randomly, and then
 *      complete that turn.  The code to choose a direction randomly is
 *      provided, the rest is left to you to implement.  Making a turn
 *      or going straight should be done by calling one of the functions
 *      above.
 */
 
static
void
approachintersection(void * unusedpointer,
                     unsigned long carnumber)
{
        int cardirection;
	int carDest;
        /*
         * Avoid unused variable and function warnings.
         */

        (void) unusedpointer;
        (void) carnumber;
	(void) gostraight;
	(void) turnleft;
	(void) turnright;

        /*
         * cardirection is set randomly.
         */

        cardirection = random() % 4;
	carDest = random() % 3;

	if(carnumber == 0){
        	lock_acquire(finisher);
    	}
    	else {
        	lock_pass(finisher);
    	}

/*
	if(carDest == 0){
		if(cardirection == 0){ //Arriving from North
			printApproach(carnumber, cardirection, 1);
		}
		else if(cardirection == 1){ //Arriving from East
			printApproach(carnumber, cardirection, 2);
		}
		else if(cardirection == 2){ //Arriving from South
			printApproach(carnumber, cardirection, 3);

		}
		else{ //Arriving from West
			printApproach(carnumber, cardirection, 0);
		}
	}
	else if(carDest == 1){
		if(cardirection == 0){ //Arriving from North
			printApproach(carnumber, cardirection, 2);
		}
		else if(cardirection == 1){ //Arriving from East
			printApproach(carnumber, cardirection, 3);
		}
		else if(cardirection == 2){ //Arriving from South
			printApproach(carnumber, cardirection, 0);
		}
		else{ //Arriving from West
			printApproach(carnumber, cardirection, 1);
		}
	}
	else{
		if(cardirection == 0){ //Arriving from North
			printApproach(carnumber, cardirection, 3);
		}
		else if(cardirection == 1){
			printApproach(carnumber, cardirection, 0);
		}
		else if(cardirection == 2){
			printApproach(carnumber, cardirection, 1);
		}
		else{
			printApproach(carnumber, cardirection, 2);
		}
	}
*/	


// this is where the lock acquiring for whoever is first in their direction acquires lock

	if(cardirection == 0){
        	lock_acquire(north);
    	}
    	else if(cardirection == 1){
        	lock_acquire(east);
    	}
    	else if(cardirection == 2){
        	lock_acquire(south);
    	}
    	else{
        	lock_acquire(west);
    	}


	if(carDest == 0){
		turnleft(cardirection, carnumber);
	}
	else if(carDest == 1){
		gostraight(cardirection, carnumber);
	}
	else{
		turnright(cardirection, carnumber);
	}

	if(cardirection == 0){
        	lock_release(north);
    	}
    	else if(cardirection == 1){
        	lock_release(east);
    	}
    	else if(cardirection == 2){
        	lock_release(south);
    	}
    	else{
        	lock_release(west);
    	}
	
	sum++;
	if(sum == NCARS){
		lock_pass(finisher);
        	lock_release(finisher);
    	}	
}


/*
 * createcars()
 *
 * Arguments:
 *      int nargs: unused.
 *      char ** args: unused.
 *
 * Returns:
 *      0 on success.
 *
 * Notes:
 *      Driver code to start up the approachintersection() threads.  You are
 *      free to modiy this code as necessary for your solution.
 */

int
createcars(int nargs,
           char ** args)
{
        int index, error;

        /*
         * Avoid unused variable warnings.
         */

        (void) nargs;
        (void) args;

	
        /*
         * Start NCARS approachintersection() threads.
         */
	
	northwest = lock_create("northwest");
	northeast = lock_create("northeast");
	southwest = lock_create("southwest");
	southeast = lock_create("southeast");

	north = lock_create("north");
	east = lock_create("east");
	west = lock_create("west");
	south = lock_create("south");

	finisher = lock_create("finisher");

	
        for (index = 0; index < NCARS; index++) {

                error = thread_fork("approachintersection thread",
                                    NULL,
                                    index,
                                    approachintersection,
                                    NULL
                                    );
//		kprintf("print the index number for threads: %d\n", index);

                /*
                 * panic() on error.
                 */

                if (error) {
                        
                        panic("approachintersection: thread_fork failed: %s\n",
                              strerror(error)
                              );
                }
        }
//	thread_yield();
	lock_acquire(finisher);
	 kprintf("all cars have left the intersection\n");
	lock_release(finisher);
//	kprintf("all cars have left the intersection\n");
	lock_destroy(northwest);
        lock_destroy(northeast);
        lock_destroy(southwest);
        lock_destroy(southeast);
        lock_destroy(north);
        lock_destroy(south);
        lock_destroy(east);
        lock_destroy(west);
        lock_destroy(finisher);
	sum = 0;
        return 0;

}
