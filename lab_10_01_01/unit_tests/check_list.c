#include <check.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#include "check_func.h"

/// Тест для добавления узла в конец пустого списка
START_TEST(test_list_add_tail_empty)
{
    node_t *head = NULL;
    node_t *new_node = node_create(NULL);
    head = list_add_tail(head, new_node);

    ck_assert_ptr_eq(head, new_node);

    list_free(head);
}
END_TEST

/// Тест для добавления узла в конец непустого списка
START_TEST(test_list_add_tail_nonempty)
{
    node_t *head = node_create(NULL);
    node_t *node1 = node_create(NULL);
    node_t *node2 = node_create(NULL);
    
    head->next = node1;
    node1->next = node2;

    node_t *new_node = node_create(NULL);
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

/// Тест печати списка из нескольких элементов
START_TEST(test_list_print_many)
{
    int arr[N_MAX] = {1, 2, 3};
    size_t n = 3;

    node_t *head;
    ck_assert_int_eq(init_list_from_int_arr(&head, arr, n), ERR_OK);

    FILE *f = fopen("./out/tmp", "w");
    list_print(f, head, print_int);
    fclose(f);

    int res[N_MAX];
    f = fopen("./out/tmp", "r");
    ck_assert_int_eq(read_int_arr(f, res, n), ERR_OK);
    fclose(f);

    ck_assert_int_eq(int_arr_eq_list(res, n, head), ERR_OK);
    list_free(head);
}
END_TEST

/// Тест печати списка из одного элемента
START_TEST(test_list_print_one)
{
    int arr[N_MAX] = {1};
    size_t n = 1;

    node_t *head;
    ck_assert_int_eq(init_list_from_int_arr(&head, arr, n), ERR_OK);

    FILE *f = fopen("./out/tmp", "w");
    list_print(f, head, print_int);
    fclose(f);

    int res[N_MAX];
    f = fopen("./out/tmp", "r");
    ck_assert_int_eq(read_int_arr(f, res, n), ERR_OK);
    fclose(f);

    ck_assert_int_eq(int_arr_eq_list(res, n, head), ERR_OK);
    list_free(head);
}
END_TEST

Suite* list_print_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("list_print");

    core = tcase_create("pos");
    tcase_add_test(core, test_list_print_one);
    tcase_add_test(core, test_list_print_many);

    suite_add_tcase(s, core);

    return s;
}

/// Тест для поиска узла в непустом списке в начале
START_TEST(test_find_nonempty_list_beg)
{
    int arr[N_MAX] = {1, 2, 3};
    size_t n = 3;

    node_t *head;
    ck_assert_int_eq(init_list_from_int_arr(&head, arr, n), ERR_OK);

    int x = 1;
    node_t *res = find(head, &x, cmp_int);

    ck_assert_ptr_eq(res, head);

    list_free(head);
}
END_TEST

/// Тест для поиска узла в непустом списке в конце
START_TEST(test_find_nonempty_list_end)
{
    int arr[N_MAX] = {1, 2, 3};
    size_t n = 3;

    node_t *head;
    ck_assert_int_eq(init_list_from_int_arr(&head, arr, n), ERR_OK);

    int x = 2;
    node_t *res = find(head, &x, cmp_int);

    ck_assert_ptr_eq(res, head->next);

    list_free(head);
}
END_TEST

/// Тест для поиска узла в непустом списке в середине
START_TEST(test_find_nonempty_list_mid)
{
    int arr[N_MAX] = {1, 2, 3};
    size_t n = 3;

    node_t *head;
    ck_assert_int_eq(init_list_from_int_arr(&head, arr, n), ERR_OK);

    int x = 3;
    node_t *res = find(head, &x, cmp_int);

    ck_assert_ptr_eq(res, head->next->next);

    list_free(head);
}
END_TEST

/// Тест для поиска узла в списке длины 1
START_TEST(test_find_nonempty_list_one)
{
    int arr[N_MAX] = {1};
    size_t n = 1;

    node_t *head;
    ck_assert_int_eq(init_list_from_int_arr(&head, arr, n), ERR_OK);

    int x = 1;
    node_t *res = find(head, &x, cmp_int);

    ck_assert_ptr_eq(res, head);

    list_free(head);
}
END_TEST

