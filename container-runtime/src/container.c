#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "container.h"
#include "process.h"
#include "test.h"

int child_proc(void *arg) {
  struct container *container = (struct container *)arg;

  if (sethostname(container->hostname, strlen(container->hostname)) < 0) {
    fprintf(stderr, "Error: Set Hostname!");
    return -1;
  }

  char **args = container->proc.argv;
  if (args == NULL || args[0] == NULL) {
    fprintf(stderr, "Error: No command passed");
    return -1;
  }

  printf("o: %s", args[0]);
  // execvp()

  return 0;
}

int container_create(struct container *container) {
  struct container_process *proc = &container->proc;

  if (process_create(proc, child_proc, container) < 0) {
    return -1;
  }

  if (proc->pid == 0) {
    if (namespace_create() < 0) {
      return -1;
    }

    if (execvp("/bin/bash", proc->argv)) {
      fprintf(stderr, "Error: Execvp failed!");
      return -1;
    }
  }

  return 0;
}
