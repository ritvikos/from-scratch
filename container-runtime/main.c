// TODO: Cgroups
// TODO: Networking

// DONE:
// - Namespace

#define _GNU_SOURCE
#include <limits.h>
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <unistd.h>

#include "test.h"

#define STACK_SIZE (1024 * 1024)

static int child(void *arg) {
  // set hostname
  sethostname(HOSTNAME, HOSTNAME_SIZE);

  print_child_cfg();
  return 0;
}

// Basically Container:
// - Run the command in spawned process.
// - Isolate the process from the system.
int run(int argc, char *args[]) {
  char *stack = malloc(STACK_SIZE);
  char *top = stack + STACK_SIZE;

  if (stack == NULL) {
    fprintf(stderr, "Error: Memory Allocation!");
    free(stack);
    exit(EXIT_FAILURE);
  }

  pid_t cpid = clone(child, top,
                     CLONE_NEWUTS | CLONE_NEWPID | CLONE_NEWNS | CLONE_NEWUSER |
                         CLONE_NEWIPC | SIGCHLD,
                     NULL);

  if (cpid == -1) {
    fprintf(stderr, "Error: Process Creation!");
    free(stack);
    exit(EXIT_FAILURE);
  }

  if (waitpid(cpid, NULL, 0) == -1) {
    fprintf(stderr, "Error: waitpid() failed!");
    free(stack);
    exit(EXIT_FAILURE);
  }

  return 0;
}

typedef struct {
  const char *command;
  int (*fn)(int argc, char *args[]);
} Command;

Command lookup_table[] = {
    {"run", run},
};

int main(int argc, char *argv[]) {
  for (size_t i = 0; lookup_table[i].command != NULL; i++) {
    if (strcmp(argv[1], lookup_table[i].command) == 0) {
      lookup_table[i].fn(argc, argv);
      break;
    } else {
      fprintf(stderr, "Unsupported Command!");
      exit(EXIT_FAILURE);
    }
  }

  return EXIT_SUCCESS;
}
