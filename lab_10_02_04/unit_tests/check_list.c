#include <check.h>
#include <stdio.h>
#include "list.h"
#include "err.h"
#include "check_func.h"

/// Тест для добавления узла в конец пустого списка
START_TEST(test_list_add_tail_empty)
{
    node_t *head = NULL;
    node_t *new_node = node_create(0, 0);
    head = list_add_tail(head, new_node);

    ck_assert_ptr_eq(head, new_node);

    list_free(head);
}
END_TEST

/// Тест для добавления узла в конец непустого списка
START_TEST(test_list_add_tail_nonempty)
{
    node_t *head = node_create(0, 0);
    node_t *node1 = node_create(0, 0);
    node_t *node2 = node_create(0, 0);
    
    head->next = node1;
    node1->next = node2;

    node_t *new_node = node_create(0, 0);
    head = list_add_tail(head, new_node);

    ck_assert_ptr_eq(head->next->next->next, new_node);

    list_free(head);
}
END_TEST

Suite* list_add_tail_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("list_add_tail");

    core = tcase_create("pos");
    tcase_add_test(core, test_list_add_tail_empty);
    tcase_add_test(core, test_list_add_tail_nonempty);

    suite_add_tcase(s, core);

    return s;
}

/// Простое число
START_TEST(test_init_list_from_num_prime)
{
    int num = 13;
    int facts[N_MAX][FACT_CHARS] = {{13, 1}};
    size_t n = 1;
    node_t *head;

    int rc = init_list_from_num(&head, num);
    ck_assert_int_eq(rc, OK);

    ck_assert_int_eq(fact_arr_eq_list(facts, n, head), ERR_OK);
    list_free(head);
}
END_TEST

/// Число с двумя множителями
START_TEST(test_init_list_from_num_two)
{
    int num = 12;
    int facts[N_MAX][FACT_CHARS] = {{2, 2}, {3, 1}};
    size_t n = 2;
    node_t *head;

    int rc = init_list_from_num(&head, num);
    ck_assert_int_eq(rc, OK);

    ck_assert_int_eq(fact_arr_eq_list(facts, n, head), ERR_OK);
    list_free(head);
}
END_TEST

/// Число с многими множителями
START_TEST(test_init_list_from_num_many)
{
    int num = 42;
    int facts[N_MAX][FACT_CHARS] = {{2, 1}, {3, 1}, {7, 1}};
    size_t n = 3;
    node_t *head;

    int rc = init_list_from_num(&head, num);
    ck_assert_int_eq(rc, OK);

    ck_assert_int_eq(fact_arr_eq_list(facts, n, head), ERR_OK);
    list_free(head);
}
END_TEST

Suite* init_list_from_num_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("init_list_from_num");

    core = tcase_create("pos");
    tcase_add_test(core, test_init_list_from_num_prime);
    tcase_add_test(core, test_init_list_from_num_two);
    tcase_add_test(core, test_init_list_from_num_many);

    suite_add_tcase(s, core);

    return s;
}

/// Простое число
START_TEST(test_get_num_from_list_prime)
{
    int num = 13;
    node_t *head;

    int rc = init_list_from_num(&head, num);
    ck_assert_int_eq(rc, OK);

    ck_assert_int_eq(get_num_from_list(head), num);
    list_free(head);
}
END_TEST

/// Число с двумя множителями
START_TEST(test_get_num_from_list_two)
{
    int num = 12;
    node_t *head;

    int rc = init_list_from_num(&head, num);
    ck_assert_int_eq(rc, OK);

    ck_assert_int_eq(get_num_from_list(head), num);
    list_free(head);
}
END_TEST

/// Число с многими множителями
START_TEST(test_get_num_from_list_many)
{
    int num = 42;
    node_t *head;

    int rc = init_list_from_num(&head, num);
    ck_assert_int_eq(rc, OK);

    ck_assert_int_eq(get_num_from_list(head), num);
    list_free(head);
}
END_TEST

Suite* get_num_from_list_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("get_num_from_list");

    core = tcase_create("pos");
    tcase_add_test(core, test_get_num_from_list_prime);
    tcase_add_test(core, test_get_num_from_list_two);
    tcase_add_test(core, test_get_num_from_list_many);

    suite_add_tcase(s, core);

    return s;
}

/// Простое число
START_TEST(test_print_num_prime)
{
    int num = 13;
    int exp[N_MAX] = {13, 1, 1};
    size_t n = 3;
    int arr[N_MAX];
    node_t *head;

    int rc = init_list_from_num(&head, num);
    ck_assert_int_eq(rc, OK);
    
    FILE *f = fopen("./out/tmp", "w");
    print_num(f, head);
    fclose(f);

    f = fopen("./out/tmp", "r");
    read_int_arr(f, arr, n);
    fclose(f);

    ck_assert_int_eq(int_arr_eq(exp, arr, n), ERR_OK);
    list_free(head);
}
END_TEST

/// Число с двумя множителями
START_TEST(test_print_num_two)
{
    int num = 12;
    int exp[N_MAX] = {3, 1, 2, 2, 1};
    size_t n = 5;
    int arr[N_MAX];
    node_t *head;

    int rc = init_list_from_num(&head, num);
    ck_assert_int_eq(rc, OK);
    
    FILE *f = fopen("./out/tmp", "w");
    print_num(f, head);
    fclose(f);

    f = fopen("./out/tmp", "r");
    read_int_arr(f, arr, n);
    fclose(f);

    ck_assert_int_eq(int_arr_eq(exp, arr, n), ERR_OK);
    list_free(head);
}
END_TEST

/// Число с многими множителями
START_TEST(test_print_num_many)
{
    int num = 42;
    int exp[N_MAX] = {7, 1, 3, 1, 2, 1, 1};
    size_t n = 7;
    int arr[N_MAX];
    node_t *head;

    int rc = init_list_from_num(&head, num);
    ck_assert_int_eq(rc, OK);
    
    FILE *f = fopen("./out/tmp", "w");
    print_num(f, head);
    fclose(f);

    f = fopen("./out/tmp", "r");
    read_int_arr(f, arr, n);
    fclose(f);

    ck_assert_int_eq(int_arr_eq(exp, arr, n), ERR_OK);
    list_free(head);
}
END_TEST

Suite* print_num_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("print_num");

    core = tcase_create("pos");
    tcase_add_test(core, test_print_num_prime);
    tcase_add_test(core, test_print_num_two);
    tcase_add_test(core, test_print_num_many);

    suite_add_tcase(s, core);

    return s;
}
