#include "check_alloc.c"
#include "check_io.c"
#include "check_op.c"
#include <check.h>

#define N_TESTS 12

int main(void)
{
    int failed = 0;
    Suite *s[N_TESTS];
    SRunner *runner;

    s[0] = matrix_allocate_suite();
    s[1] = matrix_fill_null_suite();
    s[2] = matrix_fill_d_ones_suite();
    s[3] = matrix_copy_suite();
    s[4] = matrix_read_coord_suite();
    s[5] = matrix_create_suite();
    s[6] = matrix_print_simple_suite();
    s[7] = matrix_mult_suite();
    s[8] = matrix_add_suite();
    s[9] = solve_eq_suite();
    s[10] = matrix_transpose_suite();
    s[11] = matrix_calc_rev_suite();


    for (size_t i = 0; failed == 0 && i < N_TESTS; ++i)
    {
        runner = srunner_create(s[i]);

        srunner_run_all(runner, CK_VERBOSE);

        failed = srunner_ntests_failed(runner);

        srunner_free(runner);
    }

    if (failed)
        printf("\n\033[1;31m FAILED TESTS: %d\n", failed);
    else
        printf("\n\033[0;32m PASSED ALL TESTS\n");
    return failed;
}
