#include "rec.h"
#include "iter.h"
#include <stdio.h>

char* itoa(int n, char* s);

int main()
{
	int arr[5] = {1, 1, 2, 3, 4};
	char str[20];
	printf("sum_arr_rec(arr, size) = %d\n", sum_arr_rec(arr, 5));
	printf("sum_arr(arr, size) = %d\n", sum_arr(arr, 5));
	printf("fib_rec(n) = %d\n", fib_rec(5));
	printf("fib(n) = %d\n", fib(5));
	itoa(100, str);
	printf("%s\n", str);

	return 0;
}

char* itoa(int n, char* s)
{
	int d = n % 10;
	int r = n / 10;
	if (n < 0) {
		*s++ = '-';
		d = -d;
		r = -r;
	}
	if (r) {
		s = itoa(r, s);
	}
	*s++ = "0123456789"[d];
	*s = '\0';
	return s;
}
