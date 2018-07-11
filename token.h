typedef struct {
  enum TokenType { LPAR, SYM, RPAR } type;
  union {
    char *name;
  };
} Token;

typedef struct {
  size_t count;
  Token *tokens;
  char *strings;
} TokenList;

TokenList tokenize(char *sexpr);
void free_TokenList(TokenList tl);
void printTokens(Token *tokens, size_t count, FILE *stream);
