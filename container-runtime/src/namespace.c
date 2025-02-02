#define _GNU_SOURCE

#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "namespace.h"

int namespace_create() {
  int flags =
      CLONE_NEWUTS | CLONE_NEWPID | CLONE_NEWNS | CLONE_NEWUSER | CLONE_NEWIPC;

  if (unshare(flags) == -1) {
    fprintf(stderr, "Unshare failed!");
    return -1;
  }

  return 0;
}
