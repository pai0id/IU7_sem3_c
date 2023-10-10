#include "film_arr.h"
#include <string.h>

int film_insert(struct film_t *film_arr, size_t *pn, struct film_t *film, size_t index)
{
    if (index > *pn)
        return ERR_RANGE;
    else
    {
        for (size_t i = *pn; i > index; --i)
            film_arr[i] = film_arr[i - 1];
        film_arr[index] = *film;
        (*pn)++;
    }
    return OK;
}

// int fa_read_sorted_by_field(FILE *f, struct film_t *film_arr, size_t n_max, size_t *pn, char *field)
// {
//     struct film_t curr;
//     size_t i, n = 0;
//     int rc = OK;
//     while (!rc)
//     {
//         rc = film_read(f, &curr);
//         if (!rc)
//         {
//             if (n < n_max)
//             {
//                 i = 0;
//                 if (strcmp(field, TITLE) == 0)
//                 {
//                     while (i < n && film_cmp_by_title(&film_arr[i], &curr) <= 0)
//                         i++;
//                     rc = film_insert(film_arr, &n, &curr, i);
//                 }
//                 else if (strcmp(field, NAME) == 0)
//                 {
//                     while (i < n && film_cmp_by_name(&film_arr[i], &curr) <= 0)
//                         i++;
//                     rc = film_insert(film_arr, &n, &curr, i);
//                 }
//                 else if (strcmp(field, YEAR) == 0)
//                 {
//                     while (i < n && film_cmp_by_year(&film_arr[i], &curr) <= 0)
//                         i++;
//                     rc = film_insert(film_arr, &n, &curr, i);
//                 }
//             }
//             else
//                 rc = ERR_OVERFLOW;
//         }
//     }
//     *pn = n;
//     if (rc && feof(f))
//         rc = OK;
//     return rc;
// }

size_t find_pos(size_t n, struct film_t *film_arr, struct film_t *curr, cmp_t cmp)
{
    size_t i = 0;
    while (i < n && cmp(&film_arr[i], curr) <= 0)
        i++;
    return i;
}

int fa_read_sorted_by_field(FILE *f, struct film_t *film_arr, size_t n_max, size_t *pn, cmp_t cmp)
{
    struct film_t curr;
    size_t i, n = 0;
    int rc = OK;
    while (!rc)
    {
        rc = film_read(f, &curr);
        if (!rc)
        {
            if (n < n_max)
            {
                i = find_pos(n, film_arr, &curr, cmp);
                rc = film_insert(film_arr, &n, &curr, i);
            }
            else
                rc = ERR_OVERFLOW;
        }
    }
    *pn = n;
    if (rc && feof(f))
        rc = OK;
    return rc;
}

void fa_print(FILE *f, const struct film_t *film_arr, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        film_print(f, &film_arr[i]);
}

int bin_search_by_field(const struct film_t *film_arr, size_t size, const struct film_t *key, cmp_t cmp)
{
    int mid, l = 0, r = size - 1;
    
    while (l <= r)
    {
        mid = l + (r - l) / 2;
        if (cmp(&film_arr[mid], key) == 0)
        {
            film_print(stdout, &film_arr[mid]);
            return OK;
        }
        else if (cmp(&film_arr[mid], key) < 0)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return ERR_NOT_FOUND;
}
