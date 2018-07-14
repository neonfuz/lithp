#include <stdio.h>
#include <stdlib.h>

#include "mem.h"
#include "token.h"
#include "parse.h"

static
void pad_depth(int depth, FILE *f)
{
  depth *= 2; // Tab width
  while (depth--) fputc(' ', f);
}

void print_parsenode(Node *n, int depth, FILE *f)
{
  enum NodeType type = n==NULL ? P_NIL : n->type;
  char *typestr;
  switch (type) {
  case P_NIL:  typestr = "NIL"; break;
  case P_SYM:  typestr = "SYM"; break;
  case P_PAIR: typestr = "PAIR"; break;
  default:     typestr = "UNKNOWN"; break;
  }

  pad_depth(depth, f);
  fprintf(f, "type: %s\n", typestr);

  switch (type) {
  case P_NIL:
    break;
  case P_SYM:
    pad_depth(depth, f);
    fprintf(f, "content: %s\n\n", n->sym.name);
    break;
  case P_PAIR:
    print_parsenode(n->pair.a, depth+1, f);
    print_parsenode(n->pair.b, depth+1, f);
    break;
  default: break;
  }
}

static
Node *parse_list(Token *tkns, size_t left, Vector *nodes)
{
  if (!left || tkns->type == RPAR)
    return NULL;

  Node *n = parse(tkns, left, nodes);
  if (n == NULL)
    return NULL;

  Node *pair = Vector_next(nodes);
  pair->type = P_PAIR;
  pair->pair.a = n;
  pair->pair.b = parse_list(tkns+1, left-1, nodes);

  return pair;
}

Node *parse(Token *tkns, size_t left, Vector *nodes)
{
  if (!left)
    return NULL;

  Node *n;
  switch (tkns->type) {
    case SYM:
      n = Vector_next(nodes);
      n->type = P_SYM;
      n->sym.name = tkns[0].name;
      return n;
    case LPAR:
      return parse_list(tkns+1, left-1, nodes);
    case RPAR: break;
      return NULL;
  }
}

void free_NodeList(NodeList nl)
{
  free(nl.nodes);
  free(nl.strings);
}
