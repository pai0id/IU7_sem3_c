#include <check.h>
#include <stdio.h>
#include <math.h>
#include "mtr_alloc.h"
#include "mtr_io.h"
#include "check_func.h"

/// Заполнение матрицы 3х3 нулями
START_TEST(test_matrix_fill_null_neq3_meq3)
{
    size_t n = 3, m = 3;
    double exp[N_MAX][M_MAX] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    double *pexp[N_MAX] = {exp[0], exp[1], exp[2]};

    double **data = matrix_allocate(n, m);
    matrix_fill_null(data, n, m);

    ck_assert_int_eq(double_mtr_eq(data, n, m, pexp, n, m), ERR_OK);
    
    matrix_free(data, n);
}
END_TEST

/// Заполнение матрицы 1х3 нулями
START_TEST(test_matrix_fill_null_neq1_meq3)
{
    size_t n = 1, m = 3;
    double exp[N_MAX][M_MAX] = {{0, 0, 0}};
    double *pexp[N_MAX] = {exp[0]};
    
    double **data = matrix_allocate(n, m);
    matrix_fill_null(data, n, m);

    ck_assert_int_eq(double_mtr_eq(data, n, m, pexp, n, m), ERR_OK);
    
    matrix_free(data, n);
}
END_TEST

/// Заполнение матрицы 3х1 нулями
START_TEST(test_matrix_fill_null_neq3_meq1)
{
    size_t n = 3, m = 1;
    double exp[N_MAX][M_MAX] = {{0}, {0}, {0}};
    double *pexp[N_MAX] = {exp[0], exp[1], exp[2]};
    
    double **data = matrix_allocate(n, m);
    matrix_fill_null(data, n, m);

    ck_assert_int_eq(double_mtr_eq(data, n, m, pexp, n, m), ERR_OK);
    
    matrix_free(data, n);
    
}
END_TEST

Suite* matrix_fill_null_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("matrix_fill_null");
    
    core = tcase_create("tests");
    tcase_add_test(core, test_matrix_fill_null_neq3_meq3);
    tcase_add_test(core, test_matrix_fill_null_neq1_meq3);
    tcase_add_test(core, test_matrix_fill_null_neq3_meq1);

    suite_add_tcase(s, core);

    return s;
}

/// Заполнение диагонали матрицы 3х3 единицами
START_TEST(test_matrix_fill_d_ones_neq3_meq3)
{
    size_t n = 3, m = 3;
    double exp[N_MAX][M_MAX] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    double *pexp[N_MAX] = {exp[0], exp[1], exp[2]};
    
    double **data = matrix_allocate(n, m);
    matrix_fill_d_ones(data, n, m);

    ck_assert_int_eq(double_mtr_eq(data, n, m, pexp, n, m), ERR_OK);
    
    matrix_free(data, n);
}
END_TEST

/// Заполнение диагонали матрицы 1х3 единицами
START_TEST(test_matrix_fill_d_ones_neq1_meq3)
{
    size_t n = 1, m = 3;
    double exp[N_MAX][M_MAX] = {{1, 0, 0}};
    double *pexp[N_MAX] = {exp[0]};
    
    double **data = matrix_allocate(n, m);
    matrix_fill_d_ones(data, n, m);

    ck_assert_int_eq(double_mtr_eq(data, n, m, pexp, n, m), ERR_OK);
    
    matrix_free(data, n);
}
END_TEST

/// Заполнение диагонали матрицы 3х1 единицами
START_TEST(test_matrix_fill_d_ones_neq3_meq1)
{
    size_t n = 3, m = 1;
    double exp[N_MAX][M_MAX] = {{1}, {0}, {0}};
    double *pexp[N_MAX] = {exp[0], exp[1], exp[2]};
    
    double **data = matrix_allocate(n, m);
    matrix_fill_d_ones(data, n, m);

    ck_assert_int_eq(double_mtr_eq(data, n, m, pexp, n, m), ERR_OK);
    
    matrix_free(data, n);
}
END_TEST

Suite* matrix_fill_d_ones_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("matrix_fill_d_ones");
    
    core = tcase_create("tests");
    tcase_add_test(core, test_matrix_fill_d_ones_neq3_meq3);
    tcase_add_test(core, test_matrix_fill_d_ones_neq1_meq3);
    tcase_add_test(core, test_matrix_fill_d_ones_neq3_meq1);

    suite_add_tcase(s, core);

    return s;
}

/// Копирование матрицы 3х3 
START_TEST(test_matrix_copy_neq3_meq3)
{
    size_t n = 3, m = 3;
    double expp[N_MAX][M_MAX] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    double *exp[N_MAX] = {expp[0], expp[1], expp[2]};
    
    double **data = matrix_allocate(n, m);
    matrix_copy(exp, n, m, data);

    ck_assert_int_eq(double_mtr_eq(data, n, m, exp, n, m), ERR_OK);

    matrix_free(data, n);
}
END_TEST

