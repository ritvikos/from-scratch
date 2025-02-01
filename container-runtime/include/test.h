#ifndef TEST_H
#define TEST_H

#define HOSTNAME "container"
#define HOSTNAME_SIZE HOST_NAME_MAX

void test_fs_cfg();
void test_proc_cfg();
void test_user_cfg();
void test_sys_cfg();
void print_container_config();

#endif
