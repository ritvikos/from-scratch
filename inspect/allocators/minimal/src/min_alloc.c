#include "../include/min_alloc.h"
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>

#elif __linux__
#include <unistd.h>

#endif

header_t *head, *tail;

header_t *first_fit(size_t size) {
  // create a pointer for iteration.
  header_t *current = head;

  // Iterate.
  while (current) {
    // - Current block is free and
    // - Current block's size >= required_size (size)
    if (current->s.is_free && current->s.size >= size)
      return current;

    // Move next.
    current = current->s.next;
  }

  return NULL;
}

void *min_alloc(size_t size) {
  // Ensure "NULL" is returned for zero size.
  if (!size)
    return NULL;

  // Get Free Block.
  header_t *header = first_fit(size);

  // If block is found,
  if (header) {
    // set the block to 0, which states that it's not free.
    header->s.is_free = 0;

    // Return (header + 1), as it excludes the address for
    // the header block (basically, hiding the header from the caller).
    return (void *)(header + 1);
  }

  // Total Size = Size of header + Size to allocate.
  size_t total_size = sizeof(header_t) + size;

// Sufficiently large-sized block is not found, so extend the heap.
// Allocate space for block via syscall, if not left.
#ifdef __linux__
  void *block;
  block = sbrk(total_size);

  // // If OOM
  if (block == (void *)-1) {
    return NULL;
  }

#elif _WIN32
  LPVOID block =
      VirtualAlloc(NULL, total_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

  if (block == NULL) {
    perror("VirtualAlloc");
    return NULL;
  }

#else
  perror("error: Unsupported OS");
  exit()

#endif

  // Now, we obtained the memory from the OS.
  // Make space for header.
  header = block;

  // Set the header size.
  header->s.size = size;

  // Mark it NOT Free.
  header->s.is_free = 0;

  // Set next header to NULL.
  header->s.next = NULL;

  if (!head)
    head = header;
  if (tail)
    tail->s.next = header;

  tail = header;

  // Return (header + 1), as it excludes the address for
  // the header block (basically, hiding the header from the caller).
  return (void *)(header + 1);
}
