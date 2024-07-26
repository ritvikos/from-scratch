#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
  // Keywords
  TOKEN_CONST = 256,
  TOKEN_VAR,
  TOKEN_PROCEDURE,
  TOKEN_CALL,
  TOKEN_BEGIN,
  TOKEN_END,
  TOKEN_IF,
  TOKEN_THEN,
  TOKEN_WHILE,
  TOKEN_DO,

  // Operators
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_MULT,
  TOKEN_DIV,
  TOKEN_ASSIGN,
  TOKEN_EQUAL,
  TOKEN_NOT_EQUAL,
  TOKEN_LESS,
  TOKEN_LESS_EQUAL,
  TOKEN_GREATER,
  TOKEN_GREATER_EQUAL,

  // Punctuation
  TOKEN_COMMA,
  TOKEN_SEMICOLON,
  TOKEN_LPAREN,
  TOKEN_RPAREN,
  TOKEN_PERIOD,

  // Literals
  TOKEN_IDENTIFIER,
  TOKEN_NUMBER,

  // Special Tokens
  TOKEN_EOF,
  TOKEN_INVALID,
  TOKEN_NONE
} TokenType;

typedef struct {
  TokenType type;
  char *lexeme;
} Token;

Token createToken(TokenType type, const char *lexeme);
void freeToken(Token *token);

#endif
