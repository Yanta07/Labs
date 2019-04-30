#include "heap.h"

struct heap *heap_create(int maxsize)
{
	struct heap *h;
	h = malloc(sizeof(*h));
	if (h != NULL) {
		h->maxsize = maxsize;
		h->nnodes = 0;
		h->nodes = malloc(sizeof(*h->nodes) * (maxsize)); /* Последний индекс - maxsize */
		if (h->nodes == NULL) {
			free(h);
			return NULL;
		}
	}
	return h;
}

void heap_free(struct heap *h)
{
	free(h->nodes);
	free(h);
}

void heap_swap(struct heapnode *a, struct heapnode *b)
{
	struct heapnode temp = *a;
	*a = *b;
	*b = temp;
}

struct heapnode *heap_min(struct heap *h)
{
	if (h->nnodes == 0) {
		return NULL;
	}
	return &h->nodes[0];
}

int heap_insert(struct heap *h, int key, int value)
{
	if (h->nnodes >= h->maxsize) {
		return -1;
	}
	h->nnodes++;
	h->nodes[h->nnodes - 1].key = key;
	h->nodes[h->nnodes - 1].value = value;
	/* HeapifyDown */
	for (int i = h->nnodes - 1; i > 0 && h->nodes[(i - 1) / 2].key > h->nodes[i].key; i = (i - 1) / 2) {
		heap_swap(&h->nodes[i], &h->nodes[(i - 1) / 2]);
	}
	return 0;
}

struct heapnode heap_extract_min(struct heap *h)
{
	if (h->nnodes <= 0) {
		return (struct heapnode){-1, -1};
	}
	if (h->nnodes == 1) {
		h->nnodes--;
		return h->nodes[0];
	}	
	struct heapnode minnode = h->nodes[0];
	h->nodes[0] = h->nodes[h->nnodes - 1];
	h->nnodes--;
	heap_heapify(h, 0);

	return minnode;
}

void heap_heapify(struct heap *h, int index)
{
	while (1) {
		int left = 2 * index + 1;
		int right = 2 * index + 2;
		int smallest = index;
		if (left < h->nnodes && h->nodes[left].key < h->nodes[smallest].key)
			smallest = left;
		if (right < h->nnodes && h->nodes[right].key < h->nodes[smallest].key)
			smallest = right;
		if (smallest == index)
			break;
		heap_swap(&h->nodes[index], &h->nodes[smallest]);
		index = smallest;
	}
}

int heap_decrease_key(struct heap *h, int index, int newkey)
{
	if (newkey >= h->nodes[index].key) {
		return -1;
	}
	h->nodes[index].key = newkey;
	while (index > 0 && h->nodes[(index - 1) / 2].key > h->nodes[index].key) {
		heap_swap(&h->nodes[index], &h->nodes[(index - 1) / 2]);
		index = (index - 1) / 2;
	}
	return index;
}
