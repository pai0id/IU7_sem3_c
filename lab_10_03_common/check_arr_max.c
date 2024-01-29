#include "check_arr_max.h"
#include "associative_array.h"
#include "check_defines.h"
#include <stdio.h>

/// Поиск значения соответствующее максимальному ключу в массиве из одного элемента
START_TEST(test_arr_max_one)
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

    int *tmp;
    rc = assoc_array_max(arr, &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*tmp, 1);

    assoc_array_destroy(&arr);
}
END_TEST

/// Поиск значения соответствующее максимальному ключу в массиве из нескольких элементов
START_TEST(test_arr_max_many)
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

    int *tmp;
    rc = assoc_array_max(arr, &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*tmp, 5);

    assoc_array_destroy(&arr);
}
END_TEST

/// Поиск значения соответствующее максимальному ключу в пустом массиве
START_TEST(test_arr_max_empt)
{
    assoc_array_error_t rc;

    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    int *tmp;
    rc = assoc_array_max(arr, &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

Suite* arr_max_suite(void)
{
    Suite *s;
    TCase *pos, *neg;

    s = suite_create("arr_max");

    pos = tcase_create("pos");
    tcase_add_test(pos, test_arr_max_one);
    tcase_add_test(pos, test_arr_max_many);
    suite_add_tcase(s, pos);

    neg = tcase_create("neg");
    tcase_add_test(neg, test_arr_max_empt);
    suite_add_tcase(s, neg);

    return s;
}
