#ifndef LOOKUP_H
#define LOOKUP_H

// For optimal lookup performance,
// a hashmap is generally preferred
// due to its O(1) average time complexity.

// However, since this is a tiny project aimed at
// understanding compiler internals,
// an array is used instead.

#include "lex.h"
#include "token.h"

typedef struct {
  const char ch;
  TokenType type;
} SymbolLookup;

const SymbolLookup symTable[] = {
    {'+', TOKEN_PLUS},    {'-', TOKEN_MINUS},     {'*', TOKEN_MULT},
    {'/', TOKEN_DIV},     {'(', TOKEN_LPAREN},    {')', TOKEN_RPAREN},
    {',', TOKEN_COMMA},   {';', TOKEN_SEMICOLON}, {'.', TOKEN_PERIOD},
    {'=', TOKEN_EQUAL},   {'#', TOKEN_NOT_EQUAL}, {'<', TOKEN_LESS},
    {'>', TOKEN_GREATER}, {':', TOKEN_INVALID},   {'!', TOKEN_WRITE}};

const size_t symTableLen = (sizeof(symTable) / sizeof(symTable[0]));

typedef struct {
  const char *lexeme;
  TokenType type;
} keywordLookup;

const keywordLookup keywordTable[] = {
    {"const", TOKEN_CONST},
    {"var", TOKEN_VAR},
    {"procedure", TOKEN_PROCEDURE},
    {"call", TOKEN_CALL},
    {"begin", TOKEN_BEGIN},
    {"end", TOKEN_END},
    {"if", TOKEN_IF},
    {"else", TOKEN_ELSE},
    {"then", TOKEN_THEN},
    {"while", TOKEN_WHILE},
    {"do", TOKEN_DO},
};

const size_t keywordTableLen = (sizeof(keywordTable) / sizeof(keywordTable[0]));

Token lookupKeywordIdentifier(Lexer *lexer);
Token lookupNumber(Lexer *lexer);
Token lookupSymbol(Lexer *lexer, char ch);
Token handleLessThan(Lexer *lexer);
Token handleGreaterThan(Lexer *lexer);
Token handleColon(Lexer *lexer);

#endif
