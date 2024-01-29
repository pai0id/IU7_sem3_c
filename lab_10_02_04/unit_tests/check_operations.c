#include <check.h>
#include <stdio.h>
#include "list.h"
#include "operations.h"
#include "err.h"
#include "check_func.h"

/// Числа с несовпадающими множителями
START_TEST(test_mul_nums_dif)
{
    int num1 = 13, num2 = 12;
    int exp[N_MAX][FACT_CHARS] = {{2, 2}, {3, 1}, {13, 1}};
    size_t n = 3;
    node_t *head1, *head2;

    int rc = init_list_from_num(&head1, num1);
    ck_assert_int_eq(rc, OK);

    rc = init_list_from_num(&head2, num2);
    ck_assert_int_eq(rc, OK);

    node_t *res = mul_nums(head1, head2);

    ck_assert_int_eq(fact_arr_eq_list(exp, n, res), ERR_OK);
    
    list_free(head1);
    list_free(head2);
    list_free(res);
}
END_TEST

/// Числа с совпадающими множителями
START_TEST(test_mul_nums_same)
{
    int num1 = 6, num2 = 12;
    int exp[N_MAX][FACT_CHARS] = {{2, 3}, {3, 2}};
    size_t n = 2;
    node_t *head1, *head2;

    int rc = init_list_from_num(&head1, num1);
    ck_assert_int_eq(rc, OK);

    rc = init_list_from_num(&head2, num2);
    ck_assert_int_eq(rc, OK);

    node_t *res = mul_nums(head1, head2);

    ck_assert_int_eq(fact_arr_eq_list(exp, n, res), ERR_OK);
    
    list_free(head1);
    list_free(head2);
    list_free(res);
}
END_TEST

Suite* mul_nums_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("mul_nums");

    core = tcase_create("pos");
    tcase_add_test(core, test_mul_nums_dif);
    tcase_add_test(core, test_mul_nums_same);

    suite_add_tcase(s, core);

    return s;
}

/// Число с одним множителем
START_TEST(test_sqr_num_one)
{
    int num = 13;
    int exp[N_MAX][FACT_CHARS] = {{13, 2}};
    size_t n = 1;
    node_t *head;

    int rc = init_list_from_num(&head, num);
    ck_assert_int_eq(rc, OK);

    node_t *res = sqr_num(head);

    ck_assert_int_eq(fact_arr_eq_list(exp, n, res), ERR_OK);
    
    list_free(head);
    list_free(res);
}
END_TEST

/// Числа с несколькими множителями
START_TEST(test_sqr_num_many)
{
    int num = 12;
    int exp[N_MAX][FACT_CHARS] = {{2, 4}, {3, 2}};
    size_t n = 2;
    node_t *head;

    int rc = init_list_from_num(&head, num);
    ck_assert_int_eq(rc, OK);

    node_t *res = sqr_num(head);

    ck_assert_int_eq(fact_arr_eq_list(exp, n, res), ERR_OK);
    
    list_free(head);
    list_free(res);
}
END_TEST

Suite* sqr_num_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("sqr_num");

    core = tcase_create("pos");
    tcase_add_test(core, test_sqr_num_one);
    tcase_add_test(core, test_sqr_num_many);

    suite_add_tcase(s, core);

    return s;
}

/// Числа с несовпадающими множителями
START_TEST(test_reduce_nums_dif)
{
    int num1 = 13, num2 = 12;
    int exp1[N_MAX][FACT_CHARS] = {{13, 1}};
    size_t n1 = 1;
    int exp2[N_MAX][FACT_CHARS] = {{2, 2}, {3, 1}};
    size_t n2 = 2;
    node_t *head1, *head2;
    node_t *new1, *new2;

    int rc = init_list_from_num(&head1, num1);
    ck_assert_int_eq(rc, OK);

    rc = init_list_from_num(&head2, num2);
    ck_assert_int_eq(rc, OK);

    rc = reduce_nums(head1, head2, &new1, &new2);

    ck_assert_int_eq(fact_arr_eq_list(exp1, n1, new1), ERR_OK);
    ck_assert_int_eq(fact_arr_eq_list(exp2, n2, new2), ERR_OK);
    
    list_free(head1);
    list_free(head2);
    list_free(new1);
    list_free(new2);
}
END_TEST

/// Числа с совпадающими множителями
START_TEST(test_reduce_nums_same)
{
    int num1 = 8, num2 = 12;
    int exp1[N_MAX][FACT_CHARS] = {{2, 1}};
    size_t n1 = 1;
    int exp2[N_MAX][FACT_CHARS] = {{3, 1}};
    size_t n2 = 1;
    node_t *head1, *head2;
    node_t *new1, *new2;

    int rc = init_list_from_num(&head1, num1);
    ck_assert_int_eq(rc, OK);

    rc = init_list_from_num(&head2, num2);
    ck_assert_int_eq(rc, OK);

    rc = reduce_nums(head1, head2, &new1, &new2);

    ck_assert_int_eq(fact_arr_eq_list(exp1, n1, new1), ERR_OK);
    ck_assert_int_eq(fact_arr_eq_list(exp2, n2, new2), ERR_OK);
    
    list_free(head1);
    list_free(head2);
    list_free(new1);
    list_free(new2);
}
END_TEST

Suite* reduce_nums_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("reduce_nums");

    core = tcase_create("pos");
    tcase_add_test(core, test_reduce_nums_dif);
    tcase_add_test(core, test_reduce_nums_same);

    suite_add_tcase(s, core);

    return s;
}

/// Результат равен 0
START_TEST(test_div_nums_null)
{
    int num1 = 13, num2 = 12;
    node_t *head1, *head2;

    int rc = init_list_from_num(&head1, num1);
    ck_assert_int_eq(rc, OK);

    rc = init_list_from_num(&head2, num2);
    ck_assert_int_eq(rc, OK);

    node_t *res = div_nums(head1, head2);

    ck_assert_ptr_null(res);
    
    list_free(head1);
    list_free(head2);
}
END_TEST

/// Остатка нет
START_TEST(test_div_nums_no_rem)
{
    int num1 = 12, num2 = 6;
    int exp[N_MAX][FACT_CHARS] = {{2, 1}};
    size_t n = 1;
    node_t *head1, *head2;

    int rc = init_list_from_num(&head1, num1);
    ck_assert_int_eq(rc, OK);

    rc = init_list_from_num(&head2, num2);
    ck_assert_int_eq(rc, OK);

    node_t *res = div_nums(head1, head2);

    ck_assert_int_eq(fact_arr_eq_list(exp, n, res), ERR_OK);
    
    list_free(head1);
    list_free(head2);
    list_free(res);
}
END_TEST

/// Остаток есть
START_TEST(test_div_nums_yes_rem)
{
    int num1 = 12, num2 = 5;
    int exp[N_MAX][FACT_CHARS] = {{2, 1}};
    size_t n = 1;
    node_t *head1, *head2;

    int rc = init_list_from_num(&head1, num1);
    ck_assert_int_eq(rc, OK);

    rc = init_list_from_num(&head2, num2);
    ck_assert_int_eq(rc, OK);

    node_t *res = div_nums(head1, head2);

    ck_assert_int_eq(fact_arr_eq_list(exp, n, res), ERR_OK);
    
    list_free(head1);
    list_free(head2);
    list_free(res);
}
END_TEST

Suite* div_nums_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("div_nums");

    core = tcase_create("pos");
    tcase_add_test(core, test_div_nums_null);
    tcase_add_test(core, test_div_nums_no_rem);
    tcase_add_test(core, test_div_nums_yes_rem);

    suite_add_tcase(s, core);

    return s;
}
