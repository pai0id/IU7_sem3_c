#include "libfilter.h"

int calculate_avr(const int *pb_src, const int *pe_src, double *avr)
{
    if (pb_src == pe_src)
        return LIB_ERR_SIZE;

    *avr = 0;
    int cnt = 0;
    for (const int *curr = pb_src; curr < pe_src; ++curr)
    {
        *avr += *curr;
        cnt++;
    }

    *avr /= cnt;
    return LIB_OK;
}

int count_above_avr(const int *pb_src, const int *pe_src, double avr, size_t *count)
{
    size_t cnt = 0;
    for (const int *curr = pb_src; curr < pe_src; ++curr)
    {
        if (*curr > avr)
            cnt++;
    }

    if (cnt == 0)
        return LIB_ERR_SIZE;

    *count = cnt;
    return LIB_OK;
}

int fill_above_avr(const int *pb_src, const int *pe_src, double avr, int **write, int *end)
{
    for (const int *read = pb_src; read < pe_src; ++read)
    {
        if (*read > avr)
        {
            if (*write >= end)
                return LIB_ERR_SIZE;
            *(*write)++ = *read;
        }
    }
    return LIB_OK;
}

int copy_above_avr(const int *pb_src, const int *pe_src, double avr, int **pb_dst, int **pe_dst)
{
    int *write = *pb_dst;
    int rc = fill_above_avr(pb_src, pe_src, avr, &write, *pe_dst);

    *pe_dst = write;
    if (!rc && *pb_dst == *pe_dst)
        rc = LIB_ERR_SIZE;
    return rc;
}

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    double avr;
    int rc = calculate_avr(pb_src, pe_src, &avr);
    if (rc)
        return rc;

    return copy_above_avr(pb_src, pe_src, avr, pb_dst, pe_dst);
}
