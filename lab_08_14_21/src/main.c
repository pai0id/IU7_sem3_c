#include "mtr_io.h"
#include "mtr_op.h"
#include "mtr_alloc.h"
#include "err.h"
#include <string.h>

int main(int argc, char **argv)
{
    int rc = OK;
    FILE *f1 = NULL, *f2 = NULL, *f_res = NULL;
    double **mtr1, **mtr2, **res;
    size_t n1, m1, n2, m2, n_res, m_res;

    if (((argc == 5 && (strcmp(argv[1], "a") == 0 || strcmp(argv[1], "m") == 0))
        || (argc == 4 && strcmp(argv[1], "o") == 0)))
    {
        f1 = fopen(argv[2], "r");
        if (f1 == NULL)
            rc = ERR_NO_FILE;
        if (!rc)
            rc = matrix_create(f1, &mtr1, &n1, &m1);
        if (!rc)
        {
            if (argc == 4)
            {
                rc = matrix_calc_rev(mtr1, n1, m1, &res, &n_res, &m_res);
                if (!rc)
                {
                    f_res = fopen(argv[3], "w");
                    if (f_res == NULL)
                        rc = ERR_NO_FILE;
                    else
                        matrix_print_simple(f_res, res, n_res, m_res);
                    matrix_free(res, n_res);
                }
            }
            else
            {
                f2 = fopen(argv[3], "r");
                if (f2 == NULL)
                    rc = ERR_NO_FILE;
                if (!rc)
                    rc = matrix_create(f2, &mtr2, &n2, &m2);
                if (!rc)
                {
                    if (strcmp(argv[1], "a") == 0)
                        rc = matrix_add(mtr1, n1, m1, mtr2, n2, m2, &res, &n_res, &m_res);
                    else
                        rc = matrix_mult(mtr1, n1, m1, mtr2, n2, m2, &res, &n_res, &m_res);
                    if (!rc)
                    {
                        f_res = fopen(argv[4], "w");
                        if (f_res == NULL)
                            rc = ERR_NO_FILE;
                        else
                            matrix_print_simple(f_res, res, n_res, m_res);
                        matrix_free(res, n_res);
                    }
                    matrix_free(mtr2, n2);
                }
            }
            matrix_free(mtr1, n1);
        }
    }
    else
        rc = ERR_ARGS;
    
    if (f1 != NULL)
        fclose(f1);
    if (f2 != NULL)
        fclose(f2);
    if (f_res != NULL)
        fclose(f_res);
    return rc;
}
