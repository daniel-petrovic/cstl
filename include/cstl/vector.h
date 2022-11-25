#ifndef CSTL_VECTOR
#define CSTL_VECTOR

#include <stdlib.h>

struct cstl_vector;

// Creation/Deletion
struct cstl_vector *cstl_vector_new(size_t elem_size);
void cstl_vector_clear(struct cstl_vector *);
void cstl_vector_delete(struct cstl_vector *);

size_t cstl_vector_elem_size(const struct cstl_vector *);
size_t cstl_vector_elem_count(const struct cstl_vector *);
size_t cstl_vector_elem_capacity(const struct cstl_vector *);
int cstl_vector_empty(const struct cstl_vector *);

// Modifier
void cstl_vector_reserve(struct cstl_vector *, size_t count);
void cstl_vector_push(struct cstl_vector *, const void *elem);
void *cstl_vector_pop(struct cstl_vector *);

// Element access
void *cstl_vector_back(struct cstl_vector *);
void *cstl_vector_front(struct cstl_vector *);

#endif
