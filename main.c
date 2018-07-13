#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "mem.h"
#include "token.h"
#include "parse.h"

int main(int argc, char **argv) {
  TokenList tl = tokenize("(hello world)");
  printTokens(tl.tokens, tl.count, stdout);

  Vector nodes = new_Vector(Node, tl.count);
  Node *n = recur_parse(tl.tokens, tl.count, &nodes);
  printf("%p\n", n);
  return 0;
}
