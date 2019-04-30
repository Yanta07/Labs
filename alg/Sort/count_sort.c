#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int getrand(int min, int max);
double wtime();
void fill_arr(int *arr, int size);
double count_sort(int *arr, int *rez, int size);
void print_arr(int *arr, int size);
int check_rez(int *arr, int size);

int main()
{
	system("clear");
	srand(time(NULL));

	unsigned int size = 1000000;
	int *arr = (int *)malloc(sizeof(int) * size);
	int *rez = (int *)malloc(sizeof(int) * size);

	fill_arr(arr, size);

	printf("\nCOUNTING SORT TIME : %f sec\n", count_sort(arr, rez, size));
	check_rez(rez, size) == 1 ? printf("CHECK : TRUE\n") : printf("CHECK : FALSE\n");
	
	free(arr);
	arr = NULL;
	free(rez);
	rez = NULL;

	return 0;
}

int getrand(int min, int max) {
	return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

double wtime() {
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void fill_arr(int *arr, int size)
{
	for (int i = 0; i < size; i++) {
		*(arr + i) = getrand(0, 100);
	}
}

double count_sort(int *arr, int *rez, int size)
{	
	double t = wtime();
	int max = arr[0];
	for (int i = 1; i < size; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}

	int *counter = (int *)calloc(max + 1, sizeof(int));

	for (int i = 0; i < size; i++) {
		counter[*(arr + i)] += 1;
	}	
	int j = 0;
	for (int x = 0; x < max + 1; x++) {
		for (int i = 0; i < counter[x]; i++) {
			rez[j] = x;
			j++;
		}
	}	

	return wtime() - t;
}

void print_arr(int *arr, int size)
{
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
}

int check_rez(int *arr, int size)
{	
	for (int i = 0; i < size - 1; i++) {
		if (arr[i] > arr[i + 1]) {
			return 0;
		}
	}
	return 1;
}