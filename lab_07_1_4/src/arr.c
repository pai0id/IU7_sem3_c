#include "arr.h"
#include <stdlib.h>

int cnt_elements(FILE *f, int *cnt)
{
    int curr;
    *cnt = 0;
    while (fscanf(f, "%d", &curr) == 1)
        (*cnt)++;
    if (!feof(f))
        return ERR_IO;
    rewind(f);
    return OK;
}

int read_arr(FILE *f, int **pb, int **pe)
{
    int *write = *pb, curr;
    while (fscanf(f, "%d", &curr) == 1)
        *write++ = curr;
    if (!feof(f))
        return ERR_IO;
    *pe = write;
    return OK;
}

int get_arr(FILE *f, int **pb, int **pe)
{
    int rc, cnt;
    rc = cnt_elements(f, &cnt);

    if (rc)
        return rc;
    if (cnt == 0)
        return ERR_FILE_EMPTY;
    *pb = malloc(sizeof(int) * cnt);
    if (*pb == NULL)
        return ERR_MEM;
    read_arr(f, pb, pe);
    return OK;
}

void print_arr(FILE *f, const int *pb, const int *pe)
{
    for (const int *curr = pb; curr < pe; ++curr)
        fprintf(f, "%d ", *curr);
}
