#include <stdio.h>
#include "file.c"

// PL/0 Compiler from scratch in C
int main(int argc, char **argv) {

    if (argv[1] == NULL) {
        perror("No file provided");
        return 1;
    }

    char *raw = readFile(argv[1]);
    if ( raw == NULL) {
        return 1;
    }

    printf("%s", raw);

    return 0;
}
