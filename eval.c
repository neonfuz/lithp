#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stddef.h>

#include "token.h"
#include "mem.h"
#include "parse.h"
#include "eval.h"

Node *eval(Node *prog)
{
        assert(prog->type == P_PAIR);
        return prog;
//  switch (prog->pair.a->type) {
//  case P_PAIR:
//    eval(prog->pair.a)
//  }
//
//  return prog->pair.b;
}