/// Копирование матрицы 1х3 
START_TEST(test_matrix_copy_neq1_meq3)
{
    size_t n = 1, m = 3;
    double expp[N_MAX][M_MAX] = {{1, 0, 0}};
    double *exp[N_MAX] = {expp[0]};
    
    double **data = matrix_allocate(n, m);
    matrix_copy(exp, n, m, data);

    ck_assert_int_eq(double_mtr_eq(data, n, m, exp, n, m), ERR_OK);
    
    matrix_free(data, n);
}
END_TEST

/// Копирование матрицы 3х1
START_TEST(test_matrix_copy_neq3_meq1)
{
    size_t n = 3, m = 1;
    double expp[N_MAX][M_MAX] = {{1}, {0}, {0}};
    double *exp[N_MAX] = {expp[0], expp[1], expp[2]};
    
    double **data = matrix_allocate(n, m);
    matrix_copy(exp, n, m, data);

    ck_assert_int_eq(double_mtr_eq(data, n, m, exp, n, m), ERR_OK);
    
    matrix_free(data, n);
    
}
END_TEST

Suite* matrix_copy_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("matrix_copy");
    
    core = tcase_create("tests");
    tcase_add_test(core, test_matrix_copy_neq3_meq3);
    tcase_add_test(core, test_matrix_copy_neq1_meq3);
    tcase_add_test(core, test_matrix_copy_neq3_meq1);

    suite_add_tcase(s, core);

    return s;
}

/// Чтение координат элементов матрицы без элементов
START_TEST(test_matrix_read_coord_no_el)
{
    size_t n = 3, m = 3, cnt_el = 0;
    double expp[N_MAX][M_MAX] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    double *exp[N_MAX] = {expp[0], expp[1], expp[2]};
    
    FILE *f = fopen("./out/tmp", "w");
    matrix_print_coord(f, exp, n, m, cnt_el);
    fclose(f);
    f = fopen("./out/tmp", "r");
    size_t tmp_n, tmp_m, tmp_cnt_el;
    fscanf(f, "%lu %lu %lu\n", &tmp_n, &tmp_m, &tmp_cnt_el);

    double **data = matrix_allocate(n, m);
    matrix_fill_null(data, n, m);
    int rc = matrix_read_coord(f, data, n, m, cnt_el);
    fclose(f);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(double_mtr_eq(data, n, m, exp, n, m), ERR_OK);
    
    matrix_free(data, n);
    
}
END_TEST

/// Чтение координат элементов матрицы с несколькими элементами
START_TEST(test_matrix_read_coord_few_el)
{
    size_t n = 3, m = 3, cnt_el = 3;
    double expp[N_MAX][M_MAX] = {{1, 0, 0}, {0, 2, 0}, {0, 0, 3}};
    double *exp[N_MAX] = {expp[0], expp[1], expp[2]};
    
    FILE *f = fopen("./out/tmp", "w");
    matrix_print_coord(f, exp, n, m, cnt_el);
    fclose(f);
    f = fopen("./out/tmp", "r");
    fscanf(f, "%lu %lu %lu\n", &n, &m, &cnt_el);

    double **data = matrix_allocate(n, m);
    matrix_fill_null(data, n, m);
    int rc = matrix_read_coord(f, data, n, m, cnt_el);
    fclose(f);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(double_mtr_eq(data, n, m, exp, n, m), ERR_OK);
    
    matrix_free(data, n);
    
}
END_TEST

/// Чтение координат элементов матрицы со всеми значимыми элементами
START_TEST(test_matrix_read_coord_all_el)
{
    size_t n = 3, m = 3, cnt_el = 9;
    double expp[N_MAX][M_MAX] = {{1, 4, 7}, {9, 2, 5}, {6, 8, 3}};
    double *exp[N_MAX] = {expp[0], expp[1], expp[2]};
    
    FILE *f = fopen("./out/tmp", "w");
    matrix_print_coord(f, exp, n, m, cnt_el);
    fclose(f);
    f = fopen("./out/tmp", "r");
    size_t tmp_n, tmp_m, tmp_cnt_el;
    fscanf(f, "%lu %lu %lu\n", &tmp_n, &tmp_m, &tmp_cnt_el);

    double **data = matrix_allocate(n, m);
    matrix_fill_null(data, n, m);
    int rc = matrix_read_coord(f, data, n, m, cnt_el);
    fclose(f);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(double_mtr_eq(data, n, m, exp, n, m), ERR_OK);
    
    matrix_free(data, n);
    
}
END_TEST