/// Тест для поиска узла в пустом списке
START_TEST(test_find_empty_list)
{
    node_t *head = NULL;

    int x = 42;
    node_t *res = find(head, &x, cmp_int);

    ck_assert_ptr_null(res);
}
END_TEST

Suite* find_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("find");

    tc_pos = tcase_create("pos");
    tcase_add_test(tc_pos, test_find_nonempty_list_beg);
    tcase_add_test(tc_pos, test_find_nonempty_list_end);
    tcase_add_test(tc_pos, test_find_nonempty_list_mid);
    tcase_add_test(tc_pos, test_find_nonempty_list_one);

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("neg");
    tcase_add_test(tc_pos, test_find_empty_list);

    suite_add_tcase(s, tc_neg);

    return s;
}

/// Тест для вставки узла в непустом списке в начале
START_TEST(test_insert_nonempty_list_beg)
{
    int arr[N_MAX] = {1, 2, 3};
    int el = 0;
    size_t n = 3;
    int exp[N_MAX] = {0, 1, 2, 3};
    size_t n_exp = 4;

    node_t *head;
    ck_assert_int_eq(init_list_from_int_arr(&head, arr, n), ERR_OK);

    node_t *elem = node_create(&el);
    ck_assert_ptr_nonnull(elem);

    insert(&head, elem, head);
    ck_assert_int_eq(int_arr_eq_list(exp, n_exp, head), ERR_OK);

    list_free(head);
}
END_TEST

/// Тест для вставки узла в непустом списке в середину
START_TEST(test_insert_nonempty_list_mid)
{
    int arr[N_MAX] = {1, 2, 3};
    int el = 0;
    size_t n = 3;
    int exp[N_MAX] = { 1, 0, 2, 3};
    size_t n_exp = 4;

    node_t *head;
    ck_assert_int_eq(init_list_from_int_arr(&head, arr, n), ERR_OK);

    node_t *elem = node_create(&el);
    ck_assert_ptr_nonnull(elem);

    insert(&head, elem, head->next);
    ck_assert_int_eq(int_arr_eq_list(exp, n_exp, head), ERR_OK);

    list_free(head);
}
END_TEST

/// Тест для вставки узла в непустом списке перед последним узлом
START_TEST(test_insert_nonempty_list_end)
{
    int arr[N_MAX] = {1, 2, 3};
    int el = 0;
    size_t n = 3;
    int exp[N_MAX] = { 1, 2, 0, 3};
    size_t n_exp = 4;

    node_t *head;
    ck_assert_int_eq(init_list_from_int_arr(&head, arr, n), ERR_OK);

    node_t *elem = node_create(&el);
    ck_assert_ptr_nonnull(elem);

    insert(&head, elem, head->next->next);
    ck_assert_int_eq(int_arr_eq_list(exp, n_exp, head), ERR_OK);

    list_free(head);
}
END_TEST

/// Тест для вставки узла в непустом списке длины 1
START_TEST(test_insert_nonempty_list_one)
{
    int arr[N_MAX] = {1};
    int el = 0;
    size_t n = 1;
    int exp[N_MAX] = {0, 1};
    size_t n_exp = 2;

    node_t *head;
    ck_assert_int_eq(init_list_from_int_arr(&head, arr, n), ERR_OK);

    node_t *elem = node_create(&el);
    ck_assert_ptr_nonnull(elem);

    insert(&head, elem, head);
    ck_assert_int_eq(int_arr_eq_list(exp, n_exp, head), ERR_OK);

    list_free(head);
}
END_TEST

Suite* insert_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("insert");

    core = tcase_create("pos");
    tcase_add_test(core, test_insert_nonempty_list_one);
    tcase_add_test(core, test_insert_nonempty_list_beg);
    tcase_add_test(core, test_insert_nonempty_list_end);
    tcase_add_test(core, test_insert_nonempty_list_mid);

    suite_add_tcase(s, core);

    return s;
}

/// Список с дупликатами
START_TEST(test_remove_duplicates_yes)
{
    int arr[N_MAX] = {1, 2, 2};
    size_t n = 3;
    int exp[N_MAX] = {1, 2};
    size_t n_exp = 2;

    node_t *head;
    ck_assert_int_eq(init_list_from_int_arr(&head, arr, n), ERR_OK);

    remove_duplicates(&head, cmp_int);
    ck_assert_int_eq(int_arr_eq_list(exp, n_exp, head), ERR_OK);

    list_free(head);
}
END_TEST

