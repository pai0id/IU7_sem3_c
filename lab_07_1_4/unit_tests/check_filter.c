#include "filter.h"
#include <check.h>

/// Тест расчета среднего значения для пустого массива
START_TEST(test_calculate_avr_empty_array)
{
    int arr[] = {0};
    int *pb = arr;
    int *pe = arr;

    double avr;
    int rc = calculate_avr(pb, pe, &avr);

    ck_assert_int_eq(rc, ERR_SIZE);
}
END_TEST

/// Тест расчета среднего значения для массива с одним элементом
START_TEST(test_calculate_avr_one_element)
{
    int arr[] = {42};
    int *pb = arr;
    int *pe = arr + 1;

    double avr = 0;
    int rc = calculate_avr(pb, pe, &avr);

    ck_assert_int_eq(rc, OK);
    ck_assert_double_eq_tol(avr, 42, 0.000001);
}
END_TEST

/// Тест расчета среднего значения для массива с положительными элементами
START_TEST(test_calculate_avr_positive_numbers)
{
    int arr[] = {1, 2, 3, 4, 5};
    int *pb = arr;
    int *pe = arr + 5;

    double avr = 0;
    int rc = calculate_avr(pb, pe, &avr);

    ck_assert_int_eq(rc, OK);
    ck_assert_double_eq_tol(avr, 3, 0.000001);
}
END_TEST

/// Тест расчета среднего значения для массива с отрицательными элементами
START_TEST(test_calculate_avr_negative_numbers)
{
    int arr[] = {-1, -2, -3, -4, -5};
    int *pb = arr;
    int *pe = arr + 5;

    double avr = 0;
    int rc = calculate_avr(pb, pe, &avr);

    ck_assert_int_eq(rc, OK);
    ck_assert_double_eq_tol(avr, -3, 0.000001);
}
END_TEST

Suite* calculate_avr_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("calculate_avr");
    
    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_calculate_avr_empty_array);

    suite_add_tcase(s, tc_neg);
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_calculate_avr_one_element);
    tcase_add_test(tc_pos, test_calculate_avr_positive_numbers);
    tcase_add_test(tc_pos, test_calculate_avr_negative_numbers);

    suite_add_tcase(s, tc_pos);

    return s;
}

/// Тест подсчета элементов больше среднего для пустого массива
START_TEST(test_count_above_avr_empty_array)
{
    int arr[] = {0};
    int *pb = arr;
    int *pe = arr;

    double avr = 0;
    int count = 0;
    int rc = count_above_avr(pb, pe, avr, &count);

    ck_assert_int_eq(rc, ERR_SIZE);
    ck_assert_int_eq(count, 0);
}
END_TEST

/// Тест подсчета элементов больше среднего для массива с одним элементом
START_TEST(test_count_above_avr_one_element)
{
    int arr[] = {42};
    int *pb = arr;
    int *pe = arr + 1;

    double avr = 42;
    int count = 0;
    int rc = count_above_avr(pb, pe, avr, &count);

    ck_assert_int_eq(rc, ERR_SIZE);
    ck_assert_int_eq(count, 0);
}
END_TEST

/// Тест подсчета элементов больше среднего для массива с элементами больше среднего
START_TEST(test_count_above_avr_elements_above_avr)
{
    int arr[] = {1, 2, 3, 4, 5};
    int *pb = arr;
    int *pe = arr + 5;

    double avr = 3;
    int count = 0;
    int rc = count_above_avr(pb, pe, avr, &count);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(count, 2); 
}
END_TEST

Suite* count_above_avr_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("count_above_avr");
    
    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_count_above_avr_empty_array);
    tcase_add_test(tc_neg, test_count_above_avr_one_element);

    suite_add_tcase(s, tc_neg);
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_count_above_avr_elements_above_avr);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Тестирование функции fill_above_avr с всеми элементами выше среднего
START_TEST(test_fill_above_avr_all_above)
{
    const int src[] = {6, 7, 8, 9};
    int res[] ={6, 7, 8, 9};
    int result[10];
    double avr = 5.0;

    fill_above_avr(src, src + 4, avr, result);

    for (size_t i = 0; i < sizeof(res)/sizeof(res[0]); ++i)
        ck_assert_int_eq(res[i], result[i]);
}
END_TEST

// Тестирование функции fill_above_avr с одним элементом выше среднего
START_TEST(test_fill_above_avr_one_above)
{
    const int src[] = {6, 7, 8, 10};
    int res[] ={10};
    int result[10];
    double avr = 9.0;

    fill_above_avr(src, src + 4, avr, result);

    for (size_t i = 0; i < sizeof(res)/sizeof(res[0]); ++i)
        ck_assert_int_eq(res[i], result[i]);
}
END_TEST

Suite *fill_above_avr_suite(void)
{
    Suite *s;
    TCase *tc;

    s = suite_create("fill_above_avr");

    tc = tcase_create("tests");

    tcase_add_test(tc, test_fill_above_avr_all_above);
    tcase_add_test(tc, test_fill_above_avr_one_above);

    suite_add_tcase(s, tc);

    return s;
}

