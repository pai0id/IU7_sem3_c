#include "check_arr_each.h"
#include "associative_array.h"
#include "check_defines.h"
#include <stdio.h>

void sqr(const char *key, int *num, void *param)
{
    (void)key;
    (void)param;
    *num *= *num;
}

void mul(const char *key, int *num, void *param)
{
    (void)key;
    int *x = param;
    *num *= *x;
}

/// Функция без параметра
START_TEST(test_arr_each_no_param)
{
    check_pair_t pair_arr[N_MAX] = {
        {"jan", 1},
        {"feb", 2},
        {"mar", 3},
        {"apr", 4},
        {"may", 5}
    };
    int exp[N_MAX] = {1, 4, 9, 16, 25};
    size_t n = 5;
    assoc_array_error_t rc;

    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    for (size_t i = 0; i < n; ++i)
    {
        rc = assoc_array_insert(arr, pair_arr[i].key, pair_arr[i].val);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    }

    rc = assoc_array_each(arr, sqr, NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *tmp;
    for (size_t i = 0; i < n; ++i)
    {
        rc = assoc_array_find(arr, pair_arr[i].key, &tmp);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_int_eq(*tmp, exp[i]);
    }

    assoc_array_destroy(&arr);
}
END_TEST

/// Функция с параметром
START_TEST(test_arr_each_yes_param)
{
    check_pair_t pair_arr[N_MAX] = {
        {"jan", 1},
        {"feb", 2},
        {"mar", 3},
        {"apr", 4},
        {"may", 5}
    };
    int exp[N_MAX] = {2, 4, 6, 8, 10};
    size_t n = 5;
    assoc_array_error_t rc;

    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    for (size_t i = 0; i < n; ++i)
    {
        rc = assoc_array_insert(arr, pair_arr[i].key, pair_arr[i].val);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    }

    int x = 2;
    rc = assoc_array_each(arr, mul, &x);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *tmp;
    for (size_t i = 0; i < n; ++i)
    {
        rc = assoc_array_find(arr, pair_arr[i].key, &tmp);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_int_eq(*tmp, exp[i]);
    }

    assoc_array_destroy(&arr);
}
END_TEST

Suite* arr_each_suite(void)
{
    Suite *s;
    TCase *pos;

    s = suite_create("arr_each");

    pos = tcase_create("pos");
    tcase_add_test(pos, test_arr_each_yes_param);
    tcase_add_test(pos, test_arr_each_no_param);
    suite_add_tcase(s, pos);

    return s;
}
