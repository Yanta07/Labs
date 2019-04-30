#include "rec.h"
#include <stdio.h>

int sum_arr_rec(int* arr, int size)
{
	if (size == 0) {
		return 0;
	}

	return arr[size - 1] + sum_arr_rec(arr, size - 1);
}

int fib_rec(int n)
{
	if (n == 0) {
		return 0;
	}
	if (n == 1) {
		return 1;
	}

	return fib_rec(n - 1) + fib_rec(n - 2);
}