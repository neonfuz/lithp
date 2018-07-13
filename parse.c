#include <stdio.h>
#include <stdlib.h>

#include "mem.h"
#include "token.h"
#include "parse.h"

static
Node *parse_list(Token *tkns, size_t left, Vector *nodes)
{
  if (!left || tkns->type == RPAR)
    return NULL;

  Node *n = recur_parse(tkns, left, nodes);
  if (n == NULL)
    return NULL;

  Node *pair = Vector_next(nodes);
  pair->type = P_PAIR;
  pair->pair.a = n;
  pair->pair.b = parse_list(tkns+1, left-1, nodes);

  return pair;
}

Node *recur_parse(Token *tkns, size_t left, Vector *nodes)
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
