#include <check.h>
#include <stdio.h>
#include "node_list.h"

/// Корректные данные
START_TEST(test_node)
{
    int x = 1, y = 2;
    node_t *exp = node_create(x, y);
    ck_assert_ptr_nonnull(exp);

    FILE *f = fopen("./out/tmp", "w");
    node_print(f, exp);
    fclose(f);

    int num, pow;
    f = fopen("./out/tmp", "r");
    fscanf(f, "%d %d", &num, &pow);
    fclose(f);
    ck_assert_int_eq(x, num);
    ck_assert_int_eq(y, pow);

    node_free(exp);
}
END_TEST

Suite* node_io_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("node_io");
    
    core = tcase_create("core");
    tcase_add_test(core, test_node);

    suite_add_tcase(s, core);

    return s;
}
