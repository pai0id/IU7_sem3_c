#include "film.h"
#include <string.h>
#include <sys/types.h>

void film_init_content(struct film_t *fp, char *title, char *name, int year)
{
    film_free_content(fp);
    fp->title = title;
    fp->name = name;
    fp->year = year;
}

void film_free_content(struct film_t *fp)
{
    free(fp->title);
    fp->title = NULL;
    free(fp->name);
    fp->name = NULL;
}

int film_read(FILE *f, struct film_t *fp)
{
    char *buf_title = NULL;
    size_t len = 0;
    ssize_t read_title;
    char *buf_name = NULL;
    ssize_t read_name;
    int year;
    int rc = OK;
    
    if ((read_title = getline(&buf_title, &len, f)) == -1)
        rc = ERR_IO;
    if (read_title > 1)
    {
        buf_title[read_title - 1] = 0;
        if ((read_name = getline(&buf_name, &len, f)) == -1)
            rc = ERR_IO;
        if (read_name > 1)
        {
            buf_name[read_name - 1] = 0;
            if (fscanf(f, "%d\n", &year) != 1)
                rc = ERR_IO;
            else
            {
                if (year <= 0)
                    rc = ERR_RANGE;
                else
                    film_init_content(fp, buf_title, buf_name, year);
            }
        }
        else
            rc = ERR_RANGE;
    }
    else
        rc = ERR_END;
    if (rc)
    {
        free(buf_title);
        free(buf_name);
    }
    return rc;
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
