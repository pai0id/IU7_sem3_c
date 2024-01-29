#include "filter.h"

int calculate_avr(const int *pb_src, const int *pe_src, double *avr)
{
    if (pb_src == pe_src)
        return ERR_SIZE;

    *avr = 0;
    int cnt = 0;
    for (const int *curr = pb_src; curr < pe_src; ++curr)
    {
        *avr += *curr;
        cnt++;
    }

    *avr /= cnt;
    return OK;
}

int count_above_avr(const int *pb_src, const int *pe_src, double avr, int *count)
{
    int cnt = 0;
    for (const int *curr = pb_src; curr < pe_src; ++curr)
    {
        if (*curr > avr)
            cnt++;
    }

    if (cnt == 0)
        return ERR_SIZE;

    *count = cnt;
    return OK;
}

void fill_above_avr(const int *pb_src, const int *pe_src, double avr, int *write)
{
    for (const int *read = pb_src; read < pe_src; ++read)
    {
        if (*read > avr)
            *write++ = *read;
    }
}

int copy_above_avr(const int *pb_src, const int *pe_src, double avr, int **pb_dst, int **pe_dst)
{
    int count;
    int rc = count_above_avr(pb_src, pe_src, avr, &count);
    if (rc)
        return rc;

    *pb_dst = malloc(sizeof(int) * count);
    if (*pb_dst == NULL)
        return ERR_MEM;

    int *write = *pb_dst;
    fill_above_avr(pb_src, pe_src, avr, write);

    *pe_dst = write + count;
    return OK;
}

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    double avr;
    int rc = calculate_avr(pb_src, pe_src, &avr);
    if (rc)
        return rc;

    return copy_above_avr(pb_src, pe_src, avr, pb_dst, pe_dst);
}

