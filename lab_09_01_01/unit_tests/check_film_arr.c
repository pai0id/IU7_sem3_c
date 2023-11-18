#include <check.h>
#include <stdio.h>
#include <string.h>
#include "film_arr.h"
#include <stdbool.h>

bool film_eq(struct film_t *l, struct film_t *r)
{
    return (strcmp(l->title, r->title) == 0) && (strcmp(l->name, r->name) == 0) && (l->year == r->year);
} 

/// Одна структура
START_TEST(test_fa_count_one)
{
    struct film_t exp;
    exp.title = "Metal gear";
    exp.name = "Bob";
    exp.year = 2000;
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
    struct film_t exp;
    exp.title = "Metal gear";
    exp.name = "Bob";
    exp.year = 2000;
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

/// Вставка в начало
START_TEST(test_film_insert_beg)
{
    struct film_t f1;
    f1.title = "Metal gear";
    f1.name = "Bob";
    f1.year = 2000;
    struct film_t f2;
    f2.title = "Numetal";
    f2.name = "Obo";
    f2.year = 2007;
    struct film_t add;
    add.title = "UUUU";
    add.name = "AAAAA";
    add.year = 2077;

    struct film_t films[3] = {f1, f2};
    size_t n = 2;

    int rc = film_insert(films, &n, &add, 0);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(film_eq(&add, &films[0]), true);
    ck_assert_int_eq(film_eq(&f1, &films[1]), true);
    ck_assert_int_eq(film_eq(&f2, &films[2]), true);
}
END_TEST

/// Вставка в середину
START_TEST(test_film_insert_mid)
{
    struct film_t f1;
    f1.title = "Metal gear";
    f1.name = "Bob";
    f1.year = 2000;
    struct film_t f2;
    f2.title = "Numetal";
    f2.name = "Obo";
    f2.year = 2007;
    struct film_t add;
    add.title = "UUUU";
    add.name = "AAAAA";
    add.year = 2077;

    struct film_t films[3] = {f1, f2};
    size_t n = 2;

    int rc = film_insert(films, &n, &add, 1);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(film_eq(&f1, &films[0]), true);
    ck_assert_int_eq(film_eq(&add, &films[1]), true);
    ck_assert_int_eq(film_eq(&f2, &films[2]), true);
}
END_TEST

/// Вставка в конец
START_TEST(test_film_insert_end)
{
    struct film_t f1;
    f1.title = "Metal gear";
    f1.name = "Bob";
    f1.year = 2000;
    struct film_t f2;
    f2.title = "Numetal";
    f2.name = "Obo";
    f2.year = 2007;
    struct film_t add;
    add.title = "UUUU";
    add.name = "AAAAA";
    add.year = 2077;

    struct film_t films[3] = {f1, f2};
    size_t n = 2;

    int rc = film_insert(films, &n, &add, 2);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(film_eq(&f1, &films[0]), true);
    ck_assert_int_eq(film_eq(&f2, &films[1]), true);
    ck_assert_int_eq(film_eq(&add, &films[2]), true);
}
END_TEST

/// Вставка в пустой массив
START_TEST(test_film_insert_empt)
{
    struct film_t add;
    add.title = "UUUU";
    add.name = "AAAAA";
    add.year = 2077;

    struct film_t films[3];
    size_t n = 0;

    int rc = film_insert(films, &n, &add, 0);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(film_eq(&add, &films[0]), true);
}
END_TEST

/// Некорректный индекс
START_TEST(test_film_insert_neg)
{
    struct film_t f1;
    f1.title = "Metal gear";
    f1.name = "Bob";
    f1.year = 2000;
    struct film_t f2;
    f2.title = "Numetal";
    f2.name = "Obo";
    f2.year = 2007;
    struct film_t add;
    add.title = "UUUU";
    add.name = "AAAAA";
    add.year = 2077;

    struct film_t films[3];
    size_t n = 2;
    films[0] = f1;
    films[1] = f2;

    int rc = film_insert(films, &n, &add, 12);

    ck_assert_int_eq(rc, ERR_RANGE);
}
END_TEST

Suite* film_insert_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("film_insert");
    
    tc_pos = tcase_create("pos");
    tcase_add_test(tc_pos, test_film_insert_beg);
    tcase_add_test(tc_pos, test_film_insert_mid);
    tcase_add_test(tc_pos, test_film_insert_end);
    tcase_add_test(tc_pos, test_film_insert_empt);

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("neg");
    tcase_add_test(tc_neg, test_film_insert_neg);

    suite_add_tcase(s, tc_neg);

    return s;
}

