#include "check_arr_rem.h"
#include "associative_array.h"
#include "check_defines.h"
#include <stdio.h>

/// Удаление элемента
START_TEST(test_arr_rem_good)
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

    rc = assoc_array_remove(arr, "feb");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *tmp;
    rc = assoc_array_find(arr, "feb", &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

/// Удаление элемента - пустая строка
START_TEST(test_arr_rem_empt)
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

    rc = assoc_array_remove(arr, "");
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST

/// Удаление элемента - не существуеут
START_TEST(test_arr_rem_bad)
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

    rc = assoc_array_remove(arr, "err");
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

Suite* arr_rem_suite(void)
{
    Suite *s;
    TCase *pos, *neg;

    s = suite_create("arr_rem");

    pos = tcase_create("pos");
    tcase_add_test(pos, test_arr_rem_good);
    suite_add_tcase(s, pos);

    neg = tcase_create("neg");
    tcase_add_test(neg, test_arr_rem_bad);
    tcase_add_test(neg, test_arr_rem_empt);
    suite_add_tcase(s, neg);

    return s;
}
