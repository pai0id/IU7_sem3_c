/**
 *  \author Андрей ИУ7-32Б
 * 
 *  Вариант 1
 * 
 *  Программа, обрабатывающая файл со структурами.
 *  Вид структуры:
 *  а) Название фильма (<= 25 симв.)
 *  б) Фамилия режисера (<= 25 симв.)
 *  в) Год выхода
 * 
 *  Необходимо считать информацию из файла в массив,
 *  сразу упорядочивая по заданному полю.
 * 
 *  Если ключ поиска не указан, вывести массив.
 * 
 *  Если ключ указан, выполнить бинарный поиск по полю и ключу.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "err.h"
#include "film_arr.h"
#include "film.h"

int main(int argc, char **argv)
{
    int rc;
    struct film_t film_arr[N_MAX];
    size_t size;
    FILE *f = NULL;
    cmp_t cmp;

    if ((argc == 3 || argc == 4) && (strcmp(argv[2], TITLE) == 0 ||
        strcmp(argv[2], NAME) == 0 || strcmp(argv[2], YEAR) == 0))
    {
        f = fopen(argv[1], "r");
        if (f == NULL)
            rc = ERR_NO_FILE;
        else
        {
            if (strcmp(argv[2], TITLE) == 0)
                cmp = film_cmp_by_title;
            else if (strcmp(argv[2], NAME) == 0)
                cmp = film_cmp_by_name;
            else
                cmp = film_cmp_by_year;
            rc = fa_read_sorted_by_field(f, film_arr, N_MAX, &size, cmp);
        }
        if (!rc)
        {
            if (size == 0)
                rc = ERR_EMPTY;
            else if (argc == 4)
            {
                char *tmp;
                if (strcmp(argv[2], YEAR) == 0)
                {
                    tmp = argv[3];
                    while (*tmp)
                        if (isdigit(*tmp++) == 0)
                            return ERR_ARGS;
                }
                struct film_t key;
                if (strcmp(argv[2], TITLE) == 0)
                    strcpy(key.title, argv[3]);
                else if (strcmp(argv[2], NAME) == 0)
                    strcpy(key.name, argv[3]);
                else
                    key.year = atoi(argv[3]);

                rc = bin_search_by_field(film_arr, size, &key, cmp);
                if (rc == ERR_NOT_FOUND)
                {
                    printf("Not found\n");
                    rc = OK;
                }
            }
            else
                fa_print(stdout, film_arr, size);
        }
    }
    else
        rc = ERR_ARGS;
    if (f != NULL)
        fclose(f);

    return rc;
}
