#ifndef CSTL_VECTOR
#define CSTL_VECTOR

#include <stdlib.h>

struct cstl_vector;

// Creation/Deletion
/**
 * @brief Allocate a new vector. Caller is reponsible for freeing the vector.
 * @see cstl_vector_delete
 * 
 * @param elem_size 
 * @return struct cstl_vector* 
 */
struct cstl_vector *cstl_vector_new(size_t elem_size);

/**
 * @brief Delete the vector and it's associated memory.
 * 
 * @param vec 
 */
void cstl_vector_delete(struct cstl_vector *vec);

/**
 * @brief Get the size in bytes of the contained element type.
 * 
 * @param vec 
 * @return size_t 
 */
size_t cstl_vector_elem_size(const struct cstl_vector *vec);

/**
 * @brief Get the number (not bytes!) of elements in the vector.
 *        The number of bytes can be calculated with cont * esize
 * @param vec 
 * @return size_t 
 */
size_t cstl_vector_elem_count(const struct cstl_vector *vec);

/**
 * @brief Get the max number of elements (not bytes!) which
 *        could be inserted in the vector without reallocation.
 * 
 * @param vec 
 * @return size_t 
 */
size_t cstl_vector_elem_capacity(const struct cstl_vector *vec);

/**
 * @brief  Check if vector is empty.
 * 
 * @param vec 
 * @return int - non-zero if empty, otherwise 0
 */
int cstl_vector_empty(const struct cstl_vector *vec);

// Modifier
/**
 * @brief Set the vector capacity in number of elements (not bytes)!. 
 *        Does nothing if count < current capacity.
 * 
 * @param vec 
 * @param count 
 */
void cstl_vector_reserve(struct cstl_vector *vec, size_t count);

/**
 * @brief Push the element at the end.
 * 
 * @param vec 
 * @param elem 
 */
void cstl_vector_push(struct cstl_vector *vec, const void *elem);

/**
 * @brief Pop and return a pointer to the last element.
 *        The pointer is invalidated if an reallocation happens after the pop operation,
 *        for ex. due a new call to reserve.
 * 
 * @param vec 
 * @return void* 
 */
void *cstl_vector_pop(struct cstl_vector *vec);

// Element access
/**
 * @brief Get a pointer to the last element.
 *        The pointer is invalidated if an reallocation happens after the pop operation,
 *        for ex. due a new call to reserve.
 * 
 * @param vec 
 * @return void* 
 */
void *cstl_vector_back(struct cstl_vector *vec);

/**
 * @brief Get a pointer to the first element.
 *        The pointer is invalidated if an reallocation happens after the pop operation,
 *        for ex. due a new call to reserve.
 * 
 * @param vec 
 * @return void* 
 */
void *cstl_vector_front(struct cstl_vector *vec);

/**
 * @brief Get a pointer to the element at a specified index.
 *        The pointer is invalidated if an reallocation happens after the pop operation,
 *        for ex. due a new call to reserve.
 * 
 * @param index 
 * @return void* 
 */
void *cstl_vector_at_or_null(struct cstl_vector *, size_t index);

#endif
