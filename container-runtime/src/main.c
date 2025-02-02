// Subsystems:
// - process launcher
// - namespace
// - cgroup
// - fs
// - seccomp
// - container controller
// - process reaper
// - snapshot

// Non Targets:
// - Adhere to OCI-rt spec
// - networking

#define _GNU_SOURCE

#include <stdio.h>

#include "container.h"
#include "process.h"
#include "test.h"

int main(int argc, char *argv[]) {
  struct container container = {.hostname = "minimal-container",
                                .proc = {.pid = 0, .argv = argv, .argc = argc}};

  printf("hostname: %s\n", container.hostname);
  printf("0: %s\n", container.proc.argv[0]);
  printf("1: %s\n", container.proc.argv[1]);
  printf("2: %s\n", container.proc.argv[2]);

  container_create(&container);

  return 0;
}
