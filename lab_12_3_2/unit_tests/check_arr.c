#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "libarr.h"

#define N 10

#define ERR_OK 0
#define ERR_DIFF_EL 1
#define ERR_DIFF_SIZE 2

int int_arr_eq(int *l_arr, size_t l_n, int *r_arr, size_t r_n)
{
    if (l_n != r_n)
        return ERR_DIFF_SIZE;
    for (size_t i = 0; i < l_n; ++i)
        if (l_arr[i] != r_arr[i])
            return ERR_DIFF_EL;
    return ERR_OK;
}

/// Массив из одного простого числа
START_TEST(test_fill_primes_one)
{
    int arr[N];
    int exp[N] = {2};
    size_t n = 1;
    fill_primes(arr, n);
    ck_assert_int_eq(int_arr_eq(arr, n, exp, n), ERR_OK);
}
END_TEST

/// Массив из нескольких простых чисел
START_TEST(test_fill_primes_many)
{
    int arr[N];
    int exp[N] = {2, 3, 5, 7, 11};
    size_t n = 5;
    fill_primes(arr, n);
    ck_assert_int_eq(int_arr_eq(arr, n, exp, n), ERR_OK);
}
END_TEST

Suite* fill_primes_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("fill_primes");
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_fill_primes_many);
    tcase_add_test(tc_pos, test_fill_primes_one);

    suite_add_tcase(s, tc_pos);

    return s;
}

/// Нет четных чисел
START_TEST(test_ncpy_and_add_no_even)
{
    int arr[N] = {1, 3, 5, 7};
    size_t n_arr = 4;
    int exp[N] = {1, 3, 5, 7};
    size_t n_exp = 4;

    int res[N];
    size_t n_res;
    int rc = ncpy_and_add(arr, n_arr, res, N, &n_res, 42);

    ck_assert_int_eq(rc, LIB_OK);

    ck_assert_int_eq(n_res, n_exp);
    ck_assert_int_eq(int_arr_eq(res, n_res, exp, n_exp), ERR_OK);
}
END_TEST

/// Есть четные числа
START_TEST(test_ncpy_and_add_yes_even)
{
    int arr[N] = {1, 2, 5, 7};
    size_t n_arr = 4;
    int exp[N] = {1, 2, 42, 5, 7};
    size_t n_exp = 5;

    int res[N];
    size_t n_res;
    int rc = ncpy_and_add(arr, n_arr, res, N, &n_res, 42);

    ck_assert_int_eq(rc, LIB_OK);

    ck_assert_int_eq(n_res, n_exp);
    ck_assert_int_eq(int_arr_eq(res, n_res, exp, n_exp), ERR_OK);
}
END_TEST

/// Все числа четные
START_TEST(test_ncpy_and_add_all_even)
{
    int arr[N] = {2, 4, 6};
    size_t n_arr = 3;
    int exp[N] = {2, 42, 4, 42, 6, 42};
    size_t n_exp = 6;

    int res[N];
    size_t n_res;
    int rc = ncpy_and_add(arr, n_arr, res, N, &n_res, 42);

    ck_assert_int_eq(rc, LIB_OK);

    ck_assert_int_eq(n_res, n_exp);
    ck_assert_int_eq(int_arr_eq(res, n_res, exp, n_exp), ERR_OK);
}
END_TEST

/// Доступный размер меньше нужного
START_TEST(test_ncpy_and_add_not_full)
{
    int arr[N] = {2, 4, 6};
    size_t n_arr = 3;

    int res[N];
    size_t n_res;
    int rc = ncpy_and_add(arr, n_arr, res, 2, &n_res, 42);

    ck_assert_int_eq(rc, LIB_ERR_MEM_SIZE);
}
END_TEST

/// Доступный размер 0
START_TEST(test_ncpy_and_add_zero)
{
    int arr[N] = {2, 4, 6};
    size_t n_arr = 3;
    size_t n_exp = 6;

    int res[N];
    size_t n_res;
    int rc = ncpy_and_add(arr, n_arr, res, 0, &n_res, 42);

    ck_assert_int_eq(rc, LIB_OK);

    ck_assert_int_eq(n_res, n_exp);
}
END_TEST

/// Доступный dst == NULL && dst_available_size != 0
START_TEST(test_ncpy_and_add_err_args)
{
    int arr[N] = {2, 4, 6};
    size_t n_arr = 3;

    size_t n_res;
    int rc = ncpy_and_add(arr, n_arr, NULL, 42, &n_res, 42);

    ck_assert_int_eq(rc, LIB_ERR_ARGS);
}
END_TEST

Suite* ncpy_and_add_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("ncpy_and_add");
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_ncpy_and_add_no_even);
    tcase_add_test(tc_pos, test_ncpy_and_add_yes_even);
    tcase_add_test(tc_pos, test_ncpy_and_add_all_even);
    tcase_add_test(tc_pos, test_ncpy_and_add_not_full);
    tcase_add_test(tc_pos, test_ncpy_and_add_zero);
    tcase_add_test(tc_pos, test_ncpy_and_add_err_args);

    suite_add_tcase(s, tc_pos);

    return s;
}