/// Тест копирования элементов больше среднего для пустого массива
START_TEST(test_copy_above_avr_empty_array)
{
    int arr[] = {0};
    int *pb_src = arr;
    int *pe_src = arr;
    double avr = 0;

    int *pb_dst = NULL;
    int *pe_dst = NULL;
    int rc = copy_above_avr(pb_src, pe_src, avr, &pb_dst, &pe_dst);

    ck_assert_int_eq(rc, ERR_SIZE);
}
END_TEST

/// Тест копирования элементов больше среднего для массива с одним элементом
START_TEST(test_copy_above_avr_one_element)
{
    int arr[] = {42};
    int *pb_src = arr;
    int *pe_src = arr + 1;
    double avr = 42;

    int *pb_dst = NULL;
    int *pe_dst = NULL;
    int rc = copy_above_avr(pb_src, pe_src, avr, &pb_dst, &pe_dst);

    ck_assert_int_eq(rc, ERR_SIZE);

    free(pb_dst);
}
END_TEST

/// Тест копирования элементов больше среднего для массива с элементами больше среднего
START_TEST(test_copy_above_avr_elements_above_avr)
{
    int arr[] = {1, 2, 3, 4, 5};
    int *pb_src = arr;
    int *pe_src = arr + 5;
    double avr = 3;
    int expected[] = {4, 5};

    int *pb_dst = NULL;
    int *pe_dst = NULL;
    int rc = copy_above_avr(pb_src, pe_src, avr, &pb_dst, &pe_dst);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(pb_dst);
    ck_assert_ptr_nonnull(pe_dst);
    for (int i = 0; i < pe_dst - pb_dst; ++i)
        ck_assert_int_eq(*(pb_dst + i), expected[i]);

    free(pb_dst);
}
END_TEST

Suite* copy_above_avr_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("copy_above_avr");
    
    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_copy_above_avr_empty_array);
    tcase_add_test(tc_neg, test_copy_above_avr_one_element);

    suite_add_tcase(s, tc_neg);
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_copy_above_avr_elements_above_avr);

    suite_add_tcase(s, tc_pos);

    return s;
}

/// Этот тест проверяет, что функция key корректно обрабатывает ситуацию,
/// когда в исходном массиве есть только один элемент, превышающий среднее значение.
START_TEST(test_key_one_element_above_average)
{
    int src[] = {1, 2, 3, 4, 10};
    int expected[] = {10};
    int *pb_dst = NULL;
    int *pe_dst = NULL;

    int rc = key(src, src + 5, &pb_dst, &pe_dst);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(pb_dst);
    ck_assert_ptr_nonnull(pe_dst);
    ck_assert_int_eq(pe_dst - pb_dst, 1);
    for (int i = 0; i < pe_dst - pb_dst; ++i)
        ck_assert_int_eq(*(pb_dst + i), expected[i]);

    free(pb_dst);
}
END_TEST

/// Этот тест проверяет, что функция key корректно обрабатывает ситуацию,
/// когда в исходном массиве есть несколько элементов, превышающих среднее значение.
START_TEST(test_key_many_elements_above_average)
{
    int src[] = {1, 2, 1, 4, 8, 9, 10};
    int expected[] = {8, 9, 10};
    int *pb_dst = NULL;
    int *pe_dst = NULL;

    int rc = key(src, src + 7, &pb_dst, &pe_dst);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(pb_dst);
    ck_assert_ptr_nonnull(pe_dst);
    ck_assert_int_eq(pe_dst - pb_dst, 3);
    for (int i = 0; i < pe_dst - pb_dst; ++i)
        ck_assert_int_eq(*(pb_dst + i), expected[i]);

    free(pb_dst);
}
END_TEST

/// Этот тест проверяет функцию key на корректную обработку ситуации,
/// когда входной массив пуст.
START_TEST(test_key_empty_array)
{
    int src[] = {0};
    int *pb_dst = NULL;
    int *pe_dst = NULL;

    int rc = key(src, src, &pb_dst, &pe_dst);

    ck_assert_int_eq(rc, ERR_SIZE);
    ck_assert_ptr_null(pb_dst);
    ck_assert_ptr_null(pe_dst);
}
END_TEST

/// Этот тест проверяет функцию key на корректную обработку ситуации,
/// когда все элементы входного массива равны.
START_TEST(test_key_all_elements_equal)
{
    int src[] = {1, 1, 1, 1, 1};
    int *pb_dst = NULL;
    int *pe_dst = NULL;

    int rc = key(src, src + 5, &pb_dst, &pe_dst);

    ck_assert_int_eq(rc, ERR_SIZE);
    ck_assert_ptr_null(pb_dst);
    ck_assert_ptr_null(pe_dst);
}
END_TEST

Suite* key_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("key");
    
    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_key_empty_array);
    tcase_add_test(tc_neg, test_key_all_elements_equal);

    suite_add_tcase(s, tc_neg);
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_key_one_element_above_average);
    tcase_add_test(tc_pos, test_key_many_elements_above_average);

    suite_add_tcase(s, tc_pos);

    return s;
}
