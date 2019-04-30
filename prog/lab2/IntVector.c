#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "IntVector.h"

IntVector *int_vector_new(size_t capacity)
{
	if (capacity < 0) {
		printf("Емкость не может быть меньше 0\n");
		return NULL;
	}
	IntVector *v = (IntVector *)malloc(sizeof *v);
	if (!v) {
		printf("Не могу выделить память для IntVector\n");
		return NULL;
	}

	v->capacity = capacity;
	v->size = 0;

	v->data = (int *)malloc(sizeof(int) * v->size);
	if (!v->data) {
		printf("Не могу выделить память для v->data\n");
		return NULL;
	}

	return v;
}

IntVector *int_vector_copy(const IntVector *v)
{
	IntVector *c = int_vector_new(v->capacity);
	c->size = v->size;
	for (int i = 0; i < c->size; i++) {
		c->data[i] = v->data[i];
	}
	return c;
}

void int_vector_free(IntVector **v)
{
	free((*v)->data);
	(*v)->data = NULL;
	free(*v);
	*v = NULL;
}

int int_vector_get_item(const IntVector *v, size_t index)
{
	if (index >= v->size || index < v->size) {
		printf("Значение index >=< v->size\n");
		return -1;
	}
	return v->data[index];
}

void int_vector_set_item(IntVector *v, size_t index, int item)
{
	if (index >= v->capacity) {
		printf("Значение index больше максимального индекса массива\n");
		return;
	}
	v->data[index] = item;
}

size_t int_vector_get_size(const IntVector *v)
{
	return v->size;
}

size_t int_vector_get_capacity(const IntVector *v)
{
	return v->capacity;
}

int int_vector_push_back(IntVector *v, int item)
{
	size_t temp_cap = v->capacity;
	if (v->size == temp_cap) {
		if (temp_cap == 0) {
			temp_cap += 2;
		} else {
			temp_cap *= 2;
		}
		v = realloc(v, temp_cap);
		if (!v) {
			printf("Не могу выделить больше памяти\n");
			return -1;
		}
	}
	v->capacity = temp_cap;
	v->data[v->size] = item;
	v->size++;

	return 0;
}

void int_vector_pop_back(IntVector *v)
{
	if (!v->size) {
		return;
	}
	v->size--;
}

int int_vector_shrink_to_fit(IntVector *v)
{	
	v->capacity = v->size;
	v = realloc(v, v->capacity);
	if (!v) {
		return -1;
	}
	return 0;
}

int int_vector_resize(IntVector *v, size_t new_size)
{
	if (new_size < 0) {
		printf("Размер не может быть < 0");
		return -1;
	}
	if (new_size < v->size) {
		return -1;
	} else if (new_size == v->size) {
		printf("Размер равен текущему. Перевыделение памяти не требуется\n");
		return -1;
	} else if (new_size > v->capacity) {
		if (int_vector_reserve(v, new_size) == -1) {
			return -1;
		}
	}
	IntVector *c = int_vector_copy(v);
	v->size = new_size;
	v->data = (int *)calloc(v->size, sizeof(int));
	for (int i = 0; i < c->size; i++) {
		v->data = c->data;
	}
	if (!v->data) {
		printf("Не могу выделить память для v->data");
		return -1;
	}

	return 0;
}

int int_vector_reserve(IntVector *v, size_t new_capacity)
{
	if (new_capacity <= v->capacity) {
		return -1;
	} 
	v = realloc(v, new_capacity);
	if (!v) {
		printf("Не могу изменить емкость массива\n");
		return -1;
	}
	v->capacity = new_capacity;
	return 0;
}