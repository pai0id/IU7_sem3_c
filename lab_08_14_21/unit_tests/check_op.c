#include <check.h>
#include <stdio.h>
#include <math.h>
#include "mtr_op.h"
#include "check_func.h"

/// Умножение матриц 3х3
START_TEST(test_matrix_mult_an3_am3_bn3_bm3)
{
    size_t an = 3, am = 3, bn = 3, bm = 3, cn = 3, cm = 3;
    double pa[N_MAX][M_MAX] = {{1, 8, 2}, {5, 9, 6}, {4, 7, 3}};
    double *a[N_MAX] = {pa[0], pa[1], pa[2]};
    
    double pb[N_MAX][M_MAX] = {{1, 2, 3}, {2, 1, 3}, {3, 0, 1}};
    double *b[N_MAX] = {pb[0], pb[1], pb[2]};

    double pc[N_MAX][M_MAX] = {{23, 10, 29}, {41, 19, 48}, {27, 15, 36}};
    double *c[N_MAX] = {pc[0], pc[1], pc[2]};

    double **res;

    int rc = matrix_mult(a, an, am, b, bn, bm, &res, &cn, &cm);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(cn, 3);
    ck_assert_int_eq(cm, 3);
    for (size_t i = 0; i < cn; ++i)
        for (size_t j = 0; j < cm; ++j)
            ck_assert_double_eq_tol(res[i][j], c[i][j], EPS);
    
    matrix_free(res, cn);
}
END_TEST

/// Умножение матриц 1х3 и 3х1
START_TEST(test_matrix_mult_an1_am3_bn3_bm1)
{
    size_t an = 1, am = 3, bn = 3, bm = 1, cn = 1, cm = 1;
    double pa[N_MAX][M_MAX] = {{1, 8, 2}};
    double *a[N_MAX] = {pa[0]};

    double pb[N_MAX][M_MAX] = {{1}, {2}, {3}};
    double *b[N_MAX] = {pb[0], pb[1], pb[2]};

    double pc[N_MAX][M_MAX] = {{23}};
    double *c[N_MAX] = {pc[0]};

    double **res;

    int rc = matrix_mult(a, an, am, b, bn, bm, &res, &cn, &cm);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(cn, 1);
    ck_assert_int_eq(cm, 1);
    for (size_t i = 0; i < cn; ++i)
        for (size_t j = 0; j < cm; ++j)
            ck_assert_double_eq_tol(res[i][j], c[i][j], EPS);
    
    matrix_free(res, cn);
}
END_TEST

/// Умножение матриц ошибка размера
START_TEST(test_matrix_mult_err_size)
{
    size_t an = 1, am = 2, bn = 3, bm = 1, cn, cm;
    double pa[N_MAX][M_MAX] = {{1, 8}};
    double *a[N_MAX] = {pa[0]};

    double pb[N_MAX][M_MAX] = {{1}, {2}, {3}};
    double *b[N_MAX] = {pb[0], pb[1], pb[2]};

    double **res;

    int rc = matrix_mult(a, an, am, b, bn, bm, &res, &cn, &cm);

    ck_assert_int_eq(rc, ERR_RANGE);
}
END_TEST

Suite* matrix_mult_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("matrix_mult");
    
    tc_pos = tcase_create("Pos");
    tcase_add_test(tc_pos, test_matrix_mult_an3_am3_bn3_bm3);
    tcase_add_test(tc_pos, test_matrix_mult_an1_am3_bn3_bm1);

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("Neg");
    tcase_add_test(tc_neg, test_matrix_mult_err_size);

    suite_add_tcase(s, tc_neg);

    return s;
}

