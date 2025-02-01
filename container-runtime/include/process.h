#ifndef PROCESS_H
#define PROCESS_H

#include <sys/types.h>

struct container_process {
  pid_t pid;
  int argc;
  char **argv;
  char **envp;
  char *stack;
};

int process_create(struct container_process *proc, int(*child)(void*), void *container);
int process_wait(pid_t pid);

#endif
