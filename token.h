typedef enum { LPAR, SYM, RPAR, QUOTE, LAMBDA, SPACE } TokenType;

typedef struct {
  TokenType type;
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
