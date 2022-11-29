#include "cstl/vector.h"

#include <assert.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

struct cstl_vector
{
  size_t esize;     // size of single element in bytes
  size_t ecount;    // number of elements
  size_t ecapacity; // max number of elements
  void *data;
};

struct cstl_vector *
cstl_vector_new (size_t elem_size)
{
  struct cstl_vector *vec = calloc (1, sizeof (struct cstl_vector));
  vec->esize = elem_size;
  vec->ecount = 0;
  vec->ecapacity = 0;
  vec->data = NULL;
  return vec;
}

void
cstl_vector_clear (struct cstl_vector *vec)
{
  free (vec->data);
  memset (vec, 0, sizeof (vec));
}

void
cstl_vector_delete (struct cstl_vector *vec)
{
  cstl_vector_clear (vec);
  free (vec);
}

size_t
cstl_vector_elem_size (const struct cstl_vector *vec)
{
  return vec->esize;
}

size_t
cstl_vector_elem_count (const struct cstl_vector *vec)
{
  return vec->ecount;
}

size_t
cstl_vector_elem_capacity (const struct cstl_vector *vec)
{
  return vec->ecapacity;
}

int
cstl_vector_empty (const struct cstl_vector *vec)
{
  return vec->ecount == 0;
}

void
cstl_vector_reserve (struct cstl_vector *vec, size_t count)
{
  if (count > vec->ecapacity)
    {
      vec->data = realloc (vec->data, count);
      vec->ecapacity = count;
    }
}

void
cstl_vector_push (struct cstl_vector *vec, const void *elem)
{
  if (vec->ecount >= vec->ecapacity)
    {
      cstl_vector_reserve (vec, MAX (1, 2 * vec->ecapacity));
    }

  void *back = vec->data + vec->esize * vec->ecount;
  memcpy (back, elem, vec->esize);
  ++vec->ecount;
}

void *
cstl_vector_pop (struct cstl_vector *vec)
{
  assert (vec->ecount > 0);
  void *back = cstl_vector_back (vec);
  --vec->ecount;
  return back;
}

void *
cstl_vector_back (struct cstl_vector *vec)
{
  assert (vec->ecount > 0);
  return vec->data + (vec->ecount - 1) * vec->esize;
}

void *
cstl_vector_front (struct cstl_vector *vec)
{
  assert (vec->ecount > 0);
  return vec->data;
}

void *
cstl_vector_at_or_null (struct cstl_vector *vec, size_t index)
{
  if (vec == NULL || vec->ecount <= index)
    {
      return NULL;
    }
  return vec->data + index * vec->esize;
}