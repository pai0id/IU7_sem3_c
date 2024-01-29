#include "check_film.c"
#include "check_film_arr.c"
#include "check_node_list.c"
#include "check_list.c"
#include "check_task_funcs.c"
#include "check_func.h"
#include <check.h>

#define N_TESTS 14

int main(void)
{
    int failed = 0;
    Suite *s[N_TESTS];
    SRunner *runner;

    s[0] = film_io_suite();
    s[1] = film_cmp_title_suite();
    s[2] = fa_count_suite();
    s[3] = fa_io_suite();
    s[4] = node_io_suite();
    s[5] = list_add_tail_suite();
    s[6] = init_list_from_film_arr_suite();
    s[7] = list_print_suite();
    s[8] = find_suite();
    s[9] = insert_suite();
    s[10] = remove_duplicates_suite();
    s[11] = front_back_split_suite();
    s[12] = sorted_merge_suite();
    s[13] = sort_suite();

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
