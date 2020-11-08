#include <types.h>
#include <lib.h>
#include <kern/errno.h>
#include <machine/spl.h>
#include <machine/pcb.h>
#include <thread.h>
#include <curthread.h>
#include <scheduler.h>
#include <array.h>
#include <pidarray.h>

void sys_exit(int num){
	int i, flag = 0;

	curthread->code = num;
	
	for(i = 0; i < numthreads; i++) {
		if(threads[i].interested_pid == curthread->pid) {
			flag = 1;
			break;
		}
	}
	if(!flag) {
		pidArray[((int)((curthread->pid)-1))] = 0;
		curthread->pid = NULL;
	}
	
        thread_exit();

}
