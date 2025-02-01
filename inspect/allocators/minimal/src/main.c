#include "../include/min_alloc.h"
#include <stdio.h>

int main() {
  printf("init");
  puts("");

  size_t size = 1024;
  header_t *loc = min_alloc(size);

  printf("loc: %p", &loc);
  puts("");

  return 0;
}
