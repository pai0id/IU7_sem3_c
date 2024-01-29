#include "libmysort.h"
#include <check.h>

/// Тест сортировки одного элемента
START_TEST(test_mysort_int_one_element)
{
    int arr[] = {1};
    int expected[] = {1};
    size_t count = 1;

    mysort(arr, count, sizeof(arr[0]), int_cmp);

    for (size_t i = 0; i < count; ++i)
        ck_assert_int_eq(arr[i], expected[i]);
}
END_TEST

/// Тест сортировки двух элементов (уже отсортированных)
START_TEST(test_mysort_int_two_sorted)
{
    int arr[] = {1, 2};
    int expected[] = {1, 2};
    size_t count = 2;

    mysort(arr, count, sizeof(arr[0]), int_cmp);

    for (size_t i = 0; i < count; ++i)
        ck_assert_int_eq(arr[i], expected[i]);
}
END_TEST

/// Тест сортировки двух элементов (не отсортированных)
START_TEST(test_mysort_int_two_unsorted)
{
    int arr[] = {2, 1};
    int expected[] = {1, 2};
    size_t count = 2;

    mysort(arr, count, sizeof(arr[0]), int_cmp);

    for (size_t i = 0; i < count; ++i)
        ck_assert_int_eq(arr[i], expected[i]);
}
END_TEST

/// Тест сортировки уже отсортированного массива
START_TEST(test_mysort_int_sorted)
{
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    size_t count = 5;

    mysort(arr, count, sizeof(arr[0]), int_cmp);

    for (size_t i = 0; i < count; ++i)
        ck_assert_int_eq(arr[i], expected[i]);
}
END_TEST

/// Тест сортировки в обратном порядке
START_TEST(test_mysort_int_reversed)
{
    int arr[] = {5, 4, 3, 2, 1};
    int expected[] = {1, 2, 3, 4, 5};
    size_t count = 5;

    mysort(arr, count, sizeof(arr[0]), int_cmp);

    for (size_t i = 0; i < count; ++i)
        ck_assert_int_eq(arr[i], expected[i]);
}
END_TEST

/// Тест сортировки случайного массива без одинаковых элементов
START_TEST(test_mysort_int_random_no_same)
{
    int arr[] = {5, 2, 3, 4, 1};
    int expected[] = {1, 2, 3, 4, 5};
    size_t count = 5;

    mysort(arr, count, sizeof(arr[0]), int_cmp);

    for (size_t i = 0; i < count; ++i)
        ck_assert_int_eq(arr[i], expected[i]);
}
END_TEST

/// Тест сортировки случайного массива с одинаковыми элементами
START_TEST(test_mysort_int_random_yes_same)
{
    int arr[] = {5, 2, 3, 2, 1};
    int expected[] = {1, 2, 2, 3, 5};
    size_t count = 5;

    mysort(arr, count, sizeof(arr[0]), int_cmp);

    for (size_t i = 0; i < count; ++i)
        ck_assert_int_eq(arr[i], expected[i]);
}
END_TEST

/// Компаратор для типа double
int double_cmp(const void *l, const void *r)
{
    const double *pl = l, *pr = r;

    if (*pl < *pr) return -1;
    if (*pl > *pr) return 1;
    return 0;
}

/// Тест сортировки случайного массива с элементами типа double
START_TEST(test_mysort_double_random)
{
    double arr[] = {5.34, 2.2, 3.0, 4.4, 4.3};
    double expected[] = {2.2, 3, 4.3, 4.4, 5.34};
    size_t count = 5;

    mysort(arr, count, sizeof(arr[0]), double_cmp);

    for (size_t i = 0; i < count; ++i)
        ck_assert_double_eq_tol(arr[i], expected[i], 0.000001);
}
END_TEST

/// Компаратор для типа char
int char_cmp(const void *l, const void *r)
{
    const char *pl = l, *pr = r;

    if (*pl < *pr) return -1;
    if (*pl > *pr) return 1;
    return 0;
}

