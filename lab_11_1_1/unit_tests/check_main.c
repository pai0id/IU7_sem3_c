#include <stdlib.h>
#include <check.h>
#include <stdio.h>

#include "check_my_snprintf.c"

#define N_TESTS 4

int main(void)
{
    int failed = 0;
    Suite *s[N_TESTS];
    SRunner *runner;

    s[0] = my_snprintf_suite();
    s[1] = insert_suite();
    s[2] = snprint_to_octal_suite();
    s[3] = ncpy_str_suite();

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
