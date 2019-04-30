// Bogosort Болотная сортировка
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int getrand(int min, int max);
void swap(int *a, int *b);
int check_rez(int *arr, int size);
void print_arr(int *arr, int size);
double wtime();
double bogoSort(int *arr, int size);
void shuffle(int *arr, int size);

int main() {
  system("clear");
  srand(time(NULL));
  unsigned int size = 10;
  int *arr = (int *)malloc(sizeof(int) * size);

  for (int i = 0; i < size; i++) {
    *(arr + i) = getrand(0, 33);
  }
  print_arr(arr, size);
  printf("TIME : %fs\n", bogoSort(arr, size));

  free(arr);
  *arr = 0;

  return 0;
}

double bogoSort(int *arr, int size) {
  double t = wtime();
  while (check_rez(arr, size)) {
    shuffle(arr, size);
    print_arr(arr, size);
  }
  return wtime() - t;
}

int getrand(int min, int max) {
  return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

void shuffle(int *arr, int size)
{
  for (int i = 0; i < size - 1; i++) {
    swap(&arr[i], &arr[rand() % size]);
  }
}

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int check_rez(int *arr, int size) {
  for (int i = 0; i < size - 1; i++) {
    if (arr[i] > arr[i + 1]) {
      return 1;
    }
  }
  return 0;
}

void print_arr(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

double wtime() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}