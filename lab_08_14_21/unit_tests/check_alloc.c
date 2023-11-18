#include <check.h>
#include <stdio.h>
#include "mtr_alloc.h"
#include "mtr_io.h"

/// Создание и освобождение матрицы 3х3
START_TEST(test_matrix_allocate_neq3_meq3)
{
    size_t n = 3, m = 3;
    double **data = matrix_allocate(n, m);
    matrix_fill_null(data, n, m);
    data[0][0] = 1;
    data[2][2] = 5;
    matrix_free(data, n);
}
END_TEST

/// Создание и освобождение матрицы 1х3
START_TEST(test_matrix_allocate_neq1_meq3)
{
    size_t n = 1, m = 3;
    double **data = matrix_allocate(n, m);
    matrix_fill_null(data, n, m);
    data[0][0] = 1;
    data[0][2] = 5;
    matrix_free(data, n);
}
END_TEST

/// Создание и освобождение матрицы 3х1
START_TEST(test_matrix_allocate_neq3_meq1)
{
    size_t n = 3, m = 1;
    double **data = matrix_allocate(n, m);
    matrix_fill_null(data, n, m);
    data[0][0] = 1;
    data[2][0] = 5;
    matrix_free(data, n);
}
END_TEST

Suite* matrix_allocate_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("matrix_allocate");
    
    core = tcase_create("tests");
    tcase_add_test(core, test_matrix_allocate_neq3_meq3);
    tcase_add_test(core, test_matrix_allocate_neq1_meq3);
    tcase_add_test(core, test_matrix_allocate_neq3_meq1);

    suite_add_tcase(s, core);

    return s;
}
