#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>

#include "test.h"

void test_fs_cfg() {
  if (mkdir("/mnt/testfs", 0755) == -1) {
    fprintf(stderr, "Error: Mkdir!\nProbably permissions! Run as 'root'");
    return;
  }

  if (mount("tmpfs", "/mnt/testfs", "tmpfs", 0, "") == -1) {
    fprintf(stderr, "Error: Mount!\n.");
    return;
  }

  system("mount | grep /mnt/testfs");

  umount("/mnt/testfs");
  rmdir("/mnt/testfs");
}

void test_proc_cfg() {
  system("ps -o pid,comm");
}

void test_user_cfg() {
  printf("UID: %d\n", getuid());
  printf("GID: %d\n", getgid());
}

void test_sys_cfg() {
  char hostname[HOSTNAME_SIZE];

  if (gethostname(hostname, sizeof(hostname)) != 0) {
    fprintf(stderr, "Error: gethostname() failed!");
    return;
  }

  printf("Hostname: %s\n", hostname);
  printf("PID: %ld\n", (long)getpid());
}

void print_child_cfg() {
  printf("\n-- SYS --\n");
  test_sys_cfg();

  printf("\n-- FS --\n");
  test_fs_cfg();

  printf("\n-- PROC --\n");
  test_proc_cfg();

  printf("\n-- USER NS --\n");
  test_user_cfg();
}
