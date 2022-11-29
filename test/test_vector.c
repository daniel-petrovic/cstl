#include "munit/munit.h"

#include "cstl/vector.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
static char* elem_sizes[] = { "1", "2", "4", "8", "16", "32", "64", "128", "256", "512", "1024", NULL };

static MunitParameterEnum parameters_elem_size[] = {
    {
        (char*)"elem_size", elem_sizes
    },
    { NULL, NULL }
};

static void* setup_elem_size(const MunitParameter params[], void* fixture)
{
    const char* elem_size = munit_parameters_get(params, "elem_size");
    size_t* psize = malloc(sizeof(size_t));
    *psize = atol(elem_size);
    return psize;
}


static void teardown_elem_size(void* fixture)
{
    free(fixture);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
static char* num_elems_to_push[] = { "1", "2", "4", "8", "16", "1024"};

static MunitParameterEnum parameters_num_elems_to_push[] = {
    {
        (char*)"num_elems", num_elems_to_push
    },
    { NULL, NULL }
};

static void* setup_num_elems_to_push(const MunitParameter params[], void* fixture)
{
    const char* elem_size = munit_parameters_get(params, "num_elems");
    size_t* psize = malloc(sizeof(size_t));
    *psize = atol(elem_size);
    return psize;
}


static void teardown_num_elems_to_push(void* fixture)
{
    free(fixture);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MunitResult test_vector_new_succeeds(const MunitParameter params[], void* fixture)
{
    size_t elem_size = *(size_t*)(fixture);
    struct cstl_vector* vec = cstl_vector_new(elem_size);
    munit_assert_ptr_not_equal(vec, NULL);
    munit_assert_uint64(elem_size, ==, cstl_vector_elem_size(vec));
    return MUNIT_OK;
}

MunitResult test_vector_elem_size(const MunitParameter params[], void* fixture)
{
    size_t elem_size = *(size_t*)(fixture);
    struct cstl_vector* vec = cstl_vector_new(elem_size);
    munit_assert_uint64(elem_size, ==, cstl_vector_elem_size(vec));
    return MUNIT_OK;
}

MunitResult test_vector_elem_count_is_zero_by_default(const MunitParameter params[], void* fixture)
{
    size_t elem_size = *(size_t*)(fixture);
    struct cstl_vector* vec = cstl_vector_new(elem_size);
    munit_assert_uint64(0, ==, cstl_vector_elem_count(vec));
    return MUNIT_OK;
}

MunitResult test_vector_elem_capacity_is_zero_by_default(const MunitParameter params[], void* fixture)
{
    struct cstl_vector* vec = cstl_vector_new(sizeof(int));
    munit_assert_uint64(0, ==, cstl_vector_elem_capacity(vec));
    return MUNIT_OK;
}

MunitResult test_vector_reserve_increases_capacity(const MunitParameter params[], void* fixture)
{
    struct cstl_vector* vec = cstl_vector_new(sizeof(int));
    cstl_vector_reserve(vec, 128);
    munit_assert_uint64(cstl_vector_elem_capacity(vec), >=, 128);
    return MUNIT_OK;
}

MunitResult test_vector_push_increases_count_and_capacity(const MunitParameter params[], void* fixture)
{
    size_t num_elements_to_push = *(size_t*)fixture;
    struct cstl_vector* vec = cstl_vector_new(sizeof(int));
    munit_assert_uint64(0, ==, cstl_vector_elem_count(vec));
    int x;
    cstl_vector_push(vec, &x);
    munit_assert_uint64(1, ==, cstl_vector_elem_count(vec));
    munit_assert_uint64(cstl_vector_elem_count(vec), <=, cstl_vector_elem_capacity(vec));
    return MUNIT_OK;
}

MunitResult test_vector_push(const MunitParameter params[], void* fixture)
{
    struct cstl_vector* vec = cstl_vector_new(sizeof(int));
    int x = 8;
    cstl_vector_push(vec, &x);
    int y = *(int*)(cstl_vector_back(vec));
    munit_assert_int(x, ==, y);
    return MUNIT_OK;
}

MunitResult test_vector_empty(const MunitParameter params[], void* fixture)
{
    struct cstl_vector* vec = cstl_vector_new(sizeof(int));
    munit_assert_true(cstl_vector_empty(vec));
    return MUNIT_OK;
}

MunitResult test_vector_empty_false_after_push(const MunitParameter params[], void* fixture)
{
    struct cstl_vector* vec = cstl_vector_new(sizeof(int));
    int x;
    cstl_vector_push(vec, &x);
    munit_assert_false(cstl_vector_empty(vec));
    return MUNIT_OK;
}

MunitResult test_vector_pop(const MunitParameter params[], void* fixture)
{
    struct cstl_vector* vec = cstl_vector_new(sizeof(int));
    int x = 0;
    cstl_vector_push(vec, &x);
    munit_assert_uint64(1, ==, cstl_vector_elem_count(vec));
    cstl_vector_pop(vec);
    munit_assert_uint64(0, ==, cstl_vector_elem_count(vec));
    munit_assert_true(cstl_vector_empty(vec));
    return MUNIT_OK;
}

MunitResult test_vector_back(const MunitParameter params[], void* fixture)
{
    struct cstl_vector* vec = cstl_vector_new(sizeof(int));
    const int x = 123;
    cstl_vector_push(vec, &x);
    munit_assert_uint64(1, ==, cstl_vector_elem_count(vec));
    munit_assert_int(x, ==, *(int*)(cstl_vector_back(vec)));
    return MUNIT_OK;
}

MunitResult test_vector_front(const MunitParameter params[], void* fixture)
{
    struct cstl_vector* vec = cstl_vector_new(sizeof(int));
    const int x = 123;
    cstl_vector_push(vec, &x);
    munit_assert_uint64(1, ==, cstl_vector_elem_count(vec));
    munit_assert_int(x, ==, *(int*)(cstl_vector_front(vec)));

    const int y = 456;
    cstl_vector_push(vec, &y);
    munit_assert_uint64(2, ==, cstl_vector_elem_count(vec));
    munit_assert_int(x, ==, *(int*)(cstl_vector_front(vec)));
    return MUNIT_OK;
}

MunitResult test_vector_at(const MunitParameter params[], void* fixture)
{
    struct cstl_vector* vec = cstl_vector_new(sizeof(int));
    munit_assert_ptr_null(cstl_vector_at_or_null(vec, 0));
    const int x = 1;
    cstl_vector_push(vec, &x);
    munit_assert_ptr_not_null(cstl_vector_at_or_null(vec, 0));
    munit_assert_int(x, ==, *(int*)cstl_vector_at_or_null(vec, 0));
    return MUNIT_OK;
}


// All Tests
static MunitTest test_suite_tests[] = {
    {
        (char*)"/new",
        test_vector_new_succeeds,
        setup_elem_size,   // setup
        teardown_elem_size,  // teardown
        MUNIT_SUITE_OPTION_NONE,
        parameters_elem_size
    },
    {
        (char*)"/elem_size",
        test_vector_elem_size,
        setup_elem_size,   // setup
        teardown_elem_size,  // teardown
        MUNIT_SUITE_OPTION_NONE,
        parameters_elem_size
    },
    {
        (char*)"/elem_count_is_zero_by_default",
        test_vector_elem_count_is_zero_by_default,
        NULL,   // setup
        NULL,  // teardown
        MUNIT_SUITE_OPTION_NONE,
        NULL
    },
    {
        (char*)"/elem_capacity_is_zero_by_default",
        test_vector_elem_capacity_is_zero_by_default,
        NULL,   // setup
        NULL,  // teardown
        MUNIT_SUITE_OPTION_NONE,
        NULL
    },
    {
        (char*)"/reserve_increases_capacity",
        test_vector_reserve_increases_capacity,
        NULL,   // setup
        NULL,  // teardown
        MUNIT_SUITE_OPTION_NONE,
        NULL
    },
    {
        (char*)"/push_increases_count_and_capacity",
        test_vector_push_increases_count_and_capacity,
        setup_num_elems_to_push,   // setup
        teardown_num_elems_to_push,  // teardown
        MUNIT_SUITE_OPTION_NONE,
        parameters_num_elems_to_push
    },
    {
        (char*)"/push",
        test_vector_push,
        NULL,   // setup
        NULL,  // teardown
        MUNIT_SUITE_OPTION_NONE,
        NULL
    },
    {
        (char*)"/pop",
        test_vector_pop,
        NULL,   // setup
        NULL,  // teardown
        MUNIT_SUITE_OPTION_NONE,
        NULL
    },
    {
        (char*)"/back",
        test_vector_back,
        NULL,   // setup
        NULL,  // teardown
        MUNIT_SUITE_OPTION_NONE,
        NULL
    },
    {
        (char*)"/front",
        test_vector_front,
        NULL,   // setup
        NULL,  // teardown
        MUNIT_SUITE_OPTION_NONE,
        NULL
    },
    {
        (char*)"/empty",
        test_vector_empty,
        NULL,   // setup
        NULL,  // teardown
        MUNIT_SUITE_OPTION_NONE,
        NULL
    },
    {
        (char*)"/empty_false_after_push",
        test_vector_empty_false_after_push,
        NULL,   // setup
        NULL,  // teardown
        MUNIT_SUITE_OPTION_NONE,
        NULL
    },
    {
        (char*)"/at",
        test_vector_at,
        NULL,   // setup
        NULL,  // teardown
        MUNIT_SUITE_OPTION_NONE,
        NULL
    },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

// Test suite
static const MunitSuite test_suite = {
    (char*)("/test_cstl_vector"),
    test_suite_tests,
    NULL, 
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
  /* Finally, we'll actually run our test suite!  That second argument
   * is the user_data parameter which will be passed either to the
   * test or (if provided) the fixture setup function. */
  return munit_suite_main(&test_suite, (void*) "µnit", argc, argv);
}
