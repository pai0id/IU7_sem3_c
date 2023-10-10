#include "film.h"
#include <string.h>

int str_read(FILE *f, char *str, size_t size, size_t max_size)
{
    size_t len;

    if (!fgets(str, size, f))
        return ERR_IO;
    len = strlen(str);
    if (len && str[len - 1] == '\n')
    {
        str[len - 1] = 0;
        len--;
    }
    if (!len || len > max_size)
        return ERR_RANGE;
    return OK;
}

int film_read(FILE *f, struct film_t *fp)
{
    char buf_title[TITLE_LEN + 7];
    char buf_name[NAME_LEN + 7];
    char tmp[7];
    int year;
    int rc;

    rc = str_read(f, buf_title, sizeof(buf_title), TITLE_LEN);
    if (rc)
        return rc;
    
    rc = str_read(f, buf_name, sizeof(buf_name), NAME_LEN);
    if (rc)
        return rc;

    if (fscanf(f, "%d", &year) != 1)
        return ERR_IO;
    if (year <= 0)
        return ERR_RANGE;
    fgets(tmp, sizeof(tmp), f);

    strcpy(fp->title, buf_title);
    strcpy(fp->name, buf_name);
    fp->year = year;
    return OK;
}

void film_print(FILE *f, const struct film_t *fp)
{
    fprintf(f, "%s\n%s\n%d\n", fp->title, fp->name, fp->year);
}

int film_cmp_by_title(const struct film_t *lp, const struct film_t *rp)
{
    return strcmp(lp->title, rp->title);
}

int film_cmp_by_name(const struct film_t *lp, const struct film_t *rp)
{
    return strcmp(lp->name, rp->name);
}

int film_cmp_by_year(const struct film_t *lp, const struct film_t *rp)
{
    if (lp->year > rp->year)
        return 1;
    else if (lp->year == rp->year)
        return 0;
    else
        return -1;
}
