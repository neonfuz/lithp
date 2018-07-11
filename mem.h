typedef struct vector_s {
  size_t itemSize;
  size_t count;
  size_t head;
  void *data;
} Vector;

#define new_Vector(type, count) _new_Vector(sizeof(type), count)

Vector _new_Vector(size_t itemSize, size_t count);
void Vector_push(Vector *vec, void *item);
void *Vector_next(Vector *vec);
void free_Vector(Vector vec);
