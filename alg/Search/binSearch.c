// Бинарный поиск
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define MAX 1000

int getrand(int min, int max) {
	return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

int BinSearch(int *a, int x)
{	
	int l = 0, r = MAX;
	int mid;
	while (mid >= 0) {
		mid = l + ((r - l) / 2);
		if (a[mid] == x) {
			return mid;
		} else if (a[mid] > x) {
			r = mid - 1;
		} else if (a[mid] < x) {
			l = mid + 1;
		}
	}

	return -1;
}

int main()
{
	system("clear");	
	srand(time(NULL));

	int x;

	int *a = (int *)malloc(sizeof(int) * MAX);
	a[0] = rand() % MAX;
	for (int i = 1; i < MAX; i++) {
		a[i] = a[i - 1] + rand() % 10;
		printf("%d ", a[i]);
	}
	x = getrand(0, MAX);
	printf("\nINDEX : %d\nNUMB : %d\n", x, a[x]);

	printf("REZ INDEX: %d", BinSearch(a, a[x]));

	free(a);
	*a = 0;
	printf("\n");

	return 0;
}