/// Список без дупликатов
START_TEST(test_remove_duplicates_no)
{
    int arr[N_MAX] = {1, 2, 3};
    size_t n = 3;
    int exp[N_MAX] = {1, 2, 3};
    size_t n_exp = 3;

    node_t *head;
    ck_assert_int_eq(init_list_from_int_arr(&head, arr, n), ERR_OK);

    remove_duplicates(&head, cmp_int);
    ck_assert_int_eq(int_arr_eq_list(exp, n_exp, head), ERR_OK);

    list_free(head);
}
END_TEST

Suite* remove_duplicates_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("remove_duplicates");

    core = tcase_create("pos");
    tcase_add_test(core, test_remove_duplicates_yes);
    tcase_add_test(core, test_remove_duplicates_no);

    suite_add_tcase(s, core);

    return s;
}

/// Список четной длины
START_TEST(test_front_back_split_even)
{
    int arr[N_MAX] = {1, 2, 3, 4, 5, 6};
    size_t n = 6;
    int exp1[N_MAX] = {1, 2, 3};
    size_t n_exp1 = 3;
    int exp2[N_MAX] = {4, 5, 6};
    size_t n_exp2 = 3;

    node_t *head;
    ck_assert_int_eq(init_list_from_int_arr(&head, arr, n), ERR_OK);
    node_t *back;

    front_back_split(head, &back);
    ck_assert_int_eq(int_arr_eq_list(exp1, n_exp1, head), ERR_OK);
    ck_assert_int_eq(int_arr_eq_list(exp2, n_exp2, back), ERR_OK);

    list_free(head);
    list_free(back);
}
END_TEST

/// Список нечетной длины
START_TEST(test_front_back_split_odd)
{
    int arr[N_MAX] = {1, 2, 3, 4, 5};
    size_t n = 5;
    int exp1[N_MAX] = {1, 2, 3};
    size_t n_exp1 = 3;
    int exp2[N_MAX] = {4, 5};
    size_t n_exp2 = 2;

    node_t *head;
    ck_assert_int_eq(init_list_from_int_arr(&head, arr, n), ERR_OK);
    node_t *back;

    front_back_split(head, &back);
    ck_assert_int_eq(int_arr_eq_list(exp1, n_exp1, head), ERR_OK);
    ck_assert_int_eq(int_arr_eq_list(exp2, n_exp2, back), ERR_OK);

    list_free(head);
    list_free(back);
}
END_TEST

/// Список длины 1
START_TEST(test_front_back_split_one)
{
    int arr[N_MAX] = {1};
    size_t n = 1;

    node_t *head;
    ck_assert_int_eq(init_list_from_int_arr(&head, arr, n), ERR_OK);
    node_t *back;

    front_back_split(head, &back);
    ck_assert_int_eq(int_arr_eq_list(arr, n, head), ERR_OK);
    ck_assert_ptr_null(back);

    list_free(head);
}
END_TEST

Suite* front_back_split_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("front_back_split");

    core = tcase_create("pos");
    tcase_add_test(core, test_front_back_split_one);
    tcase_add_test(core, test_front_back_split_odd);
    tcase_add_test(core, test_front_back_split_even);

    suite_add_tcase(s, core);

    return s;
}

/// Все элементы первого меньше второго
START_TEST(test_sorted_merge_sorted)
{
    int arr1[N_MAX] = {1, 2};
    size_t n1 = 2;
    int arr2[N_MAX] = {3, 4};
    size_t n2 = 2;
    int exp[N_MAX] = {1, 2, 3, 4};
    size_t n = 4;

    node_t *head1, *head2, *res;
    ck_assert_int_eq(init_list_from_int_arr(&head1, arr1, n1), ERR_OK);
    ck_assert_int_eq(init_list_from_int_arr(&head2, arr2, n2), ERR_OK);

    res = sorted_merge(&head1, &head2, cmp_int);

    ck_assert_ptr_null(head1);
    ck_assert_ptr_null(head2);
    ck_assert_int_eq(int_arr_eq_list(exp, n, res), ERR_OK);

    list_free(head1);
    list_free(head2);
    list_free(res);
}
END_TEST

