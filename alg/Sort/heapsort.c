#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int getrand(int min, int max);
double wtime();
void swap(int *a, int *b);
void fill_arr(int *arr, int size);
void print_arr(int *arr, int size);
int check_rez(int *arr, int size);
void sift_down(int *arr, int top, int bottom);
double heap_sort(int *arr, int size);

int main()
{
	system("clear");
	srand(time(NULL));

	unsigned int size = 100;
	int *arr = (int *)malloc(sizeof(int) * size);
	fill_arr(arr, size);

    printf("TIME : %f\n", heap_sort(arr, size));
    check_rez(arr, size) == 1 ? printf("CHECK : TRUE\n") : printf("CHECK : FALSE\n");

    free(arr);
    arr = NULL;
	return 0;
}

double heap_sort(int *arr, int size) 
{   
    double t = wtime();
    for (int i = (size / 2) - 1; i >= 0; i--) {
        sift_down(arr, i, size - 1);
    }

    for (int i = size - 1; i >= 1; i--) {
        swap(&arr[0], &arr[i]);
        sift_down(arr, 0, i - 1);
    }

    return wtime() - t;
}

void sift_down(int *arr, int top, int bottom)
{
    int max_cld_index;
    int flag = 0; 

    while ((top * 2 <= bottom) && (!flag)) {
        if (top * 2 == bottom) {
            max_cld_index = top * 2;
        } else if (arr[top * 2] > arr[top * 2 + 1]) {
            max_cld_index = top * 2;
        } else {
            max_cld_index = top * 2 + 1;
        }
        if (arr[top] < arr[max_cld_index]) {
            swap(&arr[top], &arr[max_cld_index]);
            top = max_cld_index;
        } else {
            flag = 1;
        }
    }
}

int getrand(int min, int max) {
	return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

double wtime() {
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void fill_arr(int *arr, int size)
{
	for (int i = 0; i < size; i++) {
		*(arr + i) = getrand(0, 100);
	}
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