#include <check.h>
#include <stdio.h>
#include <string.h>
#include "film_arr.h"
#include "check_func.h"
#include <stdbool.h>

/// Одна структура
START_TEST(test_fa_count_one)
{
    struct film_t exp = { "Aaa", "Bob", 2000 };
    FILE *f = fopen("./out/tmp", "w");
    film_print(f, &exp);
    fclose(f);

    f = fopen("./out/tmp", "r");
    size_t cnt;
    int rc = fa_count(f, &cnt);
    fclose(f);

    ck_assert_int_eq(rc, OK);
    ck_assert_uint_eq(cnt, 1);
}
END_TEST

/// Несколько структур
START_TEST(test_fa_count_many)
{
    struct film_t exp = { "Aaa", "Bob", 2000 };
    FILE *f = fopen("./out/tmp", "w");
    for (size_t i = 0; i < 3; ++i)
        film_print(f, &exp);
    fclose(f);

    f = fopen("./out/tmp", "r");
    size_t cnt;
    int rc = fa_count(f, &cnt);
    fclose(f);

    ck_assert_int_eq(rc, OK);
    ck_assert_uint_eq(cnt, 3);
}
END_TEST

/// Ноль структур
START_TEST(test_fa_count_none)
{
    
    FILE *f = fopen("./out/tmp", "w");
    fclose(f);

    f = fopen("./out/tmp", "r");
    size_t cnt;
    int rc = fa_count(f, &cnt);
    fclose(f);

    ck_assert_int_eq(rc, OK);
    ck_assert_uint_eq(cnt, 0);
}
END_TEST

/// Некорректная структура
START_TEST(test_fa_count_neg)
{
    FILE *f = fopen("./out/tmp", "w");
    fprintf(f, "ab\nba\naa\nrr\n");
    fclose(f);

    f = fopen("./out/tmp", "r");
    size_t cnt;
    int rc = fa_count(f, &cnt);
    fclose(f);

    ck_assert_int_eq(rc, ERR_IO);
}
END_TEST

Suite* fa_count_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("fa_count");
    
    tc_pos = tcase_create("pos");
    tcase_add_test(tc_pos, test_fa_count_one);
    tcase_add_test(tc_pos, test_fa_count_many);
    tcase_add_test(tc_pos, test_fa_count_none);

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("neg");
    tcase_add_test(tc_neg, test_fa_count_neg);

    suite_add_tcase(s, tc_neg);

    return s;
}

/// Корректный вывод и ввод массива
START_TEST(test_fa_io_pos_srtd)
{
    struct film_t films[3] = {
    { "aaa", "Bob", 2000},
    { "bbb", "Obo", 2007},
    { "ccc", "AAA", 2077}};
    size_t n = 3;

    FILE *f = fopen("./out/tmp", "w");
    fa_print(f, films, n);
    fclose(f);

    struct film_t *film_arr;
    size_t size;
    f = fopen("./out/tmp", "r");
    int rc = fa_create(f, &film_arr, &size);
    fclose(f);

    ck_assert_int_eq(rc, OK);
    ck_assert_uint_eq(size, n);
    ck_assert_int_eq(film_arr_eq(films, film_arr, n), ERR_OK);
    fa_free(film_arr, size);
}
END_TEST

/// Корректный вывод и ввод массива длины 1
START_TEST(test_fa_io_pos_one)
{
    struct film_t films[3] = {{ "aaa", "Bob", 2000}};
    size_t n = 1;

    FILE *f = fopen("./out/tmp", "w");
    fa_print(f, films, n);
    fclose(f);

    struct film_t *film_arr;
    size_t size;
    f = fopen("./out/tmp", "r");
    int rc = fa_create(f, &film_arr, &size);
    fclose(f);

    ck_assert_int_eq(rc, OK);
    ck_assert_uint_eq(size, n);
    ck_assert_int_eq(film_arr_eq(films, film_arr, n), ERR_OK);
    fa_free(film_arr, size);
}
END_TEST

/// Некорректный вывод и ввод массива
START_TEST(test_fa_io_neg)
{
    struct film_t films[3] = {
    { "aaa", "Bob", 2000},
    { "bbb", "Obo", 2007},
    { "ccc", "AAA", 2077}};;
    size_t n = 3;

    FILE *f = fopen("./out/tmp", "w");
    fa_print(f, films, n);
    fprintf(f, "ba\nbb\n\bc\n");
    fclose(f);

    struct film_t *film_arr;
    size_t size;
    f = fopen("./out/tmp", "r");
    int rc = fa_create(f, &film_arr, &size);
    fclose(f);

    ck_assert_int_eq(rc, ERR_IO);
}
END_TEST

Suite* fa_io_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("fa_io");

    tc_pos = tcase_create("pos");
    tcase_add_test(tc_pos, test_fa_io_pos_srtd);
    tcase_add_test(tc_pos, test_fa_io_pos_one);

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("neg");
    tcase_add_test(tc_pos, test_fa_io_neg);

    suite_add_tcase(s, tc_neg);

    return s;
}
