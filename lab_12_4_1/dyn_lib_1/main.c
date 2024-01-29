#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libarr.h"
#include "libmysort.h"
#include "libfilter.h"
#include "err.h"

int main(int argc, char **argv)
{
    int rc = OK;
    FILE *f_in = NULL, *f_out = NULL;
    int *pb = NULL, *pe = NULL;
    int *pb_new = NULL, *pe_new = NULL;

    if (argc == 3 || (argc == 4 && strcmp(argv[3], "f") == 0))
    {
        f_in = fopen(argv[1], "r");
        if (f_in == NULL)
            rc = ERR_NO_FILE;
        if (!rc)
            rc = get_arr(f_in, &pb, &pe);
        if (!rc)
        {
            if (argc == 4)
            {
                double avr;
                size_t count;
                rc = calculate_avr(pb, pe, &avr);
                if (!rc)
                    rc = count_above_avr(pb, pe, avr, &count);
                if (!rc)
                    rc = alloc_arr(&pb_new, &pe_new, count);
                if (!rc)
                {
                    rc = key(pb, pe, &pb_new, &pe_new);
                    free_arr(&pb, &pe);
                    pb = pb_new;
                    pe = pe_new;
                }
            }
            if (!rc)
            {
                mysort(pb, pe - pb, sizeof(int), int_cmp);
                f_out = fopen(argv[2], "w");
                if (f_out == NULL)
                    rc = ERR_NO_FILE;
                if (!rc)
                    print_arr(f_out, pb, pe);
            }
        }
    }
    else
        rc = ERR_ARGS;
    if (f_in != NULL)
        fclose(f_in);
    if (f_out != NULL)
        fclose(f_out);

    if (pb)
        free_arr(&pb, &pe);

    return rc;
}
