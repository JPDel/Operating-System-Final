#include <types.h>
#include <lib.h>
#include <kern/errno.h>
#include <thread.h>
#include <array.h>
#include <synch.h>
#include <curthread.h>
#include <pid.h>


pid_t sys_waitpid(int pid, int *status,  int options, int32_t *ret) {
	
	
	if(pid < -1) { // Our pid is treated as its absolute value if it is below -1
		pid *= -1;
	}
	
	if(options != 0) {
		*ret = EINVAL;
		return -1;
	} 
	
	if(status == NULL) {
		*ret = EFAULT;
		return -1;
	}
	
	//struct thread waiting;
	
	*(curthread->interested_pid) = pid;
	
	//waiting = findthread(pid);

	/*if((options|WNOHANG) == options) {
		*status = waiting->code;
		return pid;
	}*/
	
	P(findthread(pid).sem);
	V(findthread(pid).sem);
	
	// check to see if any other threads are interested in the pid

	*status = (findthread(pid).code);
	
	return pid;
}
