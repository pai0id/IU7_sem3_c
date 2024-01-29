#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "my_snprintf.h"
#include <check.h>

#define ERR_OK 0
#define ERR_DIFF_EL 1
#define ERR_DIFF_SIZE 2
#define ARR_LEN 50

int char_arr_eq(char *l_arr, size_t l_n, char *r_arr, size_t r_n)
{
    if (l_n != r_n)
        return ERR_DIFF_SIZE;
    for (size_t i = 0; i < l_n; ++i)
        if (l_arr[i] != r_arr[i])
            return ERR_DIFF_EL;
    return ERR_OK;
}

// // тесты не допущенные -Werror

// /// Null вместо строки форматирования
// START_TEST(test_my_snprintf_form_null)
// {
//     char buf1[ARR_LEN], buf2[ARR_LEN];
//     size_t size = 10;
//     int cnt1, cnt2;
    // long long num = 0123;
//     cnt1 = my_snprintf(buf1, size, (char *)NULL);
//     cnt2 = snprintf(buf2, size, (char *)NULL);
//     ck_assert_int_eq(cnt1, cnt2);
// }
// END_TEST

// /// Size == 0 - подсчет символов полученной строки
// START_TEST(test_my_snprintf_cnt_only)
// {
//     size_t size = 0;
//     int cnt1, cnt2;
    // long long num = 0123;
//     cnt1 = my_snprintf(NULL, size, "%llo %s", num, "Hello");
//     cnt2 = snprintf(NULL, size, "%llo %s", num, "Hello");
//     ck_assert_int_eq(cnt1, cnt2);
// }
// END_TEST

// /// Модификатору %s соответсвтует NULL
// START_TEST(test_my_snprintf_s_null)
// {
//     char buf1[ARR_LEN], buf2[ARR_LEN];
//     size_t size = 10;
//     int cnt1, cnt2;
    // long long num = 0123;
//     cnt1 = my_snprintf(buf1, size, "%s", (char *)NULL);
//     cnt2 = snprintf(buf2, size, "%s", (char *)NULL);
//     ck_assert_int_eq(cnt1, cnt2);
//     ck_assert_str_eq(buf1, buf2);
// }
// END_TEST

