#include "includes/lex.h"
#include "lookup.c"
#include "includes/token.h"
#include <corecrt.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void initLexer(Lexer *lexer, const char *raw) {
  lexer->raw = raw;
  lexer->length = strlen(raw);
  lexer->line = 1;
  lexer->index = 0;
}

void freeLexer(Lexer *lexer) { free(lexer); }

char advance(Lexer *lexer) {
  char ch = peek(lexer);
  lexer->index++;

  if (strcmp(&ch, "\n") == 0) {
    lexer->line++;
  }

  return ch;
}

char retract(Lexer *lexer) { return lexer->raw[lexer->index--]; }

char peek(Lexer *lexer) {
  if (lexer->index >= lexer->length)
    return '\0';
  return lexer->raw[lexer->index];
}

void skipWhitespace(Lexer *lexer) {
  while (isspace(peek(lexer)))
    advance(lexer);
}

Token getNextToken(Lexer *lexer) {
  skipWhitespace(lexer);

  char ch = advance(lexer);

  if (isalpha(ch))
    return lookupKeywordIdentifier(lexer);
  if (isdigit(ch))
    return lookupNumber(lexer);
  Token token = lookupSymbol(lexer, ch);
  if (token.type != TOKEN_INVALID) {
    return token;
  }

  if (ch == '\0')
    return createToken(TOKEN_EOF, "EOF");

  return createToken(TOKEN_INVALID, "INVALID_TOKEN");
}
