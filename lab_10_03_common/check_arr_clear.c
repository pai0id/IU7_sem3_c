#include "check_arr_clear.h"
#include "associative_array.h"
#include "check_defines.h"
#include <stdio.h>

/// Очистка массива из одного элемента
START_TEST(test_arr_clear_one)
{
    check_pair_t pair_arr[N_MAX] = {
        {"jan", 1}
    };
    size_t n = 1;
    assoc_array_error_t rc;

    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    for (size_t i = 0; i < n; ++i)
    {
        rc = assoc_array_insert(arr, pair_arr[i].key, pair_arr[i].val);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    }

    rc = assoc_array_clear(arr);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *tmp;
    for (size_t i = 0; i < n; ++i)
    {
        rc = assoc_array_find(arr, pair_arr[i].key, &tmp);
        ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    }

    assoc_array_destroy(&arr);
}
END_TEST

/// Очистка массива из нескольких элементов
START_TEST(test_arr_clear_many)
{
    check_pair_t pair_arr[N_MAX] = {
        {"jan", 1},
        {"feb", 2},
        {"mar", 3},
        {"apr", 4},
        {"may", 5}
    };
    size_t n = 5;
    assoc_array_error_t rc;

    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    for (size_t i = 0; i < n; ++i)
    {
        rc = assoc_array_insert(arr, pair_arr[i].key, pair_arr[i].val);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    }

    rc = assoc_array_clear(arr);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *tmp;
    for (size_t i = 0; i < n; ++i)
    {
        rc = assoc_array_find(arr, pair_arr[i].key, &tmp);
        ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    }

    assoc_array_destroy(&arr);
}
END_TEST

/// Очистка - функции подан пустой указатель
START_TEST(test_arr_clear_null)
{
    assoc_array_error_t rc;

    assoc_array_t arr = NULL;

    rc = assoc_array_clear(arr);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

Suite* arr_clear_suite(void)
{
    Suite *s;
    TCase *pos, *neg;

    s = suite_create("arr_clear");

    pos = tcase_create("pos");
    tcase_add_test(pos, test_arr_clear_one);
    tcase_add_test(pos, test_arr_clear_many);
    suite_add_tcase(s, pos);

    neg = tcase_create("neg");
    tcase_add_test(neg, test_arr_clear_null);
    suite_add_tcase(s, neg);

    return s;
}
