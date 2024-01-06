#ifndef MIN_ALLOC_H
#define MIN_ALLOC_H

/*
    Structure: header_t

    Description:
    This structure represents a header for managing memory blocks in a custom
   memory allocation system. It includes essential information about the
   allocated memory block, such as its size, allocation status, and a pointer to
   the next block.

    Members:
    - size_t size: The size, in bytes, of the memory block.
    - unsigned is_free: A flag indicating whether the memory block is free (1)
   or allocated (0).
    - struct header_t *next: A pointer to the next memory block in the linked
   list.

    Usage:
    - This structure is typically used in conjunction with memory allocation
   functions to keep track of allocated memory blocks.
*/
struct header_t {
  size_t size;
  unsigned is_free;
  struct header_t *next;
} typedef header_t;

/*
    Function: void *min_alloc(size_t size);

    Description:
    This function is responsible for [replace with a concise description of the
   functionality]. It allocates a block of memory of the specified size and
   returns a void pointer to the beginning of the allocated memory.

    Parameters:
    - size_t size: The size, in bytes, of the memory block to be allocated.

    Return:
    - void *: A pointer to the beginning of the allocated memory block.
*/
void *min_alloc(size_t size);

/*
    Function: void *min_free(void *block);

    Description:
    This function is designed to perform [replace with a concise description of
   the functionality]. It takes a pointer to a block in memory as its parameter
   and returns a void pointer.

    Parameters:
    - void *block: A pointer to the memory block.

    Return:
    - void *: A pointer to [replace with the specific type or purpose of the
   result].
*/
void *min_free(void *block);

#endif
