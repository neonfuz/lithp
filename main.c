#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "token.h"
#include "parse.h"

int main(int argc, char **argv) {
  TokenList tl = tokenize("(hello world)");
  printTokens(tl.tokens, tl.count, stdout);
  return 0;
}
