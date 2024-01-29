#include <check.h>
#include <stdio.h>
#include "node_list.h"
#include "check_func.h"

#define EPS 0.0000001

/// data - int*
START_TEST(test_node_int)
{
    int x = 42;
    node_t *exp = node_create(&x);
    ck_assert_ptr_nonnull(exp);

    FILE *f = fopen("./out/tmp", "w");
    node_print(f, exp, print_int);
    fclose(f);

    int read;
    f = fopen("./out/tmp", "r");
    fscanf(f, "%d", &read);
    fclose(f);
    ck_assert_int_eq(x, read);

    node_free(exp);
}
END_TEST

/// data - double*
START_TEST(test_node_double)
{
    double x = 42.42;
    node_t *exp = node_create(&x);
    ck_assert_ptr_nonnull(exp);

    FILE *f = fopen("./out/tmp", "w");
    node_print(f, exp, print_double);
    fclose(f);

    double read;
    f = fopen("./out/tmp", "r");
    fscanf(f, "%lf", &read);
    fclose(f);
    ck_assert_double_eq_tol(x, read, EPS);

    node_free(exp);
}
END_TEST

Suite* node_io_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("node_io");
    
    core = tcase_create("core");
    tcase_add_test(core, test_node_int);
    tcase_add_test(core, test_node_double);

    suite_add_tcase(s, core);

    return s;
}
