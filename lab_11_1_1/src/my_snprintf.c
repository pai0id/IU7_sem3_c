#include <stdarg.h>
#include <stdio.h>
#include "my_snprintf.h"

#define NULL_STR "(null)"
#define DIG_TO_CHAR(d) d + '0'

int my_snprintf(char *str, size_t size, const char *format, ...)
{
    if (format == NULL || (str == NULL && size != 0))
        return -1;

    va_list args;
    va_start(args, format);

    int size_left = size;
    size_t written = 0;
    char *current = str;
    int len;

    while (*format != 0)
    {
        if (*format == '%' && *(format + 1) == 's')
        {
            const char *arg_str = va_arg(args, const char*);
            int len = 0;
            if (arg_str == NULL)
                arg_str = NULL_STR;
            
            len = ncpy_str(current, arg_str, size_left <= 0 ? 0 : size_left);

            if (size_left > 0)
                current += len >= size_left - 1 ? size_left - 1 : len;
            
            size_left -= len;
            written += len;
            format += 2;
        }
        else if (*format == '%' && *(format + 1) == 'l' && *(format + 2) == 'l' && *(format + 3) == 'o')
        {
            unsigned long long arg_oll = va_arg(args, unsigned long long);

            len = snprint_to_octal(arg_oll, NULL, 0);
            char res_oct[len + 1];

            snprint_to_octal(arg_oll, res_oct, sizeof(res_oct));

            ncpy_str(current, res_oct, size_left <= 0 ? 0 : size_left);

            if (size_left > 0)
                current += len >= size_left - 1 ? size_left - 1 : len;

            size_left -= len;
            written += len;
            format += 4;
        }
        else
        {
            if (size_left > 1)
            {
                *current = *format;
                ++current;
            }
            --size_left;
            ++written;
            ++format;
        }
    }
    if (current)
        *current = 0;

    va_end(args);

    return written;
}

void insert_beg_fixed_size(char c, char *arr, size_t size)
{
    for (int i = size - 2; i >= 0; --i)
        arr[i + 1] = arr[i];

    if (size)
        arr[0] = c;
}

int snprint_to_octal(unsigned long long int num, char *res, size_t size)
{
    size_t len = 0;

    do
    {
        if (size)
            insert_beg_fixed_size(DIG_TO_CHAR(num % 8), res, len >= size - 1 ? size - 1 : len + 1);
        len++;
        num /= 8;
    } while (num > 0);
    if (size)
        res[len >= size - 1 ? size - 1 : len + 1] = 0;
    return len;
}

int ncpy_str(char *dest, const char *src, size_t size)
{
    size_t len = 0;
    while (*src != 0)
    {
        if (len + 1 < size)
            *dest++ = *src;
        len++;
        src++;
    }
    return len;
}
