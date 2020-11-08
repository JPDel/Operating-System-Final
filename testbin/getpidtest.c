#include "getpid.c"

void main(){
	pid_t pid1, pid2, pid3;
	pid1 = getPid();
	pid2 = getPid();
	pid3 = getPid();
	kprintf("%d\n", pid1);
	kprintf("%d\n", pid2);
	kprintf("%d\n", pid3);

}
