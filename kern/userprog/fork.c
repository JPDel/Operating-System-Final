#include <types.h>
#include <thread.h>
#include <syscall.h>
#include <machine/trapframe.h>
#include <curthread.h>
#include <kern/errno.h>
#include <addrspace.h>
#include <lib.h>
#include <pid.h>
#include <lastcur.h>
#include <machine/spl.h>

int sys_fork(int32_t *retval, void *data1) { //parent trapframe is passed in, find address space in current thread->address space
	
	struct thread *memcheck;
	int err;
	struct trapframe parenttrapframe;
	struct thread *child;
	

	memcheck = kmalloc(sizeof(struct thread));
	
	if(memcheck == NULL) {
		return ENOMEM;
	}
	
	kfree(memcheck);

	if(numthreads == 512) {
		return EAGAIN;
	}
	
	int temp = splhigh();
	memcpy(&parenttrapframe, data1, sizeof(struct trapframe));
//	memcpy(&parentspace, curthread->t_vmspace, sizeof(struct addrspace);
	splx(temp);
	
	err = thread_fork("Child process", (void*)&parenttrapframe, 0, md_forkentry, &child);
	
	*retval = *(curthread->child_pid); //Sorry
		
	return err;
}
