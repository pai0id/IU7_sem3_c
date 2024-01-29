#include "libarr.h"
#include <stdbool.h>
#include <math.h>

/**
 * \brief Проверяет, является ли число простым.
 *
 * Проверяет, является ли указанное число простым. Число считается простым, если оно больше 1
 * и не имеет делителей, кроме 1 и самого себя.
 *
 * \param n [in] Проверяемое число.
 * \return true, если число простое; false в противном случае.
 */
static bool is_prime(int n)
{
    if (n <= 1) return 0;
    for (size_t i = 2; i <= sqrt(n); ++i)
        if (n % i == 0)
            return false;
    return true;
}

void fill_primes(int *arr, size_t size)
{
    size_t cnt = 0;
    for (size_t i = 2; cnt < size; ++i)
        if (is_prime(i))
            arr[cnt++] = i;
}

int ncpy_and_add(int *src, size_t src_size, int *dst, size_t dst_available_size, size_t *dst_size, int num)
{
    size_t dst_ind = 0;
    if (dst == NULL && dst_available_size != 0)
        return LIB_ERR_ARGS;
    for (size_t i = 0; i < src_size; ++i)
    {
        if (dst_available_size != 0)
        {
            if (dst_ind >= dst_available_size)
                return LIB_ERR_MEM_SIZE;
            dst[dst_ind] = src[i];
        }
        dst_ind++;
        if (src[i] % 2 == 0)
        {
            if (dst_available_size != 0)
            {
                if (dst_ind >= dst_available_size)
                    return LIB_ERR_MEM_SIZE;
                dst[dst_ind] = num;
            }
            dst_ind++;
        }
    }
    *dst_size = dst_ind;
    return LIB_OK;
}