/// Длина полученной строки <= size
START_TEST(test_my_snprintf_len_le_size)
{
    char buf1[ARR_LEN], buf2[ARR_LEN];
    size_t size = 10;
    int cnt1, cnt2;
    long long num = 0123;
    cnt1 = my_snprintf(buf1, size, "%llo %s", num, "Hello");
    cnt2 = snprintf(buf2, size, "%llo %s", num, "Hello");
    ck_assert_int_eq(cnt1, cnt2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

/// Длина полученной строки > size
START_TEST(test_my_snprintf_len_mt_size)
{
    char buf1[ARR_LEN], buf2[ARR_LEN];
    size_t size = 5;
    int cnt1, cnt2;
    long long num = 0123;
    cnt1 = my_snprintf(buf1, size, "%llo %s", num, "Hello");
    cnt2 = snprintf(buf2, size, "%llo %s", num, "Hello");
    ck_assert_int_eq(cnt1, cnt2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

/// Модификатору %s соответсвтует пустая строка
START_TEST(test_my_snprintf_s_empt)
{
    char buf1[ARR_LEN], buf2[ARR_LEN];
    size_t size = 10;
    int cnt1, cnt2;
    cnt1 = my_snprintf(buf1, size, "%s", "");
    cnt2 = snprintf(buf2, size, "%s", "");
    ck_assert_int_eq(cnt1, cnt2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

/// LLONG_MAX
START_TEST(test_my_snprintf_llo_max)
{
    char buf1[ARR_LEN], buf2[ARR_LEN];
    size_t size = 20;
    int cnt1, cnt2;
    cnt1 = my_snprintf(buf1, size, "%llo", LLONG_MAX);
    cnt2 = snprintf(buf2, size, "%llo", LLONG_MAX);
    ck_assert_int_eq(cnt1, cnt2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

/// LLONG_MIN
START_TEST(test_my_snprintf_llo_min)
{
    char buf1[ARR_LEN], buf2[ARR_LEN];
    size_t size = 20;
    int cnt1, cnt2;
    cnt1 = my_snprintf(buf1, size, "%llo", LLONG_MIN);
    cnt2 = snprintf(buf2, size, "%llo", LLONG_MIN);
    ck_assert_int_eq(cnt1, cnt2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

Suite* my_snprintf_suite(void)
{
    Suite *s;
    TCase *pos;

    s = suite_create("my_snprintf");

    pos = tcase_create("pos");
    // tcase_add_test(pos, test_my_snprintf_cnt_only);
    tcase_add_test(pos, test_my_snprintf_len_le_size);
    tcase_add_test(pos, test_my_snprintf_len_mt_size);
    // tcase_add_test(pos, test_my_snprintf_s_null);
    tcase_add_test(pos, test_my_snprintf_s_empt);
    tcase_add_test(pos, test_my_snprintf_llo_max);
    tcase_add_test(pos, test_my_snprintf_llo_min);
    suite_add_tcase(s, pos);

    // TCase *neg;
    // neg = tcase_create("neg");
    // tcase_add_test(neg, test_my_snprintf_form_null);
    // suite_add_tcase(s, neg);

    return s;
}

/// Вставка в массив длины 0
START_TEST(test_insert_0)
{
    char arr[] = {1, 2, 3};
    char res[] = {1, 2, 3};
    
    insert_beg_fixed_size(0, arr, 0);

    ck_assert_int_eq(char_arr_eq(arr, 3, res, 3), ERR_OK);
}
END_TEST

/// Вставка в массив длины 1
START_TEST(test_insert_1)
{
    char arr[] = {1, 2, 3};
    char res[] = {0, 2, 3};
    
    insert_beg_fixed_size(0, arr, 1);

    ck_assert_int_eq(char_arr_eq(arr, 3, res, 3), ERR_OK);
}
END_TEST

/// Вставка в массив длины 3
START_TEST(test_insert_3)
{
    char arr[] = {1, 2, 3};
    char res[] = {0, 1, 2};
    
    insert_beg_fixed_size(0, arr, 3);

    ck_assert_int_eq(char_arr_eq(arr, 3, res, 3), ERR_OK);
}
END_TEST

Suite* insert_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("insert");

    core = tcase_create("core");
    tcase_add_test(core, test_insert_0);
    tcase_add_test(core, test_insert_1);
    tcase_add_test(core, test_insert_3);
    suite_add_tcase(s, core);

    return s;
}

/// Перевод в возьмеричную систему числа 7
START_TEST(test_snprint_to_octal_one_digit)
{
    char buf[ARR_LEN] = {0};
    unsigned long long x = 7;
    size_t size = 10;
    int cnt = snprint_to_octal(x, buf, size);
    ck_assert_int_eq(cnt, 1);
    ck_assert_str_eq(buf, "7");
}
END_TEST

/// Перевод в возьмеричную систему трехзначного числа
START_TEST(test_snprint_to_octal_three_digit)
{
    char buf[ARR_LEN] = {0};
    unsigned long long x = 0123;
    size_t size = 10;
    int cnt = snprint_to_octal(x, buf, size);
    ck_assert_int_eq(cnt, 3);
    ck_assert_str_eq(buf, "123");
}
END_TEST

/// Перевод в возьмеричную систему LL_MAX
START_TEST(test_snprint_to_octal_ll_max)
{
    char buf[ARR_LEN] = {0};
    unsigned long long x = LLONG_MAX;
    size_t size = 30;
    int cnt = snprint_to_octal(x, buf, size);
    ck_assert_int_eq(cnt, 21);
    ck_assert_str_eq(buf, "777777777777777777777");
}
END_TEST

/// Перевод в возьмеричную систему LL_MIN
START_TEST(test_snprint_to_octal_ll_min)
{
    char buf[ARR_LEN] = {0};
    unsigned long long x = LLONG_MIN;
    size_t size = 30;
    int cnt = snprint_to_octal(x, buf, size);
    ck_assert_int_eq(cnt, 22);
    ck_assert_str_eq(buf, "1000000000000000000000");
}
END_TEST

/// Перевод в возьмеричную систему без записи
START_TEST(test_snprint_to_octal_zero_size)
{
    char buf[ARR_LEN] = {0};
    unsigned long long x = 0123;
    size_t size = 0;
    int cnt = snprint_to_octal(x, buf, size);
    ck_assert_int_eq(cnt, 3);
}
END_TEST

/// Перевод в возьмеричную систему запись не целиком
START_TEST(test_snprint_to_octal_less_size)
{
    char buf[ARR_LEN] = {0};
    unsigned long long x = 0123;
    size_t size = 2;
    int cnt = snprint_to_octal(x, buf, size);
    ck_assert_int_eq(cnt, 3);
    ck_assert_str_eq(buf, "1");
}
END_TEST

Suite* snprint_to_octal_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("snprint_to_octal");

    core = tcase_create("core");
    tcase_add_test(core, test_snprint_to_octal_one_digit);
    tcase_add_test(core, test_snprint_to_octal_three_digit);
    tcase_add_test(core, test_snprint_to_octal_ll_max);
    tcase_add_test(core, test_snprint_to_octal_ll_min);
    tcase_add_test(core, test_snprint_to_octal_zero_size);
    tcase_add_test(core, test_snprint_to_octal_less_size);
    suite_add_tcase(s, core);

    return s;
}

/// Строка записана целиком
START_TEST(test_ncpy_str_all_size)
{
    char buf[ARR_LEN] = {0};
    char *str = "Hello";
    size_t size = 10;
    int cnt = ncpy_str(buf, str, size);
    ck_assert_str_eq(buf, str);
    ck_assert_int_eq(cnt, 5);
}
END_TEST

/// Строка записана не целиком
START_TEST(test_ncpy_str_less_size)
{
    char buf[ARR_LEN] = {0};
    char *str = "Hello";
    char *res = "He";
    size_t size = 3;
    int cnt = ncpy_str(buf, str, size);
    ck_assert_str_eq(buf, res);
    ck_assert_int_eq(cnt, 5);
}
END_TEST

/// size = 0
START_TEST(test_ncpy_str_zero_size)
{
    char buf[ARR_LEN] = {0};
    char *str = "Hello";
    char *res = "";
    size_t size = 0;
    int cnt = ncpy_str(buf, str, size);
    ck_assert_str_eq(buf, res);
    ck_assert_int_eq(cnt, 5);
}
END_TEST

Suite* ncpy_str_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("ncpy_str");

    core = tcase_create("core");
    tcase_add_test(core, test_ncpy_str_all_size);
    tcase_add_test(core, test_ncpy_str_less_size);
    tcase_add_test(core, test_ncpy_str_zero_size);
    suite_add_tcase(s, core);

    return s;
}