/// Позиция в начале
START_TEST(test_find_pos_beg)
{
    struct film_t f1;
    f1.title = "bbb";
    f1.name = "Bob";
    f1.year = 2000;
    struct film_t f2;
    f2.title = "ccc";
    f2.name = "Obo";
    f2.year = 2007;
    struct film_t add;
    add.title = "aaa";
    add.name = "AAAAA";
    add.year = 2077;

    struct film_t films[3] = {f1, f2};
    size_t n = 2;

    size_t pos = find_pos(n, films, &add, film_cmp_by_title);

    ck_assert_uint_eq(pos, 0);
}
END_TEST

/// Позиция в середине
START_TEST(test_find_pos_mid)
{
    struct film_t f1;
    f1.title = "aaa";
    f1.name = "Bob";
    f1.year = 2000;
    struct film_t f2;
    f2.title = "ccc";
    f2.name = "Obo";
    f2.year = 2007;
    struct film_t add;
    add.title = "bbb";
    add.name = "AAAAA";
    add.year = 2077;

    struct film_t films[3] = {f1, f2};
    size_t n = 2;

    size_t pos = find_pos(n, films, &add, film_cmp_by_title);

    ck_assert_uint_eq(pos, 1);
}
END_TEST

/// Позиция в конце
START_TEST(test_find_pos_end)
{
    struct film_t f1;
    f1.title = "aaa";
    f1.name = "Bob";
    f1.year = 2000;
    struct film_t f2;
    f2.title = "bbb";
    f2.name = "Obo";
    f2.year = 2007;
    struct film_t add;
    add.title = "ccc";
    add.name = "AAAAA";
    add.year = 2077;

    struct film_t films[3] = {f1, f2};
    size_t n = 2;

    size_t pos = find_pos(n, films, &add, film_cmp_by_title);

    ck_assert_uint_eq(pos, 2);
}
END_TEST

Suite* find_pos_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("find_pos");
    
    core = tcase_create("tests");
    tcase_add_test(core, test_find_pos_beg);
    tcase_add_test(core, test_find_pos_mid);
    tcase_add_test(core, test_find_pos_end);

    suite_add_tcase(s, core);

    return s;
}

/// Необходимая структура есть
START_TEST(test_bin_search_by_field_pos)
{
    struct film_t f1;
    f1.title = "aaa";
    f1.name = "Bob";
    f1.year = 2000;
    struct film_t f2;
    f2.title = "bbb";
    f2.name = "Obo";
    f2.year = 2007;
    struct film_t f3;
    f3.title = "ccc";
    f3.name = "AAAAA";
    f3.year = 2077;

    struct film_t key;
    key.title = "bbb";
    key.name = NULL;
    key.year = 0;

    struct film_t films[3] = {f1, f2, f3};
    size_t n = 3;

    struct film_t res;

    int rc = bin_search_by_field(films, &res, n, &key, film_cmp_by_title);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(film_eq(&res, &f2), true);
}
END_TEST

/// Необходимой структуры нет
START_TEST(test_bin_search_by_field_neg)
{
    struct film_t f1;
    f1.title = "aaa";
    f1.name = "Bob";
    f1.year = 2000;
    struct film_t f2;
    f2.title = "bbb";
    f2.name = "Obo";
    f2.year = 2007;
    struct film_t f3;
    f3.title = "ccc";
    f3.name = "AAAAA";
    f3.year = 2077;

    struct film_t key;
    key.title = "bb";
    key.name = NULL;
    key.year = 0;

    struct film_t films[3] = {f1, f2, f3};
    size_t n = 3;

    struct film_t res;

    int rc = bin_search_by_field(films, &res, n, &key, film_cmp_by_title);

    ck_assert_int_eq(rc, ERR_NOT_FOUND);
}
END_TEST

Suite* bin_search_by_field_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("bin_search_by_field");
    
    tc_pos = tcase_create("pos");
    tcase_add_test(tc_pos, test_bin_search_by_field_pos);

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("neg");
    tcase_add_test(tc_neg, test_bin_search_by_field_neg);

    suite_add_tcase(s, tc_neg);

    return s;
}

/// Корректный вывод и ввод отсортированного массива
START_TEST(test_fa_io_pos_srtd)
{
    struct film_t f1;
    f1.title = "aaa";
    f1.name = "Bob";
    f1.year = 2000;
    struct film_t f2;
    f2.title = "bbb";
    f2.name = "Obo";
    f2.year = 2007;
    struct film_t f3;
    f3.title = "ccc";
    f3.name = "AAAAA";
    f3.year = 2077;

    struct film_t films[3] = {f1, f2, f3};
    size_t n = 3;

    FILE *f = fopen("./out/tmp", "w");
    fa_print(f, films, n);
    fclose(f);

    struct film_t *film_arr;
    size_t size;
    f = fopen("./out/tmp", "r");
    int rc = fa_create(f, &film_arr, &size, film_cmp_by_title);
    fclose(f);

    ck_assert_int_eq(rc, OK);
    ck_assert_uint_eq(size, n);
    ck_assert_int_eq(film_eq(&films[0], &film_arr[0]), true);
    ck_assert_int_eq(film_eq(&films[1], &film_arr[1]), true);
    ck_assert_int_eq(film_eq(&films[2], &film_arr[2]), true);
    fa_free(film_arr, size);
}
END_TEST

