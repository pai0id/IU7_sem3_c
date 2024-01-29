#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "arr.h"

void check_arr_eq(int *arr1, int *arr2, size_t size)
{
    for (size_t i = 0; i < size; ++i)
        ck_assert_int_eq(arr1[i], arr2[i]);
}

/// Нормальный входной файл
START_TEST(test_cnt_elements_normal)
{
    FILE *f = fopen("./out/tmp", "w");
    fprintf(f, "1 2 3 4 5");
    fclose(f);
    f = fopen("./out/tmp", "r");
    int cnt;

    int result = cnt_elements(f, &cnt);
    fclose(f);

    ck_assert_int_eq(result, OK);
    ck_assert_int_eq(cnt, 5);
}
END_TEST

/// С пустым входным файлом
START_TEST(test_cnt_elements_empty)
{
    FILE *f = fopen("./out/tmp", "w");
    fclose(f);
    f = fopen("./out/tmp", "r");
    int cnt;

    int result = cnt_elements(f, &cnt);
    fclose(f);

    ck_assert_int_eq(result, OK);
    ck_assert_int_eq(cnt, 0);
}
END_TEST

/// С ошибкой ввода/вывода
START_TEST(test_cnt_elements_io_error)
{
    FILE *f = fopen("./out/tmp", "w");
    fprintf(f, "12 abc 12");
    fclose(f);
    f = fopen("./out/tmp", "r");
    int cnt;

    int result = cnt_elements(f, &cnt);
    fclose(f);

    ck_assert_int_eq(result, ERR_IO);
}
END_TEST

Suite* cnt_elements_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("cnt_elements");
    
    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_cnt_elements_io_error);

    suite_add_tcase(s, tc_neg);
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_cnt_elements_empty);
    tcase_add_test(tc_pos, test_cnt_elements_normal);

    suite_add_tcase(s, tc_pos);

    return s;
}

/// Нормальный ввод
START_TEST(test_read_arr_normal)
{
    FILE *f = fopen("./out/tmp", "w");
    fprintf(f, "1 2 3 4 5 ");
    fclose(f);
    f = fopen("./out/tmp", "r");
    int res[] = {1, 2, 3, 4, 5};

    int *arr = malloc(100 * sizeof(int));
    int *pb = arr, *pe;

    read_arr(f, &pb, &pe);

    check_arr_eq(res, pb, sizeof(res)/sizeof(res[0]));
    _ck_assert_ptr(pe, ==, pb + sizeof(res)/sizeof(res[0]));

    fclose(f);
    free(arr);
}
END_TEST

/// Пустой ввод
START_TEST(test_read_arr_empty)
{
    FILE *f = fopen("./out/tmp", "w");
    fclose(f);
    f = fopen("./out/tmp", "r");

    int *arr = malloc(100 * sizeof(int));
    int *pb = arr, *pe;

    read_arr(f, &pb, &pe);

    ck_assert_int_eq(pe - pb, 0);

    fclose(f);
    free(arr);
}
END_TEST

Suite* read_arr_suite(void)
{
    Suite *s;
    TCase *tests;

    s = suite_create("read_arr");

    tests = tcase_create("tests");
    tcase_add_test(tests, test_read_arr_empty);
    tcase_add_test(tests, test_read_arr_normal);

    suite_add_tcase(s, tests);

    return s;
}

//--------------------------------------------

/// Тест считывания из пустого файла
START_TEST(test_get_arr_empty_file)
{
    FILE *f = fopen("./out/empt", "r");

    int *pb = NULL;
    int *pe = NULL;
    int result = get_arr(f, &pb, &pe);
    fclose(f);

    ck_assert_int_eq(result, ERR_FILE_EMPTY);
    ck_assert_ptr_null(pb);
    ck_assert_ptr_null(pe);

}
END_TEST

