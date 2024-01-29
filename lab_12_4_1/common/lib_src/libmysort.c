#include "libmysort.h"
#include <string.h>
#include <stdlib.h>

int int_cmp(const void *l, const void *r)
{
    const int *pl = l, *pr = r;
    return *pl - *pr;
}

void *bin_search(void *pbeg, void *pi, size_t size, void *key, int (*cmp)(const void *, const void *))
{
    char *plo = pbeg, *phi = pi, *pmid;

    while (plo < phi)
    {
        pmid = plo + ((phi - plo) / 2) / size * size;
        if (cmp(key, pmid) < 0)
            phi = pmid;
        else
            plo = pmid + size;
    }

    return plo;
}

void mysort(void *ptr, size_t count, size_t size, int (*cmp)(const void *, const void *))
{
    char *pbeg = ptr;
    char *pend = pbeg + count * size;
    char *pcurr;
    char key[size];

    for (char *pi = pbeg; pi < pend; pi += size)
    {
        memcpy(key, pi, size);
        pcurr = bin_search(pbeg, pi, size, key, cmp);
        memmove(pcurr + size, pcurr, pi - pcurr);
        memcpy(pcurr, key, size);
    }
}
