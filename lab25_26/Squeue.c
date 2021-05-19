#include "Squeue.h"

void createQueue(QQ *queue, unsigned capacity) {
	queue->capacity = capacity;
	queue->front = queue->size = 0;
	queue->rear = capacity - 1;
	queue->data = malloc(queue->capacity * sizeof(item));
}

bool isFull(QQ *queue) {
	return (queue->size == queue->capacity);
}

bool isEmpty(QQ *queue) {
	return (queue->size == 0);
}

bool enqueue(QQ *queue, item value) {
	if (isFull(queue)){
		printf("Impossible to enqueue\nThe queue if full\n" );
		return false;
	}

	queue->data[(queue->front + queue->size) % queue->capacity] = value;
	queue->size++;

	return true;
}

void dequeue(QQ *queue) {
	if (isEmpty(queue)) {
		printf("The queue is empty\n" );
		return;
	}

	queue->front = (queue->front + 1) % queue->capacity;
	queue->size --;
}

item front(QQ* queue) {
	return queue->data[queue->front];
}

item rear(QQ* queue) {
	return queue->data[queue->rear];
}

int Qsize(QQ *queue) {
	return queue->size;
}

int queueCapacity(QQ *queue) {
	return queue->capacity;
}

void QDestroy(QQ *queue) {
	if (queue->data == NULL) return;

	free(queue->data);

	queue->data = NULL;
}

void printQQ(QQ *queue) {
	item tmp;
	int j = 0;
	for (int i = 0; i < Qsize(queue); i++) {
		tmp = queue->data[(queue->front + i) % queue->capacity];
		printf("%d      %.3lf      %5d\n", j++, tmp.key, tmp.value);
	}
}
