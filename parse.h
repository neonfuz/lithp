struct Pair_s {
  struct Node_s *a, *b;
};

struct Symbol_s {
  char *name;
};

typedef struct Node_s {
  enum NodeType {P_NIL, P_SYM, P_PAIR} type;
  union {
    struct Pair_s pair;
    struct Symbol_s sym;
  };
} Node;

typedef struct {
  size_t count;
  Node *nodes;
  char *strings;
} NodeList;

NodeList parse(TokenList tl);
void free_NodeList(NodeList nl);
