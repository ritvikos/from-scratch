#ifndef CONTAINER_H
#define CONTAINER_H

#include "namespace.h"
#include "process.h"

struct container {
  char *hostname;
  struct container_process proc;
};

int container_create(struct container *container);

#endif
