#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "mem.h"
#include "token.h"
#include "parse.h"

static
void pad_depth(int depth, FILE *f)
{
  depth *= 2; // Tab width
  while (depth--) fputc(' ', f);
}

size_t print_node(Node *n, FILE *f, bool inList, size_t count)
{
  enum NodeType type = n==NULL ? P_NIL : n->type;
  switch (type) {
  case P_SYM:
    count += strlen(n->sym.name);
    fputs(n->sym.name, f);
    break;
  case P_PAIR:
    if (!inList)
      fputc('(', f);
    print_node(n->pair.a, f, false, count);
    if (n->pair.b == NULL) {
      fputc(')', f);
    } else {
      fputc(' ', f);
      print_node(n->pair.b, f, true, count);
    }
    break;
  case P_QUOTE:
    fputc('\'', f);
    print_node(n->quote.node, f, false, count);
    break;
  case P_LAMBDA:
    fputs("λ", f);
    break;
  case P_NIL:
    fputs("NIL", f);
    break;
  }
  return count;
}

static
Node *parse_list(Token **tkns, size_t *left, Vector *nodes)
{
  ++(*tkns);
  --(*left);

  if (!*left || (*tkns)->type == RPAR)
    return NULL;

  Node *n = parse(tkns, left, nodes);
  if (n == NULL)
    return NULL;

  Node *pair = Vector_next(nodes);
  pair->type = P_PAIR;
  pair->pair.a = n;
  pair->pair.b = parse_list(tkns, left, nodes);

  return pair;
}

Node *parse(Token **tkns, size_t *left, Vector *nodes)
{
  if (!*left)
    return NULL;

  Node *n;
  TokenType type = (*tkns)->type;

  if (type == SYM) {
    char *name = (*tkns)->name;
    if (!strcmp("quote", name)) {
      type = QUOTE;
    } else if (!strcmp("lambda", name)) {
      type = LAMBDA;
    }
  }

  switch (type) {
    case SYM:
      n = Vector_next(nodes);
      n->type = P_SYM;
      n->sym.name = (*tkns)[0].name;
      return n;
    case LPAR:
      return parse_list(tkns, left, nodes);
    case RPAR: break;
      return NULL;
    case QUOTE:
      n = Vector_next(nodes);
      n->type = P_QUOTE;
      (*tkns)++; (*left)--;
      n->quote.node = parse(tkns, left, nodes);
      return n;
    case LAMBDA:
      n = Vector_next(nodes);
      n->type = P_LAMBDA;
      return n;
    default: return NULL;
  }
}

void free_NodeList(NodeList nl)
{
  free(nl.nodes);
  free(nl.strings);
}
