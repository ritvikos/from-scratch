#ifndef LEX_H
#define LEX_H

#define MAX_LEXEME_LENGTH 64

#include "token.h"

typedef struct {
  const char *raw;
  size_t length;
  size_t line;
  size_t index;
} Lexer;

void initLexer(Lexer *lexer, const char *raw);
void freeLexer(Lexer *lexer);

Token getNextToken(Lexer *lexer);

char advance(Lexer *lexer);
char retract(Lexer *lexer);
char peek(Lexer *lexer);

#endif
