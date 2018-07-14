#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "token.h"

// TODO: make smarter string compacting algorithm
TokenList tokenize(char *sexpr)
{
  size_t len = strlen(sexpr);

  char *strings = malloc(len+1);
  size_t strhead = 0;

  Token *tokens = malloc(len * sizeof(Token));
  size_t tokhead = 0;

  bool inSymbol = false;

  for (int i = 0; i < len; ++i) {
    if (inSymbol && (sexpr[i] == '(' || sexpr[i] == ')')) {
      strings[strhead++] = '\0';
    }

    switch (sexpr[i]) {
    case '(': tokens[tokhead++] = (Token){ LPAR }; break;
    case ')': tokens[tokhead++] = (Token){ RPAR }; break;
    default:
      if (isblank(sexpr[i])) {
        if (inSymbol) {
          inSymbol = false;
          strings[strhead++] = '\0';
        }
      } else {
        if (!inSymbol) {
          tokens[tokhead++] = (Token){ SYM, strings+strhead };
          inSymbol = true;
        }
        strings[strhead++] = sexpr[i];
      }
    }
  }
  strings[strhead++] = '\0';

  strings = realloc(strings, strhead);
  tokens = realloc(tokens, tokhead * sizeof(Token));

  return (TokenList){tokhead, tokens, strings};
}

void free_TokenList(TokenList tl)
{
  free(tl.tokens);
  free(tl.strings);
}

void printTokens(Token *tokens, size_t count, FILE *stream) {
  for (int i=0; i<count; ++i) {
    switch (tokens[i].type) {
    case LPAR: fputc('(', stream); break;
    case RPAR: fputc(')', stream); break;
    case SYM: fprintf(stream, " %s ", tokens[i].name); break;
    }
  }
  fputc('\n', stream);
}
