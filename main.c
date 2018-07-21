#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "mem.h"
#include "token.h"
#include "parse.h"

typedef struct {
  Node *head_node;
  Vector node_pool;
  char *string_bank;
} ParsedSexpr;

ParsedSexpr _parse(char *sexpr)
{
  TokenList tl = tokenize(sexpr);
  TokenList tl2 = tl; // Working copy
  Vector node_pool = new_Vector(Node, tl2.count);
  Node *n = parse(&tl2.tokens, &tl2.count, &node_pool);
  free(tl.tokens);
  ParsedSexpr parsed = (ParsedSexpr){ n, node_pool, tl.strings };
  return parsed;
}

void file_print_test(char *sexpr, FILE *f)
{
  ParsedSexpr parsed = _parse(sexpr);

  print_node_sexpr(parsed.head_node, f, false, 0);
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
