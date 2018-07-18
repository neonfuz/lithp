#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "mem.h"
#include "token.h"
#include "parse.h"

void file_print_test(char *sexpr, FILE *f)
{
  TokenList tl = tokenize(sexpr);

  Token *tokens = tl.tokens;
  size_t count = tl.count;
  Vector nodes = new_Vector(Node, tl.count);
  Node *n = parse(&tokens, &count, &nodes);

  print_node_sexpr(n, f, false, 0);
  fputc('\n', f);

  // TODO: free resources
}

void print_test(char *sexpr)
{
  file_print_test(sexpr, stdout);
}


int main(int argc, char **argv)
{
  print_test("(hello world)");
  print_test("(foo (bar (baz) hello world) 9001)");
  // TODO: fix implementation, fails on duplicate baz

  return 0;
}
