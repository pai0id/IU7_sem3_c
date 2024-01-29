#include "check_arr_io.h"
#include "associative_array.h"
#include "check_defines.h"
#include <stdio.h>

/// Запись-поиск одного элемента
START_TEST(test_arr_io_one)
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
    for (size_t i = 0; i < n; ++i)
    {
        rc = assoc_array_find(arr, pair_arr[i].key, &tmp);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_int_eq(*tmp, pair_arr[i].val);
    }

    assoc_array_destroy(&arr);
}
END_TEST

/// Запись-поиск нескольких элементов
START_TEST(test_arr_io_many)
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
    for (size_t i = 0; i < n; ++i)
    {
        rc = assoc_array_find(arr, pair_arr[i].key, &tmp);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_int_eq(*tmp, pair_arr[i].val);
    }

    assoc_array_destroy(&arr);
}
END_TEST

/// При вызове функции вставки указана пустая строка
START_TEST(test_arr_io_empt_str_ins)
{
    assoc_array_error_t rc;

    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    rc = assoc_array_insert(arr, "", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST

/// Значение с таким ключом уже в массиве
START_TEST(test_arr_io_exists)
{
    assoc_array_error_t rc;

    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    rc = assoc_array_insert(arr, "str", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_insert(arr, "str", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_KEY_EXISTS);

    assoc_array_destroy(&arr);
}
END_TEST

/// При вызове функции поиска указана пустая строка
START_TEST(test_arr_io_empt_str_find)
{
    assoc_array_error_t rc;

    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    rc = assoc_array_insert(arr, "str", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *tmp;
    rc = assoc_array_find(arr, "", &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST

/// Не найдено значение по указанному ключу
START_TEST(test_arr_io_not_found)
{
    assoc_array_error_t rc;

    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    rc = assoc_array_insert(arr, "str", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *tmp;
    rc = assoc_array_find(arr, "a", &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

Suite* arr_io_suite(void)
{
    Suite *s;
    TCase *pos, *neg;

    s = suite_create("arr_io");

    pos = tcase_create("pos");
    tcase_add_test(pos, test_arr_io_one);
    tcase_add_test(pos, test_arr_io_many);
    suite_add_tcase(s, pos);

    neg = tcase_create("neg");
    tcase_add_test(neg, test_arr_io_empt_str_ins);
    tcase_add_test(neg, test_arr_io_exists);
    tcase_add_test(neg, test_arr_io_empt_str_find);
    tcase_add_test(neg, test_arr_io_not_found);
    suite_add_tcase(s, neg);

    return s;
}