/// Чтение координат элементов - лишний элемент
START_TEST(test_matrix_read_coord_extra_line)
{
    size_t n = 3, m = 3, cnt_el = 3;
    double expp[N_MAX][M_MAX] = {{1, 0, 0}, {0, 2, 0}, {0, 0, 3}};
    double *exp[N_MAX] = {expp[0], expp[1], expp[2]};
    
    FILE *f = fopen("./out/tmp", "w");
    matrix_print_coord(f, exp, n, m, cnt_el);
    fprintf(f, "1 2 2\n");
    fclose(f);
    f = fopen("./out/tmp", "r");
    size_t tmp_n, tmp_m, tmp_cnt_el;
    fscanf(f, "%lu %lu %lu\n", &tmp_n, &tmp_m, &tmp_cnt_el);

    double **data = matrix_allocate(n, m);
    matrix_fill_null(data, n, m);
    int rc = matrix_read_coord(f, data, n, m, cnt_el);
    fclose(f);

    ck_assert_int_eq(rc, ERR_IO);
    ck_assert_int_eq(double_mtr_eq(data, n, m, exp, n, m), ERR_OK);
    
    matrix_free(data, n);
    
}
END_TEST

/// Чтение координат элементов матрицы - некорректная координата
START_TEST(test_matrix_read_coord_wrong_coord)
{
    size_t n = 3, m = 3, cnt_el = 4;
    double expp[N_MAX][M_MAX] = {{1, 0, 0}, {0, 2, 0}, {0, 0, 3}};
    double *exp[N_MAX] = {expp[0], expp[1], expp[2]};
    
    FILE *f = fopen("./out/tmp", "w");
    matrix_print_coord(f, exp, n, m, cnt_el);
    fprintf(f, "5 5 5\n");
    fclose(f);
    f = fopen("./out/tmp", "r");
    size_t tmp_n, tmp_m, tmp_cnt_el;
    fscanf(f, "%lu %lu %lu\n", &tmp_n, &tmp_m, &tmp_cnt_el);

    double **data = matrix_allocate(n, m);
    matrix_fill_null(data, n, m);
    int rc = matrix_read_coord(f, data, n, m, cnt_el);
    fclose(f);

    ck_assert_int_eq(rc, ERR_RANGE);
    ck_assert_int_eq(double_mtr_eq(data, n, m, exp, n, m), ERR_OK);
    
    matrix_free(data, n);
    
}
END_TEST

Suite* matrix_read_coord_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("matrix_read_coord");
    
    tc_pos = tcase_create("pos");
    tcase_add_test(tc_pos, test_matrix_read_coord_no_el);
    tcase_add_test(tc_pos, test_matrix_read_coord_few_el);
    tcase_add_test(tc_pos, test_matrix_read_coord_all_el);

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("neg");
    tcase_add_test(tc_neg, test_matrix_read_coord_extra_line);
    tcase_add_test(tc_neg, test_matrix_read_coord_wrong_coord);

    suite_add_tcase(s, tc_neg);

    return s;
}

/// Создание матрицы без значимых элементов
START_TEST(test_matrix_create_no_el)
{
    size_t n = 3, m = 3, cnt_el = 0;
    double expp[N_MAX][M_MAX] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    double *exp[N_MAX] = {expp[0], expp[1], expp[2]};
    
    FILE *f = fopen("./out/tmp", "w");
    matrix_print_coord(f, exp, n, m, cnt_el);
    fclose(f);
    f = fopen("./out/tmp", "r");
    
    double **data;
    size_t new_n, new_m;
    int rc = matrix_create(f, &data, &new_n, &new_m);
    fclose(f);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(double_mtr_eq(data, new_n, new_m, exp, n, m), ERR_OK);
    
    matrix_free(data, n);
    
}
END_TEST

/// Создание матрицы с неск. значимыми элементами
START_TEST(test_matrix_create_few_el)
{
    size_t n = 3, m = 3, cnt_el = 3;
    double expp[N_MAX][M_MAX] = {{1, 0, 0}, {0, 2, 0}, {0, 0, 3}};
    double *exp[N_MAX] = {expp[0], expp[1], expp[2]};
    
    FILE *f = fopen("./out/tmp", "w");
    matrix_print_coord(f, exp, n, m, cnt_el);
    fclose(f);
    f = fopen("./out/tmp", "r");

    double **data;
    size_t new_n, new_m;
    int rc = matrix_create(f, &data, &new_n, &new_m);
    fclose(f);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(double_mtr_eq(data, new_n, new_m, exp, n, m), ERR_OK);
    
    matrix_free(data, n);
    
}
END_TEST