/// Сложение матриц 3х3
START_TEST(test_matrix_add_an3_am3_bn3_bm3)
{
    size_t an = 3, am = 3, bn = 3, bm = 3, cn = 3, cm = 3;
    double pa[N_MAX][M_MAX] = {{1, 8, 2}, {5, 9, 6}, {4, 7, 3}};
    double *a[N_MAX] = {pa[0], pa[1], pa[2]};

    double pb[N_MAX][M_MAX] = {{1, 2, 3}, {2, 1, 3}, {3, 0, 1}};
    double *b[N_MAX] = {pb[0], pb[1], pb[2]};

    double pc[N_MAX][M_MAX] = {{2, 10, 5}, {7, 10, 9}, {7, 7, 4}};
    double *c[N_MAX] = {pc[0], pc[1], pc[2]};
    
    double **res;

    int rc = matrix_add(a, an, am, b, bn, bm, &res, &cn, &cm);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(cn, 3);
    ck_assert_int_eq(cm, 3);
    for (size_t i = 0; i < cn; ++i)
        for (size_t j = 0; j < cm; ++j)
            ck_assert_double_eq_tol(res[i][j], c[i][j], EPS);
    
    matrix_free(res, cn);
}
END_TEST

/// Сложение матриц 1х3
START_TEST(test_matrix_add_an1_am3_bn1_bm3)
{
    size_t an = 1, am = 3, bn = 1, bm = 3, cn = 1, cm = 3;
    double pa[N_MAX][M_MAX] = {{1, 8, 2}};
    double *a[N_MAX] = {pa[0]};

    double pb[N_MAX][M_MAX] = {{1, 2, 3}};
    double *b[N_MAX] = {pb[0]};

    double pc[N_MAX][M_MAX] = {{2, 10, 5}};
    double *c[N_MAX] = {pc[0]};

    double **res;

    int rc = matrix_add(a, an, am, b, bn, bm, &res, &cn, &cm);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(cn, 1);
    ck_assert_int_eq(cm, 3);
    for (size_t i = 0; i < cn; ++i)
        for (size_t j = 0; j < cm; ++j)
            ck_assert_double_eq_tol(res[i][j], c[i][j], EPS);
    
    matrix_free(res, cn);
}
END_TEST

/// Сложение матриц ошибка размера
START_TEST(test_matrix_add_err_size)
{
    size_t an = 1, am = 2, bn = 3, bm = 1, cn, cm;
    double pa[N_MAX][M_MAX] = {{1, 8}};
    double *a[N_MAX] = {pa[0]};

    double pb[N_MAX][M_MAX] = {{1}, {2}, {3}};
    double *b[N_MAX] = {pb[0], pb[1], pb[2]};
    double **res;

    int rc = matrix_add(a, an, am, b, bn, bm, &res, &cn, &cm);

    ck_assert_int_eq(rc, ERR_RANGE);
}
END_TEST

Suite* matrix_add_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("matrix_add");
    
    tc_pos = tcase_create("Pos");
    tcase_add_test(tc_pos, test_matrix_add_an3_am3_bn3_bm3);
    tcase_add_test(tc_pos, test_matrix_add_an1_am3_bn1_bm3);

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("Neg");
    tcase_add_test(tc_neg, test_matrix_add_err_size);

    suite_add_tcase(s, tc_neg);

    return s;
}

/// Решение СЛУ, имеющей решение
START_TEST(test_solve_eq_good)
{
    size_t n = 3;
    double pmtr[N_MAX][M_MAX] = {{1, 6, 9}, {1, 2, 4}, {0, 4, 3}};
    double *mtr[N_MAX] = {pmtr[0], pmtr[1], pmtr[2]};

    double f[N_MAX] = {0, 10, 8};
    double exp[N_MAX] = {28.5, 8.75, -9};

    int rc = solve_eq(mtr, n, f);
    
    ck_assert_int_eq(rc, OK);
    for (size_t i = 0; i < n; ++i)
        ck_assert_double_eq_tol(f[i], exp[i], EPS);
}
END_TEST

/// Решение СЛУ, не имеющей решение
START_TEST(test_solve_eq_bad)
{
    size_t n = 3;
    double pmtr[N_MAX][M_MAX] = {{1, 6, 9}, {1, 2, 4}, {2, 4, 8}};
    double *mtr[N_MAX] = {pmtr[0], pmtr[1], pmtr[2]};

    double f[N_MAX] = {0, 10, 20};

    int rc = solve_eq(mtr, n, f);
    
    ck_assert_int_eq(rc, ERR_UNSOLVABLE);
}
END_TEST

