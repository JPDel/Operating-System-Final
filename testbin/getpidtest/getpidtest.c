#include <sys/types.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <err.h>

void main(){
	pid_t pid1, pid2, pid3;
	pid1 = sys_getpid();
	pid2 = sys_getpid();
	pid3 = sys_getpid();
	kprintf("%d\n", pid1);
	kprintf("%d\n", pid2);
	kprintf("%d\n", pid3);

}