/// Создание матрицы со всеми значимыми элементами
START_TEST(test_matrix_create_all_el)
{
    size_t n = 3, m = 3, cnt_el = 9;
    double expp[N_MAX][M_MAX] = {{1, 4, 7}, {9, 2, 5}, {6, 8, 3}};
    double *exp[N_MAX] = {expp[0], expp[1], expp[2]};
    
    FILE *f = fopen("./out/tmp", "w");
    matrix_print_coord(f, exp, n, m, cnt_el);
    fclose(f);
    f = fopen("./out/tmp", "r");

    double **data;
    size_t new_n, new_m;
    int rc = matrix_create(f, &data, &new_n, &new_m);
    fclose(f);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(double_mtr_eq(data, new_n, new_m, exp, n, m), ERR_OK);
    
    matrix_free(data, n);
    
}
END_TEST

/// Создание матрицы - лишний элемент
START_TEST(test_matrix_create_extra_line)
{
    size_t n = 3, m = 3, cnt_el = 3;
    double expp[N_MAX][M_MAX] = {{1, 0, 0}, {0, 2, 0}, {0, 0, 3}};
    double *exp[N_MAX] = {expp[0], expp[1], expp[2]};
    
    FILE *f = fopen("./out/tmp", "w");
    matrix_print_coord(f, exp, n, m, cnt_el);
    fprintf(f, "1 2 2\n");
    fclose(f);
    f = fopen("./out/tmp", "r");
    
    double **data;
    int rc = matrix_create(f, &data, &n, &m);
    fclose(f);

    ck_assert_int_eq(rc, ERR_IO);
    
    
}
END_TEST

/// Создание матрицы - некорректная координата
START_TEST(test_matrix_create_wrong_coord)
{
    size_t n = 3, m = 3, cnt_el = 4;
    double expp[N_MAX][M_MAX] = {{1, 0, 0}, {0, 2, 0}, {0, 0, 3}};
    double *exp[N_MAX] = {expp[0], expp[1], expp[2]};
    
    FILE *f = fopen("./out/tmp", "w");
    matrix_print_coord(f, exp, n, m, cnt_el);
    fprintf(f, "5 5 5\n");
    fclose(f);
    f = fopen("./out/tmp", "r");
    
    double **data;
    int rc = matrix_create(f, &data, &n, &m);
    fclose(f);

    ck_assert_int_eq(rc, ERR_RANGE);
    
    
}
END_TEST

Suite* matrix_create_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("matrix_create");
    
    tc_pos = tcase_create("pos");
    tcase_add_test(tc_pos, test_matrix_create_no_el);
    tcase_add_test(tc_pos, test_matrix_create_few_el);
    tcase_add_test(tc_pos, test_matrix_create_all_el);

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("neg");
    tcase_add_test(tc_neg, test_matrix_create_extra_line);
    tcase_add_test(tc_neg, test_matrix_create_wrong_coord);

    suite_add_tcase(s, tc_neg);

    return s;
}

/// Вывод матрицы в простом виде - 3х3
START_TEST(test_matrix_print_simple_neq3_meq3)
{
    size_t n = 3, m = 3;
    double expp[N_MAX][M_MAX] = {{1, 0, 0}, {0, 2, 0}, {0, 0, 3}};
    double *exp[N_MAX] = {expp[0], expp[1], expp[2]};
    
    FILE *f = fopen("./out/tmp", "w");
    matrix_print_simple(f, exp, n, m);
    fclose(f);

    size_t tmp_n, tmp_m;
    f = fopen("./out/tmp", "r");
    double **data = matrix_allocate(n, m);
    int rc = matrix_read_simple(f, data, &tmp_n, &tmp_m);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(double_mtr_eq(data, tmp_n, tmp_m, exp, n, m), ERR_OK);
    
    
    matrix_free(data, n);
    
}
END_TEST

/// Вывод матрицы в простом виде - 1х1
START_TEST(test_matrix_print_simple_neq1_meq1)
{
    size_t n = 1, m = 1;
    double expp[N_MAX][M_MAX] = {{1}};
    double *exp[N_MAX] = {expp[0]};
    
    FILE *f = fopen("./out/tmp", "w");
    matrix_print_simple(f, exp, n, m);
    fclose(f);

    size_t tmp_n, tmp_m;
    f = fopen("./out/tmp", "r");
    double **data = matrix_allocate(n, m);
    int rc = matrix_read_simple(f, data, &tmp_n, &tmp_m);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(double_mtr_eq(data, tmp_n, tmp_m, exp, n, m), ERR_OK);
    
    
    matrix_free(data, n);
    
}
END_TEST   

Suite* matrix_print_simple_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("matrix_print_simple");
    
    core = tcase_create("tests");
    tcase_add_test(core, test_matrix_print_simple_neq3_meq3);
    tcase_add_test(core, test_matrix_print_simple_neq1_meq1);

    suite_add_tcase(s, core);

    return s;
}
