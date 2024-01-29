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

void fa_free(struct film_t *film_arr, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        film_free_content(&film_arr[i]);
    free(film_arr);
}

int fa_create(FILE *f, struct film_t **film_arr, size_t *n_films)
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
            rc = fa_read(f, ptmp, n);
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

int fa_read(FILE *f, struct film_t *film_arr, size_t n)
{
    int rc = OK;
    for (size_t i = 0; i < n && !rc; ++i)
        rc = film_read(f, &film_arr[i]);
    if (rc == ERR_END && feof(f))
        rc = OK;
    return rc;
}
