#include "iter.h"
#include <stdio.h>

int sum_arr_iter(int* arr, int size, int sum)
{
    if (size == 0) {
        return sum;
    }

    return sum_arr_iter(arr, size - 1, arr[size - 1] + sum);
}

int sum_arr(int* arr, int size)
{
    return sum_arr_iter(arr, size, 0);
}


int fib_iter(int cur, int prev, int count, int n)
{
    if (n == count) {
        return cur;
    }

    return fib_iter(cur + prev, cur, count + 1, n);
}

int fib(int n)
{
    return fib_iter(0, 1, 0, n);
}
