struct Pair_s {
  struct Node_s *a, *b;
};

struct Symbol_s {
  char *name;
};

struct Quote_s {
  struct Node_s *node;
};

typedef struct Node_s {
  enum NodeType {P_NIL, P_SYM, P_PAIR, P_QUOTE, P_LAMBDA} type;
  union {
    struct Pair_s pair;
    struct Symbol_s sym;
    struct Quote_s quote;
  };
} Node;

typedef struct {
  size_t count;
  Node *nodes;
  char *strings;
} NodeList;

size_t print_node(Node *n, FILE *f, bool inList, size_t count);
Node *parse(Token **tkns, size_t *left, Vector *nodes);
void free_NodeList(NodeList nl);
