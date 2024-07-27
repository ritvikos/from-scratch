#include "file.c"
#include "lex.c"
#include "lex.h"
#include "token.c"
#include "token.h"
#include <stdio.h>

// PL/0 Compiler from scratch in C
int main(int argc, char **argv) {

  if (argv[1] == NULL) {
    perror("No file provided");
    return 1;
  }

  const char *raw = readFile(argv[1]);
  if (raw == NULL) {
    return 1;
  }

  Lexer lexer;
  initLexer(&lexer, raw);

  Token token;
  do {
    token = getNextToken(&lexer);
    printf("type: %d, Lexeme: %s \n", token.type, token.lexeme);
    freeToken(&token);
  } while (token.type != TOKEN_EOF);

  freeLexer(&lexer);
  return 0;
}
