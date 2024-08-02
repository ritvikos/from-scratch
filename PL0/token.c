#include "includes/token.h"
#include <stdlib.h>
#include <string.h>

Token createToken(TokenType type, const char *lexeme) {
  Token token;
  token.type = type;
  token.lexeme = _strdup(lexeme);
  return token;
}

void freeToken(Token *token) { free(token->lexeme); }
