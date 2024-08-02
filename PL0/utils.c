#include "includes/utils.h"
#include <stdlib.h>
#include <string.h>

char *strndupCustom(const char *str, size_t n) {
  if (!str) {
    return NULL; // Handle NULL input
  }

  size_t len = strnlen(str, n);
  char *copy = (char *)malloc(len + 1);
  if (copy) {
    memcpy(copy, str, len);
    copy[len] = '\0';
  }
  return copy;
}