/// Все элементы первого больше второго
START_TEST(test_sorted_merge_revsorted)
{
    int arr1[N_MAX] = {3, 4};
    size_t n1 = 2;
    int arr2[N_MAX] = {1, 2};
    size_t n2 = 2;
    int exp[N_MAX] = {1, 2, 3, 4};
    size_t n = 4;

    node_t *head1, *head2, *res;
    ck_assert_int_eq(init_list_from_int_arr(&head1, arr1, n1), ERR_OK);
    ck_assert_int_eq(init_list_from_int_arr(&head2, arr2, n2), ERR_OK);

    res = sorted_merge(&head1, &head2, cmp_int);

    ck_assert_ptr_null(head1);
    ck_assert_ptr_null(head2);
    ck_assert_int_eq(int_arr_eq_list(exp, n, res), ERR_OK);

    list_free(head1);
    list_free(head2);
    list_free(res);
}
END_TEST

/// Смешанные
START_TEST(test_sorted_merge_rnd)
{
    int arr1[N_MAX] = {1, 3};
    size_t n1 = 2;
    int arr2[N_MAX] = {2, 4};
    size_t n2 = 2;
    int exp[N_MAX] = {1, 2, 3, 4};
    size_t n = 4;

    node_t *head1, *head2, *res;
    ck_assert_int_eq(init_list_from_int_arr(&head1, arr1, n1), ERR_OK);
    ck_assert_int_eq(init_list_from_int_arr(&head2, arr2, n2), ERR_OK);

    res = sorted_merge(&head1, &head2, cmp_int);

    ck_assert_ptr_null(head1);
    ck_assert_ptr_null(head2);
    ck_assert_int_eq(int_arr_eq_list(exp, n, res), ERR_OK);

    list_free(head1);
    list_free(head2);
    list_free(res);
}
END_TEST

Suite* sorted_merge_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("sorted_merge");

    core = tcase_create("pos");
    tcase_add_test(core, test_sorted_merge_sorted);
    tcase_add_test(core, test_sorted_merge_revsorted);
    tcase_add_test(core, test_sorted_merge_rnd);

    suite_add_tcase(s, core);

    return s;
}

/// Список длины 1
START_TEST(test_sort_one)
{
    int arr[N_MAX] = {1};
    size_t n = 1;
    int exp[N_MAX] = {1};
    size_t n_exp = 1;

    node_t *head;
    ck_assert_int_eq(init_list_from_int_arr(&head, arr, n), ERR_OK);

    head = sort(head, cmp_int);
    ck_assert_int_eq(int_arr_eq_list(exp, n_exp, head), ERR_OK);

    list_free(head);
}
END_TEST

/// Отсортированный список
START_TEST(test_sort_sorted)
{
    int arr[N_MAX] = {1, 2, 3};
    size_t n = 3;
    int exp[N_MAX] = {1, 2, 3};
    size_t n_exp = 3;

    node_t *head;
    ck_assert_int_eq(init_list_from_int_arr(&head, arr, n), ERR_OK);

    head = sort(head, cmp_int);
    ck_assert_int_eq(int_arr_eq_list(exp, n_exp, head), ERR_OK);

    list_free(head);
}
END_TEST

/// Обратно отсортированный список
START_TEST(test_sort_revsorted)
{
    int arr[N_MAX] = {3, 2, 1};
    size_t n = 3;
    int exp[N_MAX] = {1, 2, 3};
    size_t n_exp = 3;

    node_t *head;
    ck_assert_int_eq(init_list_from_int_arr(&head, arr, n), ERR_OK);

    head = sort(head, cmp_int);
    ck_assert_int_eq(int_arr_eq_list(exp, n_exp, head), ERR_OK);

    list_free(head);
}
END_TEST

/// Неотсортированный список
START_TEST(test_sort_unsorted)
{
    int arr[N_MAX] = {3, 1, 2};
    size_t n = 3;
    int exp[N_MAX] = {1, 2, 3};
    size_t n_exp = 3;

    node_t *head;
    ck_assert_int_eq(init_list_from_int_arr(&head, arr, n), ERR_OK);

    head = sort(head, cmp_int);
    ck_assert_int_eq(int_arr_eq_list(exp, n_exp, head), ERR_OK);

    list_free(head);
}
END_TEST

Suite* sort_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("sort");

    core = tcase_create("pos");
    tcase_add_test(core, test_sort_one);
    tcase_add_test(core, test_sort_sorted);
    tcase_add_test(core, test_sort_unsorted);
    tcase_add_test(core, test_sort_revsorted);

    suite_add_tcase(s, core);

    return s;
}
