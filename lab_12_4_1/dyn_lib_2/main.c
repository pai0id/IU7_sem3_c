#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>
#include "err.h"

typedef int (*fn_get_arr_t)(FILE *, int **, int **);
typedef void (*fn_free_arr_t)(int **pb, int **pe);
typedef int (*fn_calculate_avr_t)(const int *pb_src, const int *pe_src, double *avr);
typedef int (*fn_count_above_avr_t)(const int *pb_src, const int *pe_src, double avr, size_t *count);
typedef int (*fn_key_t)(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
typedef int (*fn_int_cmp_t)(const void *l, const void *r);
typedef void (*fn_mysort_t)(void *ptr, size_t count, size_t size, int (*cmp)(const void *, const void *));
typedef void (*fn_print_arr_t)(FILE *f, const int *pb, const int *pe);
typedef int (*fn_alloc_arr_t)(int **pb, int **pe, size_t size);

int main(int argc, char **argv)
{
    void* hlibarr;
    void* hlibfilter;
    fn_get_arr_t get_arr;
    fn_free_arr_t free_arr;
    fn_calculate_avr_t calculate_avr;
    fn_count_above_avr_t count_above_avr;
    fn_key_t key;
    fn_int_cmp_t int_cmp;
    fn_mysort_t mysort;
    fn_print_arr_t print_arr;
    fn_alloc_arr_t alloc_arr;

    hlibarr = dlopen("./libarr.so", RTLD_NOW);
    if (!hlibarr)
        return ERR_LIB;
    hlibfilter = dlopen("./libfilter.so", RTLD_NOW);
    if (!hlibfilter)
    {
        dlclose(hlibarr);
        return ERR_LIB;
    }

    get_arr = (fn_get_arr_t) dlsym(hlibarr, "get_arr");
    free_arr = (fn_free_arr_t) dlsym(hlibarr, "free_arr");
    calculate_avr = (fn_calculate_avr_t) dlsym(hlibfilter, "calculate_avr");
    count_above_avr = (fn_count_above_avr_t) dlsym(hlibfilter, "count_above_avr");
    key = (fn_key_t) dlsym(hlibfilter, "key");
    int_cmp = (fn_int_cmp_t) dlsym(hlibarr, "int_cmp");
    mysort = (fn_mysort_t) dlsym(hlibarr, "mysort");
    print_arr = (fn_print_arr_t) dlsym(hlibarr, "print_arr");
    alloc_arr = (fn_alloc_arr_t) dlsym(hlibarr, "alloc_arr");
    if (!get_arr || !free_arr || !calculate_avr || !count_above_avr || !key || !mysort || !print_arr || !alloc_arr)
    {
        dlclose(hlibarr);
        dlclose(hlibfilter);
        return ERR_DYN_FN;
    }

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

    dlclose(hlibarr);
    dlclose(hlibfilter);

    return rc;
}
