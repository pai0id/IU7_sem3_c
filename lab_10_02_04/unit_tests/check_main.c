#include "check_node_list.c"
#include "check_list.c"
#include "check_operations.c"
#include "check_func.h"
#include <check.h>

#define N_TESTS 8

int main(void)
{
    int failed = 0;
    Suite *s[N_TESTS];
    SRunner *runner;

    s[0] = node_io_suite();
    s[1] = init_list_from_num_suite();
    s[2] = get_num_from_list_suite();
    s[3] = print_num_suite();
    s[4] = mul_nums_suite();
    s[5] = sqr_num_suite();
    s[6] = reduce_nums_suite();
    s[7] = div_nums_suite();

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
