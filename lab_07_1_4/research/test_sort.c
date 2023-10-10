#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include "mysort.h"

#ifndef n
#error no n [use -Dn=<value>]
#endif

#define MAX_NUM_TESTS 800 // Количество тестов

double calc_mean(const long long data[], size_t length);

double calc_stdev(const long long data[], size_t length, double avr);

double calc_rse(size_t length, double avr, double stdev);

void input_sorted(int arr[], size_t a_size);

void input_rand(int arr[], size_t a_size);

void run_tests(void (*p_sort)(void *, size_t, size_t, int (*)(const void *, const void *)), void (*input)(int *, size_t), FILE *f_table, FILE *f_graph)
{
    size_t i;
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    int arr[n];
    struct timespec start, end;

    for (i = 0; i < MAX_NUM_TESTS; i++)
    {
        input(arr, n);

        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        p_sort(arr, n, sizeof(int), int_cmp);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        test_arr[i] = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;

        if (i % 10 == 9)
        {
            avr = calc_mean(test_arr, i + 1);
            if (calc_rse(i + 1, avr, calc_stdev(test_arr, i + 1, avr)) <= 5)
            {
                i++;
                break;
            }
        }
    }

    avr = calc_mean(test_arr, i);
    fprintf(f_table, "%u | %.2lf | %lu | %.2lf\n", n, avr, i, calc_rse(i, avr, calc_stdev(test_arr, i, avr)));
    fprintf(f_graph, "%u %.2lf\n", n, avr);
}

int main(void)
{
    FILE *f_table, *f_graph;
    f_table = fopen("../tables/my_sorted.txt", "a+");
    f_graph = fopen("../graphs/my_sorted.txt", "a+");
    run_tests(mysort, input_sorted, f_table, f_graph);

    f_table = fopen("../tables/my_rand.txt", "a+");
    f_graph = fopen("../graphs/my_rand.txt", "a+");
    run_tests(mysort, input_rand, f_table, f_graph);

    f_table = fopen("../tables/q_sorted.txt", "a+");
    f_graph = fopen("../graphs/q_sorted.txt", "a+");
    run_tests(qsort, input_sorted, f_table, f_graph);

    f_table = fopen("../tables/q_rand.txt", "a+");
    f_graph = fopen("../graphs/q_rand.txt", "a+");
    run_tests(qsort, input_rand, f_table, f_graph);

    fclose(f_table);
    fclose(f_graph);
    return 0;
}

// Функция для вычисления среднего значения
double calc_mean(const long long data[], size_t length)
{
    long long sum = 0;
    for (size_t i = 0; i < length; i++)
        sum += data[i];
    return (double)sum / (double)length;
}

// Функция для вычисления стандартного отклонения
double calc_stdev(const long long data[], size_t length, double avr)
{
    double sum = 0;
    for (size_t i = 0; i < length; i++)
    {
        double diff = data[i] - avr;
        sum += diff * diff;
    }
    return sqrt((double)sum / ((double)length - 1));
}

// Функция для вычисления относительной стандартной ошибки (RSE)
double calc_rse(size_t length, double avr, double stdev)
{
    return stdev / sqrt((double)length) / avr * 100;
}

/// Ввод упорядоченного массива
void input_sorted(int arr[], size_t a_size)
{
    for (size_t i = 0; i < a_size; ++i)
        arr[i] = i + 1;
}

void input_rand(int arr[], size_t a_size)
{
    for (size_t i = 0; i < a_size; ++i)
        arr[i] = rand();
}
