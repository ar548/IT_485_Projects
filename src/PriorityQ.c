#include "simple_logger.h"
#include "PriorityQ.h"
#include <stdlib.h>


int pq_isEmpty(PriorityQueue *pq) {
	if (pq->head == NULL)
		return 1;
	if (pq->tail == NULL)
		return 1;
	return 0;
}

PriorityQueue * new_pq(size_t elementSize)
{
	PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
	pq->head = NULL;
	pq->tail = NULL;
	pq->nodeSize = elementSize;
	return pq;
}

pq_node_t * pq_node_new(void* data, int priority) {
	pq_node_t *pq_node = (pq_node_t*)malloc(sizeof(pq_node_t));
	pq_node->data = data;
	pq_node->priority = priority;
	pq_node->next = NULL;
	pq_node->prev = NULL;
}

void pq_free(PriorityQueue *pq)
{

}

void *pq_delete_max(PriorityQueue *pq)
{
	if (pq == NULL)return NULL;
	if (pq_isEmpty(pq)) {
		slog("Error: attpemting to dequeue from an empty queue.");
		return NULL;
	}

	void* r = pq->tail->data;

	// if there is only one node
	if (pq->tail->prev == NULL) {
		pq->tail = NULL;
		pq->head = NULL;
	}
	else {
		pq_node_t *temp = pq->tail;
		pq->tail = pq->tail->prev;
		pq->tail->next = NULL;
		free(temp);
	}

	return r;
}

void *pq_delete_min(PriorityQueue *pq)
{
	if (pq == NULL)return NULL;
	if (pq_isEmpty(pq)) {
		slog("Error: attpemting to dequeue from an empty queue.");
		return NULL;
	}

	void* r = pq->head->data;

	// if there is only one node
	if (pq->head->prev == NULL) {
		pq->tail = NULL;
		pq->head = NULL;
	}
	else {
		pq_node_t *temp = pq->head;
		pq->head = pq->head->next;
		pq->head->prev = NULL;
		free(temp);
	}

	return r;
}

void pq_insert(PriorityQueue *pq, void *data, int priority)
{
	if (pq == NULL)return;
	if (data == NULL)return;

	pq_node_t *temp = pq_node_new(data, priority);

	// check priority is greater than tail->priority (the nes node will be new tail)
	if (priority >= pq->tail->priority) {
		// TODO: move this check up to the start of the function to save on time
		pq->tail->next = temp;
		temp->prev = pq->tail;
		pq->tail = temp;
		return;
	}

	// check if the queue is empty
	if (pq_isEmpty(pq)) {
		pq->head = temp;
		pq->tail = temp;
		return;
	}

	// find the first node that is greater than the node to be inserted.
	pq_node_t *curr = pq->head;
	while (curr != NULL) {
		if (curr->priority >= temp->priority) {
			break;
		}
		curr = curr->next;
	}

	// this should also work even if the node is the head
	temp->prev = curr->prev;
	temp->next = curr;
	temp->next->prev = temp;
	// if the new node is the new head
	if (temp->prev != NULL) {
		temp->prev->next = temp;
	}
}