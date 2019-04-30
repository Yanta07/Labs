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

void swap(int * a, int * b) 
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

unsigned long int Partition(int A[], long int low, long int high) 
{
	int pivot = A[high];
	long int i = low;
	int j;

	for (j = low; j < high; j++) {
		if (A[j] < pivot) {
			swap(&A[i], &A[j]);
			i = i + 1;
		}
	}
	swap(&A[i], &A[high]);
	return i;
}

void QuickSort(int A[], int low, long int high) 
{
	long int p;
	if (low < high) {
		p = Partition(A, low, high);
		QuickSort(A, low, p - 1);
		QuickSort(A, p + 1, high);
	}
}

int main() 
{
	long int n;
	double t;
	srand(time(NULL));
	long int i;
	int j;
	int low = 0;

	for(i = 1; i < 21; i++) {
		n = 50000 * i;

		int A[n];

		for (j = 0; j < n; ++j) {
			A[j] = rand() % N;
		}

 		t = wtime();
		QuickSort(A, low, n - 1);
		t = wtime() - t;

		printf("%7ld %5f\n", n, t);
	}

	return 0;
}