/// Тест считывания из файла с некорректными данными
START_TEST(test_get_arr_invalid_data)
{
    FILE *f = fopen("./out/tmp", "w");
    fprintf(f, "abc");
    fclose(f);
    f = fopen("./out/tmp", "r");

    int *pb = NULL;
    int *pe = NULL;
    int result = get_arr(f, &pb, &pe);
    fclose(f);

    ck_assert_int_eq(result, ERR_IO);
    ck_assert_ptr_null(pb);
    ck_assert_ptr_null(pe);
}
END_TEST

/// Тест считывания из файла с одним числом
START_TEST(test_get_arr_one_number)
{
    FILE *f = fopen("./out/one", "r");

    int expected[] = {42};

    int *pb = NULL;
    int *pe = NULL;
    int result = get_arr(f, &pb, &pe);
    fclose(f);

    ck_assert_int_eq(result, OK);
    ck_assert_ptr_nonnull(pb);
    ck_assert_ptr_nonnull(pe);
    check_arr_eq(pb, expected, pe - pb);

    free(pb);
}
END_TEST

/// Тест считывания из файла с несколькими числами
START_TEST(test_get_arr_many_numbers)
{
    FILE *f = fopen("./out/many", "r");

    int expected[] = {1, 2, 3, 4, 5};

    int *pb = NULL;
    int *pe = NULL;
    int result = get_arr(f, &pb, &pe);
    fclose(f);

    ck_assert_int_eq(result, OK);
    ck_assert_ptr_nonnull(pb);
    ck_assert_ptr_nonnull(pe);
    check_arr_eq(pb, expected, pe - pb);

    free(pb);
}
END_TEST

Suite* get_arr_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("get_arr");
    
    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_get_arr_empty_file);
    tcase_add_test(tc_neg, test_get_arr_invalid_data);

    suite_add_tcase(s, tc_neg);
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_get_arr_one_number);
    tcase_add_test(tc_pos, test_get_arr_many_numbers);

    suite_add_tcase(s, tc_pos);

    return s;
}

/// Тест печати пустого массива
START_TEST(test_print_arr_no_element)
{
    FILE *f = fopen("./out/empt", "w");

    int arr[] = {0};
    int *pb = arr;
    int *pe = arr;

    print_arr(f, pb, pe);

    fclose(f);
    f = fopen("./out/empt", "r");

    int value;
    int read_count = fscanf(f, "%d", &value);

    ck_assert_int_eq(read_count, -1);
    fclose(f);
}
END_TEST

/// Тест печати одного элемента
START_TEST(test_print_arr_one_element)
{
    FILE *f = fopen("./out/one", "w");

    int arr[] = {42};
    int *pb = arr;
    int *pe = arr + 1;

    print_arr(f, pb, pe);

    fclose(f);
    f = fopen("./out/one", "r");

    int value;
    int read_count = fscanf(f, "%d", &value);

    ck_assert_int_eq(read_count, 1);
    ck_assert_int_eq(value, 42);
    fclose(f);
}
END_TEST

/// Тест печати нескольких элементов
START_TEST(test_print_arr_many_elements)
{
    FILE *f = fopen("./out/many", "w");

    int arr[] = {1, 2, 3, 4, 5};
    int *pb = arr;
    int *pe = arr + 5;

    print_arr(f, pb, pe);

    fclose(f);
    f = fopen("./out/many", "r");

    int values[5];
    int read_count = fscanf(f, "%d %d %d %d %d",
     &values[0], &values[1], &values[2], &values[3], &values[4]);

    ck_assert_int_eq(read_count, 5);
    check_arr_eq(values, arr, 5);
    fclose(f);
}
END_TEST

Suite* print_arr_suite(void)
{
    Suite *s;
    TCase *tc;

    s = suite_create("print_arr");
    
    tc = tcase_create("tests");
    tcase_add_test(tc, test_print_arr_no_element);
    tcase_add_test(tc, test_print_arr_one_element);
    tcase_add_test(tc, test_print_arr_many_elements);
    

    suite_add_tcase(s, tc);

    return s;
}
