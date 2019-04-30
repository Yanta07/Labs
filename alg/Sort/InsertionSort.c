#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define N 100000

double wtime()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void InsertionSort(int A[], unsigned long int n) {
	int i;
	int j;
	int key;

	for (i = 1; i < n; i++) {
		key = A[i];
		j = i - 1;
		while (j >= 0 && A[j] > key) {
			A[j + 1] = A[j];
			j = j - 1;
		}
		A[j + 1] = key;
	}
}

int main() {
	unsigned long int n;
	double t;
	srand(time(NULL));
	unsigned long int i;
	int j;

	for(i = 1; i < 21; i++) {
		n = 50000 * i;

		int A[n];

		for(j = 0; j < n; ++j) {
			A[j] = rand() % N;
		}

 		t = wtime();
		InsertionSort(A, n);
		t = wtime() - t;

		printf("%7ld %5f\n", n, t);
	}

	return 0;
}