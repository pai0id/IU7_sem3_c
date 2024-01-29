#include "check_arr_io.h"
#include "check_arr_rem.h"
#include "check_arr_clear.h"
#include "check_arr_each.h"
#include "check_arr_min.h"
#include "check_arr_max.h"
#include <check.h>
#include <stdio.h>

#define N_TESTS 6

int main(void)
{
    int failed = 0;
    Suite *s[N_TESTS];
    SRunner *runner;

    s[0] = arr_io_suite();
    s[1] = arr_rem_suite();
    s[2] = arr_clear_suite();
    s[3] = arr_each_suite();
    s[4] = arr_min_suite();
    s[5] = arr_max_suite();

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
