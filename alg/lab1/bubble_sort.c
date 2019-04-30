#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int getrand(int min, int max);
double wtime();
void fill_arr(int *arr, int size);
void swap(int *a, int *b);
double bubble_sort(int *array, int size);
void print_arr(int *arr, int size);
int check_rez(int *arr, int size);

int main()
{
	system("clear");
	srand(time(NULL));

	unsigned int size = 250000;
	int *arr = (int *)malloc(sizeof(int) * size);
	fill_arr(arr, size);
	
	printf("\nBUBBLE SORT TIME : %f sec\n", bubble_sort(arr, size));
	check_rez(arr, size) == 1 ? printf("CHECK : TRUE\n") : printf("CHECK : FALSE\n");

	free(arr);
	arr = NULL;

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

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

double bubble_sort(int *array, int size)
{
    double t = wtime();
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
            }
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