Suite* solve_eq_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("solve_eq");
    
    tc_pos = tcase_create("Pos");
    tcase_add_test(tc_pos, test_solve_eq_good);

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("Neg");
    tcase_add_test(tc_neg, test_solve_eq_bad);

    suite_add_tcase(s, tc_neg);

    return s;
}

/// Транспонирование матрицы
START_TEST(test_matrix_transpose)
{
    size_t n = 3;
    double pmtr[N_MAX][M_MAX] = {{1, 6, 9}, {1, 2, 4}, {2, 4, 8}};
    double *mtr[N_MAX] = {pmtr[0], pmtr[1], pmtr[2]};

    double pexp[N_MAX][M_MAX] = {{1, 1, 2}, {6, 2, 4}, {9, 4, 8}};
    double *exp[N_MAX] = {pexp[0], pexp[1], pexp[2]};

    matrix_transpose(mtr, n);
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j)
            ck_assert_double_eq_tol(mtr[i][j], exp[i][j], EPS);
}
END_TEST

Suite* matrix_transpose_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("matrix_transpose");
    
    core = tcase_create("Tests");
    tcase_add_test(core, test_matrix_transpose);

    suite_add_tcase(s, core);

    return s;
}

/// Обратная матрица невырожденной матрицы
START_TEST(test_matrix_calc_rev_good)
{
    size_t n = 3, res_n, res_m;
    double pmtr[N_MAX][M_MAX] = {{0, 8, 2}, {2, 2, 6}, {4, 4, 8}};
    double *mtr[N_MAX] = {pmtr[0], pmtr[1], pmtr[2]};

    double pexp[N_MAX][M_MAX] = {{-0.125, -0.875, 0.6875}, {0.125, -0.125, 0.0625}, {0, 0.5, -0.25}};
    double *exp[N_MAX] = {pexp[0], pexp[1], pexp[2]};

    double **res;

    int rc = matrix_calc_rev(mtr, n, n, &res, &res_n, &res_m);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(res_n, 3);
    ck_assert_int_eq(res_m, 3);
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j)
            ck_assert_double_eq_tol(res[i][j], exp[i][j], EPS);
    
    matrix_free(res, res_n);
}
END_TEST

/// Обратная матрица вырожденной матрицы
START_TEST(test_matrix_calc_rev_bad_unsolvable)
{
    size_t n = 3, res_n, res_m;
    double pmtr[N_MAX][M_MAX] = {{0, 0, 0}, {2, 0, 6}, {4, 4, 0}};
    double *mtr[N_MAX] = {pmtr[0], pmtr[1], pmtr[2]};

    double **res;

    int rc = matrix_calc_rev(mtr, n, n, &res, &res_n, &res_m);

    ck_assert_int_eq(rc, ERR_UNSOLVABLE);
}
END_TEST

/// Обратная матрица не квадратная
START_TEST(test_matrix_calc_rev_bad_size)
{
    size_t n = 3, m = 4, res_n, res_m;
    double pmtr[N_MAX][M_MAX] = {{0, 0, 0, 1}, {2, 0, 6, 1}, {4, 4, 0, 1}};
    double *mtr[N_MAX] = {pmtr[0], pmtr[1], pmtr[2]};

    double **res;

    int rc = matrix_calc_rev(mtr, n, m, &res, &res_n, &res_m);

    ck_assert_int_eq(rc, ERR_RANGE);
}
END_TEST

Suite* matrix_calc_rev_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("matrix_calc_rev");
    
    tc_pos = tcase_create("Pos");
    tcase_add_test(tc_pos, test_matrix_calc_rev_good);

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("Neg");
    tcase_add_test(tc_neg, test_matrix_calc_rev_bad_unsolvable);
    tcase_add_test(tc_neg, test_matrix_calc_rev_bad_size);

    suite_add_tcase(s, tc_neg);

    return s;
}
