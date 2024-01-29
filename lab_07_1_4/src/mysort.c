#include "mysort.h"
#include <string.h>
#include <stdlib.h>

// Сортировка выбором + другая реализация функции обмена без VLA

int int_cmp(const void *l, const void *r)
{
    const int *pl = l, *pr = r;
    return *pl - *pr;
}

// void *bin_search(void *pbeg, void *pi, size_t size, void *key, int (*cmp)(const void *, const void *))
// {
//     char *plo = pbeg, *phi = pi, *pmid;

//     while (plo < phi)
//     {
//         /// Вычисление указателя на середину памяти в текущем сегменте для выполнения бинарного поиска,
//         /// выравнивая назад так, чтобы он указывал на начало элемента.
//         ///
//         /// Массив {0, 1, 10}:
//         /// 0x00000000 0x00000001 0x0000000a
//         ///                 ^Середина области памяти
//         ///               <--
//         ///               V Начало элемента
//         ///  0x00000000 0x00000001 0x0000000a
//         ///
//         pmid = plo + ((phi - plo) / 2) / size * size;
//         if (cmp(key, pmid) < 0)
//             phi = pmid;
//         else
//             plo = pmid + size;
//     }

//     return plo;
// }

// void mysort(void *ptr, size_t count, size_t size, int (*cmp)(const void *, const void *))
// {
//     char *pbeg = ptr;
//     char *pend = pbeg + count * size;
//     char *pcurr;
//     char key[size];

//     for (char *pi = pbeg; pi < pend; pi += size)
//     {
//         memcpy(key, pi, size);
//         pcurr = bin_search(pbeg, pi, size, key, cmp);
//         memmove(pcurr + size, pcurr, pi - pcurr);
//         memcpy(pcurr, key, size);
//     }
// }

void elem_swap(void *l, void *r, size_t n)
{
    char tmp;
    char *pl = l, *pr = r;
    for (size_t i = 0; i < n; ++i)
    {
        tmp = *pl;
        *pl = *pr;
        *pr = tmp;
        pr++;
        pl++;
    }
}

void mysort(void *ptr, size_t count, size_t size, int (*cmp)(const void *, const void *))
{
    char *pbeg = ptr;
    char *pend = pbeg + count * size;
    char *pmin;

    for (char *pi = pbeg; pi < pend; pi += size)
    {
        pmin = pi;
        for (char *pj = pi + size; pj < pend; pj += size)
            if (cmp(pj, pmin) < 0)
                pmin = pj;
        elem_swap(pmin, pi, size);
    }
}
