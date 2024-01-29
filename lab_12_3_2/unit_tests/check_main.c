#include "check_arr.c"
#include <check.h>

int main(void)
{
    int failed = 0;
    Suite *s[2];
    SRunner *runner;

    s[0] = fill_primes_suite();
    s[1] = ncpy_and_add_suite();

    for (size_t i = 0; failed == 0 && i < 2; ++i)
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
