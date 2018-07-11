#include <stdlib.h>
#include <string.h>

#include "mem.h"

Vector _new_Vector(size_t itemSize, size_t count)
{
  return (Vector){
    itemSize, count, 0, malloc(itemSize*count)
  };
}

static
void Vector_expand(Vector *vec)
{
  vec->count *= 2;
  vec->data = realloc(vec->data, vec->count * vec->itemSize);
}

void Vector_push(Vector *vec, void *item)
{
  if (vec->head >= vec->count)
    Vector_expand(vec);

  char *dest = vec->data + vec->head++ * vec->itemSize;
  memcpy(dest, item, vec->itemSize);
}

void *Vector_next(Vector *vec)
{
  if (vec->head >= vec->count) Vector_expand(vec);
  return vec->data + vec->head++ * vec->itemSize;
}

void free_Vector(Vector vec)
{
  free(vec.data);
}
