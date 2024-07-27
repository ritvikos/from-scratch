#include "lookup.h"
#include "ctype.h"
#include "lex.h"
#include "token.h"
#include "utils.c"

Token lookupKeywordIdentifier(Lexer *lexer) {
  size_t start = lexer->index - 1;
  while (isalnum(peek(lexer)))
    advance(lexer);

  size_t length = lexer->index - start;
  char *lexeme = strndupCustom(lexer->raw + start, length);

  for (size_t i = 0; i < keywordTableLen; i++) {
    if (strcmp(lexeme, keywordTable[i].lexeme) == 0) {
      return createToken(keywordTable[i].type, lexeme);
    }
  }
  return createToken(TOKEN_IDENTIFIER, lexeme);
}

Token lookupNumber(Lexer *lexer) {
  size_t start = lexer->index - 1;
  while (isdigit(peek(lexer)))
    advance(lexer);

  size_t length = lexer->index - start;
  char *lexeme = strndupCustom(lexer->raw, length);
  return createToken(TOKEN_NUMBER, lexeme);
}

// -- Symbol Helper Functions -- //
Token handleLessThan(Lexer *lexer) {
  if (peek(lexer) == '=') {
    advance(lexer);
    return createToken(TOKEN_LESS_EQUAL, "<=");
  }
  return createToken(TOKEN_LESS, "<");
}

Token handleGreaterThan(Lexer *lexer) {
  if (peek(lexer) == '=') {
    advance(lexer);
    return createToken(TOKEN_GREATER_EQUAL, ">=");
  }
  return createToken(TOKEN_GREATER, ">");
}

Token handleColon(Lexer *lexer) {
  if (peek(lexer) == '=') {
    advance(lexer);
    return createToken(TOKEN_ASSIGN, ":=");
  }
  return createToken(TOKEN_INVALID, "unexpected token after ':'");
}

Token lookupSymbol(Lexer *lexer, char ch) {
  for (size_t i = 0; i < sizeof(symTable) / sizeof(symTable[0]); i++) {
    if (ch == symTable[i].ch) {
      if (ch == '<')
        return handleLessThan(lexer);
      if (ch == '>')
        return handleGreaterThan(lexer);
      if (ch == ':')
        return handleColon(lexer);
      return createToken(symTable[i].type, &symTable[i].ch);
    }
  }
  return createToken(TOKEN_INVALID, "INVALID_TOKEN");
}
