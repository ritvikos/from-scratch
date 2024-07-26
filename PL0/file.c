#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *fileExtension = ".pl0";

// Must be ".pl0" or ".p0" file
bool validFileName(const char *fileName) {
  const int len = strlen(fileName);

  if (len < 5) {
    perror("Error: Invalid File Name\n");
    return false;
  }

  if (strcmp(&fileName[len - 4], fileExtension)) {
    perror("Error: File name must end with .pl0 extension\n");
    return false;
  }

  return true;
}

char *readFileToBuffer(FILE **stream) {
  fseek(*stream, 0, SEEK_END);
  size_t size = ftell(*stream);
  rewind(*stream);

  char *buffer = (char *)malloc(size + 1);
  if (buffer == NULL) {
    perror("Error: Memory allocation failed!");
    return NULL;
  }

  size_t bytesRead = fread(buffer, 1, size, *stream);
  if (bytesRead != size) {
    perror("Error reading file");
    free(buffer);
    return NULL;
  }

  buffer[size] = '\0';
  return buffer;
}

char *readFile(const char *fileName) {
  if (!validFileName(fileName)) {
    return NULL;
  }

  FILE *stream;
  char *buffer = NULL;

  if (fopen_s(&stream, fileName, "rb") == 0) {
    buffer = readFileToBuffer(&stream);
  } else {
    perror("File doesn't exist");
    return false;
  }

  return buffer;
}
