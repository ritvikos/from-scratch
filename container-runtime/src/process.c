#define _GNU_SOURCE
#define STACK_SIZE (1024 * 1024)

#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../include/process.h"

int process_create(struct container_process *proc, int (*child)(void *),
		   void *container)
{
	proc->stack = mmap(NULL, STACK_SIZE, PROT_READ | PROT_WRITE,
			   MAP_PRIVATE | MAP_ANONYMOUS | MAP_GROWSDOWN, -1, 0);

	if (!proc->stack) {
		fprintf(stderr, "Error: Stack Allocation!\n");
		return -1;
	}

	proc->pid = clone(child, proc->stack + STACK_SIZE - sizeof(void *),
			  SIGCHLD, container);

	if (proc->pid == -1) {
		fprintf(stderr, "Error: Process Creation!");
		munmap(proc->stack, STACK_SIZE);
		return -1;
	}

	return 0;
}

int process_wait(pid_t pid)
{
	if (waitpid(pid, NULL, 0) == -1) {
		fprintf(stderr, "Error: Process Wait!");
		return -1;
	}

	return 0;
}
