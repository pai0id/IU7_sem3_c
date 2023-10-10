#include "check_arr.c"
#include "check_filter.c"
#include "check_mysort.c"
#include <check.h>

int main(void)
{
    int failed = 0;
    Suite *s[10];
    SRunner *runner;

    s[0] = print_arr_suite();
    s[1] = get_arr_suite();
    s[2] = mysort_suite();
    s[3] = key_suite();
    s[4] = cnt_elements_suite();
    s[5] = read_arr_suite();
    s[6] = calculate_avr_suite();
    s[7] = count_above_avr_suite();
    s[8] = copy_above_avr_suite();
    s[9] = bin_search_suite();

    for (size_t i = 0; failed == 0 && i < 10; ++i)
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
