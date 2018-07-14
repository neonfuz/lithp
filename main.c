#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "mem.h"
#include "token.h"
#include "parse.h"

void print_test(char *sexpr)
{
  TokenList tl = tokenize(sexpr);
  printTokens(tl.tokens, tl.count, stdout);

  Token *tokens = tl.tokens;
  size_t count = tl.count;
  Vector nodes = new_Vector(Node, tl.count);
  Node *n = parse(&tokens, &count, &nodes);

  print_parsenode(n, 0, stdout);

  // TODO: free resources
}

int main(int argc, char **argv)
{
  print_test("(hello world)");
  print_test("(foo (bar (baz) hello world) 9001)");
  // TODO: fix implementation, fails on duplicate baz

  return 0;
}