/// Тест сортировки случайного массива с элементами типа char
START_TEST(test_mysort_char_random)
{
    char arr[] = {'a', 'z', 'e', 'b'};
    char expected[] = {'a', 'b', 'e', 'z'};
    size_t count = 4;

    mysort(arr, count, sizeof(arr[0]), char_cmp);

    for (size_t i = 0; i < count; ++i)
        ck_assert_int_eq(arr[i], expected[i]);
}
END_TEST

Suite* mysort_suite(void)
{
    Suite *s;
    TCase *tc_sorting;
    TCase *tc_other_types;

    s = suite_create("mysort");
    
    tc_sorting = tcase_create("sorting");
    tcase_add_test(tc_sorting, test_mysort_int_one_element);
    tcase_add_test(tc_sorting, test_mysort_int_two_sorted);
    tcase_add_test(tc_sorting, test_mysort_int_two_unsorted);
    tcase_add_test(tc_sorting, test_mysort_int_sorted);
    tcase_add_test(tc_sorting, test_mysort_int_reversed);
    tcase_add_test(tc_sorting, test_mysort_int_random_no_same);
    tcase_add_test(tc_sorting, test_mysort_int_random_yes_same);

    suite_add_tcase(s, tc_sorting);
    
    tc_other_types = tcase_create("other types");
    tcase_add_test(tc_other_types, test_mysort_double_random);
    tcase_add_test(tc_other_types, test_mysort_char_random);

    suite_add_tcase(s, tc_other_types);

    return s;
}

// /// Тест поиска элемента в массиве целых чисел
// START_TEST(test_bin_search_int)
// {
//     int arr[] = {1, 2, 3, 4, 5};
//     int key = 4;
//     size_t size = sizeof(int);
//     int *result = bin_search(arr, arr + 5, size, &key, int_cmp);
//     ck_assert_ptr_nonnull(result);
//     ck_assert_int_eq(*result, 5);
// }
// END_TEST

// /// Тест поиска элемента в массиве символов
// START_TEST(test_bin_search_char)
// {
//     char arr[] = {'a', 'b', 'c', 'd'};
//     size_t size = sizeof(char);
//     char key = 'c';
//     char *result = bin_search(arr, arr + 4, size, &key, char_cmp);
//     ck_assert_ptr_nonnull(result);
//     ck_assert_int_eq(*result, 'd');
// }
// END_TEST

// /// Тест поиска элемента в массиве символов
// START_TEST(test_bin_search_double)
// {
//     double arr[] = {1.2, 2.3, 3.4, 4.5};
//     size_t size = sizeof(double);
//     double key = 2.3;
//     double *result = bin_search(arr, arr + 4, size, &key, double_cmp);
//     ck_assert_ptr_nonnull(result);
//     ck_assert_double_eq_tol(*result, 3.4, 0.000001);
// }
// END_TEST

// /// Тест поиска элемента, отсутствующего в массиве
// START_TEST(test_bin_search_not_found)
// {
//     int arr[] = {1, 3, 5, 7, 9};
//     size_t size = sizeof(int);
//     int key = 4;
//     int *result = bin_search(arr, arr + 5, size, &key, int_cmp);
//     ck_assert_ptr_nonnull(result);
//     ck_assert_int_eq(*result, 5); // Возвращается элемент, который больше ключа
// }
// END_TEST

// Suite* bin_search_suite(void)
// {
//     Suite *s;
//     TCase *tc;

//     s = suite_create("bin_search");
    
//     tc = tcase_create("tests");
//     tcase_add_test(tc, test_bin_search_int);
//     tcase_add_test(tc, test_bin_search_char);
//     tcase_add_test(tc, test_bin_search_double);
//     tcase_add_test(tc, test_bin_search_not_found);

//     suite_add_tcase(s, tc);

//     return s;
// }
