#ifndef _SYSCALL_H_
#define _SYSCALL_H_

/*
 * Prototypes for IN-KERNEL entry points for system call implementations.
 */

int sys_reboot(int code);
int sys_getpid(int32_t *ret);
int sys_waitpid(int pid, int *status, int options, int32_t *ret);
void sys_exit(int status);
int sys_fork(int32_t *ret, void *data1);
//int sys_execv(const char *path, char *const argv[]);

#endif /* _SYSCALL_H_ */
