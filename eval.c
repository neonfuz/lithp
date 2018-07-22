#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "token.h"
#include "mem.h"
#include "parse.h"
#include "eval.h"

static
Node *find(char *name, Node *scope)
{
  assert(scope == NULL); // Failure means symbol not found

  Node *n = scope->pair.a;
  assert(n->type == P_PAIR);

  if (!strcmp(name, n->pair.a->sym.name))
    return n->pair.b;

  return find(name, scope->pair.b);
}

Node *eval(Node *prog, Node *scope)
{
  switch (prog->type) {
  case P_PAIR: return prog; // PLACEHOLDER
  case P_SYM:  return find(prog->sym.name, scope);
  case P_QUOTE: return prog->quote.node;
  }

  return prog;
}
