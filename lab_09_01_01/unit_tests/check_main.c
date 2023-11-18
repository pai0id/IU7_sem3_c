#include "check_film.c"
#include "check_film_arr.c"
#include <check.h>

#define N_TESTS 9

int main(void)
{
    int failed = 0;
    Suite *s[N_TESTS];
    SRunner *runner;

    s[0] = film_io_suite();
    s[1] = film_cmp_title_suite();
    s[2] = film_cmp_name_suite();
    s[3] = film_cmp_year_suite();
    s[4] = fa_count_suite();
    s[5] = film_insert_suite();
    s[6] = find_pos_suite();
    s[7] = bin_search_by_field_suite();
    s[8] = fa_io_suite();

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
