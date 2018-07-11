#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "parse.h"
#include "mem.h"

Node *recur_parse(Token *tkns, size_t left, Vector *nodes)
{
  Node n;
  switch (tkns[0].type) {
    case SYM:
      n.type = P_SYM;
      n.sym.name = tkns[0].name;
      Vector_push(nodes, &n);
      break;
    case LPAR: break;
      n.type = P_PAIR;
      Vector_push(nodes, &n);
    case RPAR: break;
  }
}

void free_NodeList(NodeList nl)
{
  free(nl.nodes);
  free(nl.strings);
}
