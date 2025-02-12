#define _GNU_SOURCE

#include <sched.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/namespace.h"

int namespace_create()
{
	int flags = CLONE_NEWUTS | CLONE_NEWPID | CLONE_NEWNS | CLONE_NEWIPC |
		    CLONE_NEWCGROUP;

	if (unshare(flags) == -1) {
		fprintf(stderr, "Unshare failed!");
		return -1;
	}

	return 0;
}

int namespace_flags()
{
	return CLONE_NEWUTS | CLONE_NEWPID | CLONE_NEWNS | CLONE_NEWIPC |
	       CLONE_NEWCGROUP;
}
