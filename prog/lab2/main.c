#include <stdio.h>
#include <stdlib.h>
#include "IntVector.h"

int main()
{	
	IntVector *v;

	v = int_vector_new(20);
	
	for (int i = 0; i < 15; i++) {
		v->data[i] = i;
		v->size++;
	}	

	//for (int i = 0; i < 15; i++) {
	//	printf("%d ", v->data[i]);
	//}
	//printf("\n");

	//v = int_vector_copy(v);
	//printf("Copy Size : %ld\nCopy Capacity : %ld\n", v->size, v->capacity);
	//printf("int_vector_get_item : %d\n", int_vector_get_item(v, 14));
	//int_vector_set_item(v, 113, 15);
	printf("int_vector_get_item : %d\n", int_vector_get_item(v, 0));


	//int_vector_push_back(v, 15);

	//int_vector_shrink_to_fit(v);

	//int_vector_resize(v, 20);
	//int_vector_pop_back(v);
	//for (int i = 0; i < v->size; i++) {
	//	printf("%d ", v->data[i]);
	//}
	//printf("\n");
	//printf("New size : %ld\n", v->size);
	//int_vector_free(&v);
	//printf("v : %p\n", v);

	return 0;
}
