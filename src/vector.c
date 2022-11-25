#include "cstl/vector.h"

#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

struct cstl_vector {
    size_t esize;       // size of single element in bytes
    size_t ecount;      // number of elements
    size_t ecapacity;   // max number of elements
    void* data;
};

struct cstl_vector* cstl_vector_new(size_t elem_size) {
    struct cstl_vector* vec = calloc(1, sizeof(struct cstl_vector));
    vec->esize = elem_size;
    vec->ecount = 0;
    vec->ecapacity = 0;
    vec->data = NULL;
    return vec;
}

void cstl_vector_clear(struct cstl_vector* vec) {
    free(vec->data);
}

void cstl_vector_delete(struct cstl_vector* vec) {
    cstl_vector_clear(vec);
    free(vec);
}

size_t cstl_vector_elem_size(const struct cstl_vector* vec) {
    return vec->esize;
}

size_t cstl_vector_elem_count(const struct cstl_vector* vec)
{
    return vec->ecount;
}

size_t cstl_vector_elem_capacity(const struct cstl_vector* vec)
{
    return vec->ecapacity;
}

void cstl_vector_reserve(struct cstl_vector* vec, size_t count)
{
    if (count > vec->ecapacity) {
        vec->data = realloc(vec->data, count);
        vec->ecapacity = count;
    }
}

void cstl_vector_push(struct cstl_vector* vec, void* elem)
{
    if (vec->ecount >= vec->ecapacity) {
        cstl_vector_reserve(vec, MAX(1, 2*vec->ecapacity));
    }

    memcpy(vec->data, elem, vec->esize);
    ++vec->ecount;
}