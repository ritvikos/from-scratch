#ifndef NAMESPACE_H
#define NAMESPACE_H

struct container_ns {
  int uts_ns;
  int pid_ns;
  int mnt_ns;
  int user_ns;
  int ipc_ns;
};

int namespace_create();

#endif
