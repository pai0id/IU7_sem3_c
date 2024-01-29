#include "libarr.h"
#include <stdlib.h>

int cnt_elements(FILE *f, int *cnt)
{
    int curr;
    *cnt = 0;
    while (fscanf(f, "%d", &curr) == 1)
        (*cnt)++;
    if (!feof(f))
        return LIB_ERR_IO;
    rewind(f);
    return LIB_OK;
}

int read_arr(FILE *f, int **pb, int **pe)
{
    int *write = *pb, curr;
    while (fscanf(f, "%d", &curr) == 1)
        *write++ = curr;
    if (!feof(f))
        return LIB_ERR_IO;
    *pe = write;
    return LIB_OK;
}

int get_arr(FILE *f, int **pb, int **pe)
{
    int rc, cnt;
    rc = cnt_elements(f, &cnt);

    if (rc)
        return rc;
    if (cnt == 0)
        return LIB_ERR_FILE_EMPTY;
    *pb = malloc(sizeof(int) * cnt);
    if (*pb == NULL)
        return LIB_ERR_MEM;
    read_arr(f, pb, pe);
    return LIB_OK;
}

int alloc_arr(int **pb, int **pe, size_t size)
{
    int *tmp = malloc(sizeof(int) * size);
    if (!tmp)
        return LIB_ERR_MEM;    
    *pb = tmp;
    *pe = tmp + size;
    return LIB_OK;
}

void free_arr(int **pb, int **pe)
{
    free(*pb);
    *pb = NULL;
    *pe = NULL;
}

void print_arr(FILE *f, const int *pb, const int *pe)
{
    for (const int *curr = pb; curr < pe; ++curr)
        fprintf(f, "%d ", *curr);
}
