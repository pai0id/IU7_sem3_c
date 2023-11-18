#include "film_arr.h"
#include <string.h>

int fa_count(FILE *f, size_t *n)
{
    struct film_t tmp = { NULL, NULL, 0 };
    int rc = OK, cnt = 0;
    while (!rc)
    {
        rc = film_read(f, &tmp);
        if (!rc)
        {
            cnt++;
            film_free_content(&tmp);
        }
    }
    *n = cnt;
    if (rc == ERR_END && feof(f))
        return OK;
    return rc;
}

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

size_t find_pos(size_t n, struct film_t *film_arr, struct film_t *curr, cmp_t cmp)
{
    size_t i = 0;
    while (i < n && cmp(&film_arr[i], curr) <= 0)
        i++;
    return i;
}

void fa_free(struct film_t *film_arr, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        film_free_content(&film_arr[i]);
    free(film_arr);
}

int fa_create(FILE *f, struct film_t **film_arr, size_t *n_films, cmp_t cmp)
{
    struct film_t *ptmp;
    size_t n = 0;
    int rc;

    *film_arr = NULL;
    *n_films = 0;

    rc = fa_count(f, &n);
    if (!n)
        rc = ERR_EMPTY;
    if (!rc)
    {
        ptmp = calloc(n, sizeof(struct film_t));
        if (!ptmp)
            rc = ERR_MEM;
        else
        {
            rewind(f);
            rc = fa_read_sorted_by_field(f, ptmp, n, cmp);
            if (!rc)
            {
                *film_arr = ptmp;
                *n_films = n;
            }
            else
                fa_free(ptmp, n);
        }
    }
    return rc;
}

int fa_read_sorted_by_field(FILE *f, struct film_t *film_arr, size_t n, cmp_t cmp)
{
    struct film_t curr;
    memset(&curr, 0, sizeof(struct film_t));
    size_t pos, n_filled = 0;
    int rc = OK;
    for (size_t i = 0; i < n && !rc; ++i)
    {
        rc = film_read(f, &curr);
        if (!rc)
        {
            pos = find_pos(n_filled, film_arr, &curr, cmp);
            rc = film_insert(film_arr, &n_filled, &curr, pos);
            memset(&curr, 0, sizeof(struct film_t));
        }
    }
    if (rc == ERR_END && feof(f))
        rc = OK;
    return rc;
}

void fa_print(FILE *f, const struct film_t *film_arr, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        film_print(f, &film_arr[i]);
}

int bin_search_by_field(const struct film_t *film_arr, struct film_t *film, size_t size, const struct film_t *key, cmp_t cmp)
{
    int mid, l = 0, r = size - 1;
    
    while (l <= r)
    {
        mid = l + (r - l) / 2;
        if (cmp(&film_arr[mid], key) == 0)
        {
            *film = film_arr[mid];
            return OK;
        }
        else if (cmp(&film_arr[mid], key) < 0)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return ERR_NOT_FOUND;
}
