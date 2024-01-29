/**
 *  \author Андрей ИУ7-32Б
 * 
 *  Программа, обрабатывающая список структур.
 *  Вид структуры:
 *  а) Название фильма
 *  б) Фамилия режисера
 *  в) Год выхода
 * 
 *  FILE_IN содержит в себе массив структур
 *  Программа 1)ищет фильм по названию KEY, вставляет перед ним фильм из FILE_FILM
 *  или 2)сортирует и удаляет дупликаты
 *  Результат в FILE_OUT
 * 
 *  1) ./app.exe FILE_IN FILE_OUT i KEY FILE_FILM
 *  2) ./app.exe FILE_IN FILE_OUT s
 */


#include <stdio.h>
#include "film.h"
#include "film_arr.h"
#include "task_funcs.h"
#include "list.h"
#include "node_list.h"
#include <string.h>

int main(int argc, char **argv)
{
    int rc;
    struct film_t *film_arr = NULL;
    node_t *list = NULL;
    
    size_t size = 0;
    FILE *f_in = NULL, *f_out = NULL;

    if ((argc == 4 || argc == 6) && (strcmp(argv[3], "i") == 0 ||
        strcmp(argv[3], "s") == 0))
    {
        f_in = fopen(argv[1], "r");
        f_out = fopen(argv[2], "w");
        if (f_in == NULL || f_out == NULL)
            rc = ERR_NO_FILE;
        else
            rc = fa_create(f_in, &film_arr, &size);
        if (!rc)
            rc = init_list_from_film_arr(&list, film_arr, size);
        if (rc)
            fa_free(film_arr, size);
        if (!rc)
        {
            if (argc == 4)
            {
                list = sort(list, film_cmp_by_title);
                remove_duplicates(&list, film_cmp_by_title);
                list_print(f_out, list, film_print);
            }
            else
            {
                FILE *f_ins = fopen(argv[5], "r");
                struct film_t insert_film;
                insert_film.name = NULL;
                insert_film.title = NULL;

                struct film_t key;
                key.title = argv[4];

                node_t *pos = NULL;
                node_t *el = NULL;

                if (f_ins == NULL)
                    rc = ERR_NO_FILE;

                if (!rc)
                    rc = film_read(f_ins, &insert_film);

                if (!feof(f_ins))
                    rc = ERR_IO;

                if (!rc)
                    pos = find(list, &key, film_cmp_by_title);
                if (!rc && pos)
                    el = node_create(&insert_film);
                else
                    rc = ERR_NOT_FOUND;
                if (!rc && el)
                {
                    insert(&list, el, pos);
                    list_print(f_out, list, film_print);
                }
                else
                    rc = ERR_MEM;
                
                film_free_content(&insert_film);
                fclose(f_ins);
            }
            list_free(list);
            fa_free(film_arr, size);
        }
    }
    else
        rc = ERR_ARGS;
    if (f_in != NULL)
        fclose(f_in);
    if (f_out != NULL)
        fclose(f_out);

    return rc;
}
