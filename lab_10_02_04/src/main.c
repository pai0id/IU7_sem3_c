#define _GNU_SOURCE

#include "list.h"
#include "node_list.h"
#include "err.h"
#include "operations.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OUT "out"
#define MUL "mul"
#define SQR "sqr"
#define DIV "div"

int main(void)
{
    int rc = OK;
    char *buf = NULL;
    size_t len = 0;
    ssize_t read;
    int tmp_num;
    node_t *num1, *num2, *res;

    if ((read = getline(&buf, &len, stdin)) == -1)
        rc = ERR_IO;
    if (read > 1)
        buf[read - 1] = 0;
    else
        rc = ERR_IO;
    if (!rc)
    {
        if (strcmp(buf, OUT) == 0)
        {
            if (scanf("%d", &tmp_num) != 1)
                rc = ERR_IO;
            if (!rc)
                rc = init_list_from_num(&num1, tmp_num);
            if (!rc)
            {
                print_num(stdout, num1);
                list_free(num1);
            }
        }
        else if (strcmp(buf, MUL) == 0)
        {
            if (scanf("%d", &tmp_num) != 1)
                rc = ERR_IO;
            if (!rc)
                rc = init_list_from_num(&num1, tmp_num);
            if (!rc)
            {
                if (scanf("%d", &tmp_num) != 1)
                    rc = ERR_IO;
                if (!rc)
                    rc = init_list_from_num(&num2, tmp_num);
                if (!rc)
                {
                    res = mul_nums(num1, num2);
                    if (res)
                    {
                        print_num(stdout, res);
                        list_free(res);
                    }
                    else
                        rc = ERR_MEM;
                    list_free(num2);
                }
                list_free(num1);
            }
        }
        else if (strcmp(buf, SQR) == 0)
        {
            if (scanf("%d", &tmp_num) != 1)
                rc = ERR_IO;
            if (!rc)
                rc = init_list_from_num(&num1, tmp_num);
            if (!rc)
            {
                res = sqr_num(num1);
                if (res)
                {
                    print_num(stdout, res);
                    list_free(res);
                }
                else
                    rc = ERR_MEM;
                list_free(num1);
            }
        }
        else if (strcmp(buf, DIV) == 0)
        {
            if (scanf("%d", &tmp_num) != 1)
                rc = ERR_IO;
            if (!rc)
                rc = init_list_from_num(&num1, tmp_num);
            if (!rc)
            {
                if (scanf("%d", &tmp_num) != 1)
                    rc = ERR_IO;
                if (!rc)
                    rc = init_list_from_num(&num2, tmp_num);
                if (!rc)
                {
                    res = div_nums(num1, num2);
                    if (res)
                    {
                        print_num(stdout, res);
                        list_free(res);
                    }
                    else
                        rc = ERR_MEM;
                    list_free(num2);
                }
                list_free(num1);
            }
        }
        else
            rc = ERR_ARGS;
    }
    free(buf);
    return rc;
}
