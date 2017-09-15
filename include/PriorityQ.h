#ifndef __PQ__
#define __PQ__
#include <stdlib.h>

typedef struct pq_node pq_node_t;

struct pq_node
{
	pq_node_t *next;
	pq_node_t *prev;
	void* data;
	int priority;
};

typedef struct {
	pq_node_t *head;
	pq_node_t *tail;
	size_t nodeSize;
}PriorityQueue;

PriorityQueue *pq_new(size_t elementSize);
void pq_free(PriorityQueue *pq);
void *pq_delete_max(PriorityQueue *pq);
void *pq_delete_min(PriorityQueue *pq);
void pq_insert(PriorityQueue *pq, void*data, int priority);

#endif