#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Item {
	double key;
	int value;
} item;

typedef struct Queue {
	int front, rear, size;
	unsigned capacity;
	item *data;
}QQ;


void createQueue(QQ *queue, unsigned capacity);
bool isFull(QQ *queue);
bool isEmpty(QQ *queue);
bool enqueue(QQ *queue, item value);
void dequeue(QQ *queue);
item front(QQ* queue);
item rear(QQ* queue);
int Qsize(QQ *queue);
int queueCapacity(QQ *queue);
void QDestroy(QQ *queue);
void printQQ(QQ *queue);

#endif
