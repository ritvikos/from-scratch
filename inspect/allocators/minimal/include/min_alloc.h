#ifndef MIN_ALLOC_H
#define MIN_ALLOC_H
#include <stdio.h>

typedef char ALIGN[16];

union header {
  struct {
    size_t size;
    unsigned is_free;
    union header *next;
  } s;
  ALIGN stub;
} typedef header_t;

void *min_alloc(size_t size);
void *min_free(void *block);

#endif
