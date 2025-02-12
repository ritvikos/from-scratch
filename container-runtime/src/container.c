#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/container.h"
#include "../include/process.h"

int init(void *c)
{
	struct container *container = (struct container *)c;

	if (sethostname(container->hostname, strlen(container->hostname)) < 0) {
		fprintf(stderr, "Error: Set Hostname!");
		return -1;
	}

	char **args = container->proc.argv;
	if (args == NULL || args[0] == NULL) {
		fprintf(stderr, "Error: No command passed");
		return -1;
	}

	execvp("/bin/bash", container->proc.argv);
	fprintf(stderr, "Error: Execvp failed!");

	return -1;
}

int container_create(struct container *container)
{
	struct container_process *proc = &container->proc;

	if (process_create(proc, init, container) < 0) {
		return -1;
	}

	if (process_wait(proc->pid) < 0) {
		return -1;
	}

	return 0;
}
