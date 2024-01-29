#include <check.h>
#include <stdio.h>
#include <stdbool.h>
#include "task_funcs.h"
#include "check_func.h"

/// Тест создания списка из массива из нескольких фильмов
START_TEST(test_init_list_from_film_arr_many)
{
    struct film_t film_arr[N_MAX] = {
    { "aaa", "Bob", 2000},
    { "bbb", "Obo", 2007},
    { "ccc", "AAA", 2077}};
    size_t n = 3;
    node_t *head;

    int rc = init_list_from_film_arr(&head, film_arr, n);
    ck_assert_int_eq(rc, OK);

    ck_assert_int_eq(film_arr_eq_list(film_arr, n, head), ERR_OK);
    list_free(head);
}
END_TEST

/// Тест создания списка из массива из одного фильма
START_TEST(test_init_list_from_film_arr_one)
{
    struct film_t film_arr[N_MAX] = {
    { "aaa", "Bob", 2000}};
    size_t n = 1;
    node_t *head;

    int rc = init_list_from_film_arr(&head, film_arr, n);
    ck_assert_int_eq(rc, OK);

    ck_assert_int_eq(film_arr_eq_list(film_arr, n, head), ERR_OK);
    list_free(head);
}
END_TEST

/// Тест создания списка из пустого массива
START_TEST(test_init_list_from_film_arr_none)
{
    struct film_t film_arr[N_MAX];
    size_t n = 0;
    node_t *head;

    int rc = init_list_from_film_arr(&head, film_arr, n);
    ck_assert_int_eq(rc, OK);

    ck_assert_ptr_null(head);
    list_free(head);
}
END_TEST

Suite* init_list_from_film_arr_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("init_list_from_film_arr");

    core = tcase_create("pos");
    tcase_add_test(core, test_init_list_from_film_arr_many);
    tcase_add_test(core, test_init_list_from_film_arr_one);
    tcase_add_test(core, test_init_list_from_film_arr_none);

    suite_add_tcase(s, core);

    return s;
}