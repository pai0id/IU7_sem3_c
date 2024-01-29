#include <check.h>
#include <stdio.h>
#include "film.h"

/// Запись и чтение корректной структуры
START_TEST(test_film_io_correct)
{
    struct film_t exp = {"aaa", "Bob", 2000};
    FILE *f = fopen("./out/tmp", "w");
    film_print(f, &exp);
    fclose(f);

    struct film_t film;
    film.title = NULL;
    film.name = NULL;
    film.year = 0;
    f = fopen("./out/tmp", "r");
    int rc = film_read(f, &film);
    fclose(f);

    ck_assert_int_eq(rc, OK);
    ck_assert_str_eq(exp.title, film.title);
    ck_assert_str_eq(exp.name, film.name);
    ck_assert_int_eq(exp.year, film.year);
    film_free_content(&film);
}
END_TEST

/// Отрицательный год
START_TEST(test_film_io_year_neg)
{
    struct film_t exp = {"aaa", "Bob", -2000};
    FILE *f = fopen("./out/tmp", "w");
    film_print(f, &exp);
    fclose(f);

    struct film_t film;
    film.title = NULL;
    film.name = NULL;
    film.year = 0;
    f = fopen("./out/tmp", "r");
    int rc = film_read(f, &film);
    fclose(f);

    ck_assert_int_eq(rc, ERR_RANGE);
}
END_TEST

/// Год равен 0
START_TEST(test_film_io_year_z)
{
    struct film_t exp = {"aaa", "Bob", 0};
    FILE *f = fopen("./out/tmp", "w");
    film_print(f, &exp);
    fclose(f);

    struct film_t film;
    film.title = NULL;
    film.name = NULL;
    film.year = 0;
    f = fopen("./out/tmp", "r");
    int rc = film_read(f, &film);
    fclose(f);

    ck_assert_int_eq(rc, ERR_RANGE);
}
END_TEST

/// Не хватает поля
START_TEST(test_film_io_no_year)
{
    struct film_t exp = {"aaa", "Bob", -2000};
    FILE *f = fopen("./out/tmp", "w");
    fprintf(f, "%s\n%s\n", exp.title, exp.name);
    fclose(f);

    struct film_t film;
    film.title = NULL;
    film.name = NULL;
    film.year = 0;
    f = fopen("./out/tmp", "r");
    int rc = film_read(f, &film);
    fclose(f);

    ck_assert_int_eq(rc, ERR_IO);
}
END_TEST

Suite* film_io_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("film_io");
    
    tc_pos = tcase_create("pos");
    tcase_add_test(tc_pos, test_film_io_correct);

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("neg");
    tcase_add_test(tc_neg, test_film_io_year_neg);
    tcase_add_test(tc_neg, test_film_io_year_z);
    tcase_add_test(tc_neg, test_film_io_no_year);

    suite_add_tcase(s, tc_neg);

    return s;
}

/// Сравнить по названию l>r
START_TEST(test_film_cmp_title_l_more_r)
{
    struct film_t l = {"Abba", "Bob", 2000};

    struct film_t r = {"Baab", "Bob", 2000};

    int cmp = film_cmp_by_title(&l, &r);

    ck_assert_int_lt(cmp, 0);
}
END_TEST

/// Сравнить по названию l==r
START_TEST(test_film_cmp_title_l_eq_r)
{
    struct film_t l = {"Abba", "Bob", 2000};

    struct film_t r = {"Abba", "Bob", 2000};

    int cmp = film_cmp_by_title(&l, &r);

    ck_assert_int_eq(cmp, 0);
}
END_TEST

/// Сравнить по названию l<r
START_TEST(test_film_cmp_title_l_less_r)
{
    struct film_t l = {"Baab", "Bob", 2000};

    struct film_t r = {"Abba", "Bob", 2000};

    int cmp = film_cmp_by_title(&l, &r);

    ck_assert_int_gt(cmp, 0);
}
END_TEST

Suite* film_cmp_title_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("film_cmp_title");
    
    core = tcase_create("tests");
    tcase_add_test(core, test_film_cmp_title_l_more_r);
    tcase_add_test(core, test_film_cmp_title_l_eq_r);
    tcase_add_test(core, test_film_cmp_title_l_less_r);

    suite_add_tcase(s, core);

    return s;
}