/// Корректный вывод и ввод нетсортированного массива
START_TEST(test_fa_io_pos_usrtd)
{
    struct film_t f1;
    f1.title = "bbb";
    f1.name = "Obo";
    f1.year = 2007;
    struct film_t f2;
    f2.title = "ccc";
    f2.name = "AAAAA";
    f2.year = 2077;
    struct film_t f3;
    f3.title = "aaa";
    f3.name = "Bob";
    f3.year = 2000;

    struct film_t films[3] = {f1, f2, f3};
    size_t n = 3;

    FILE *f = fopen("./out/tmp", "w");
    fa_print(f, films, n);
    fclose(f);

    struct film_t *film_arr;
    size_t size;
    f = fopen("./out/tmp", "r");
    int rc = fa_create(f, &film_arr, &size, film_cmp_by_title);
    fclose(f);

    ck_assert_int_eq(rc, OK);
    ck_assert_uint_eq(size, n);
    ck_assert_int_eq(film_eq(&films[2], &film_arr[0]), true);
    ck_assert_int_eq(film_eq(&films[0], &film_arr[1]), true);
    ck_assert_int_eq(film_eq(&films[1], &film_arr[2]), true);
    fa_free(film_arr, size);
}
END_TEST

/// Корректный вывод и ввод массива длины 1
START_TEST(test_fa_io_pos_one)
{
    struct film_t f1;
    f1.title = "bbb";
    f1.name = "Obo";
    f1.year = 2007;

    struct film_t films[3];
    size_t n = 1;
    films[0] = f1;

    FILE *f = fopen("./out/tmp", "w");
    fa_print(f, films, n);
    fclose(f);

    struct film_t *film_arr;
    size_t size;
    f = fopen("./out/tmp", "r");
    int rc = fa_create(f, &film_arr, &size, film_cmp_by_title);
    fclose(f);

    ck_assert_int_eq(rc, OK);
    ck_assert_uint_eq(size, n);
    ck_assert_int_eq(film_eq(&films[0], &film_arr[0]), true);
    fa_free(film_arr, size);
}
END_TEST

/// Корректный вывод и ввод нетсортированного массива с повторами
START_TEST(test_fa_io_pos_rep)
{
    struct film_t f1;
    f1.title = "bbb";
    f1.name = "Obo";
    f1.year = 2007;
    struct film_t f2;
    f2.title = "ccc";
    f2.name = "AAAAA";
    f2.year = 2077;
    struct film_t f3;
    f3.title = "bbb";
    f3.name = "Bob";
    f3.year = 2000;

    struct film_t films[3] = {f1, f2, f3};
    size_t n = 3;

    FILE *f = fopen("./out/tmp", "w");
    fa_print(f, films, n);
    fclose(f);

    struct film_t *film_arr;
    size_t size;
    f = fopen("./out/tmp", "r");
    int rc = fa_create(f, &film_arr, &size, film_cmp_by_title);
    fclose(f);

    ck_assert_int_eq(rc, OK);
    ck_assert_uint_eq(size, n);
    ck_assert_int_eq(film_eq(&films[0], &film_arr[0]), true);
    ck_assert_int_eq(film_eq(&films[2], &film_arr[1]), true);
    ck_assert_int_eq(film_eq(&films[1], &film_arr[2]), true);
    fa_free(film_arr, size);
}
END_TEST

/// Некорректный вывод и ввод массива
START_TEST(test_fa_io_neg)
{
    struct film_t f1;
    f1.title = "aaa";
    f1.name = "Bob";
    f1.year = 2000;
    struct film_t f2;
    f2.title = "bbb";
    f2.name = "Obo";
    f2.year = 2007;
    struct film_t f3;
    f3.title = "ccc";
    f3.name = "AAAAA";
    f3.year = 2077;

    struct film_t films[3] = {f1, f2, f3};
    size_t n = 3;

    FILE *f = fopen("./out/tmp", "w");
    fa_print(f, films, n);
    fprintf(f, "ba\nbb\n\bc\n");
    fclose(f);

    struct film_t *film_arr;
    size_t size;
    f = fopen("./out/tmp", "r");
    int rc = fa_create(f, &film_arr, &size, film_cmp_by_title);
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
    tcase_add_test(tc_pos, test_fa_io_pos_usrtd);
    tcase_add_test(tc_pos, test_fa_io_pos_one);
    tcase_add_test(tc_pos, test_fa_io_pos_rep);

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("neg");
    tcase_add_test(tc_pos, test_fa_io_neg);

    suite_add_tcase(s, tc_neg);

    return s;
}
