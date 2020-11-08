#include <types.h>
#include <lib.h>
#include <kern/errno.h>
#include <machine/spl.h>
#include <machine/pcb.h>
#include <thread.h>
#include <curthread.h>
#include <thread.h>
#include <curthread.h>
#include <scheduler.h>
#include <array.h>
#include <pid.h>
#include <pidarray.h>

int pidArray[512];
int first = 0;

int sys_getpid(int32_t *retval) {
	int i, g, flag = 0;
	int returnPid;
	
	if(first == 0) {
		first++;
		for(i=0;i<512;i++) {
			pidArray[i] = 0;
		}
	}
	
	for(i=0;i<512;i++) {
		if(pidArray[i] == 0) {
			returnPid = i+1;
			pidArray[i] = 1;
			break;
		}
		
		if(pidArray[i] == 1) {
			for(g = 0; g < numthreads; g++) {
				if(*(threads[g].interested_pid) == i+1) {
					flag = 1;
				}
			}
			if(!flag){
				pidArray[i] = 0;
			}
		}
	}

	*retval = 0;
	return returnPid;
}

