#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "../exception/excdefs.h"
#include "../exception/exception.h"

EXC_DEFINE(queue_function_not_implemented, EXC_NUM_USER_DEFINED + 10, "function not implemented");
EXC_DEFINE(queue_overflow, EXC_NUM_USER_DEFINED + 11, "queue overflow");
EXC_DEFINE(queue_underflow, EXC_NUM_USER_DEFINED + 12, "queue underflow");

void queueInitialize(Queue *queue)
{
	unsigned int i, n;

	if (NULL == queue)
	{
		printf("Queue::init queue is NULL");
		exit(-1);
	}
	queue->head = QUEUE_FIRST_INDEX;
	queue->tail = QUEUE_FIRST_INDEX;
	n = sizeof(queue->buffer) / sizeof(queue->buffer[0]);
	for (i = 0; i < n; i++)
	{
		queue->buffer[i].id = 0;
		queue->buffer[i].name[0] = '\x0';
	}
}

void enqueue(Queue *queue, const Finger *finger)
{
	if (queue == NULL || finger == NULL)
		EXC_THROW(invalid_pointer);
	if (queue->tail > QUEUE_LAST_ELEMENT_INDEX || queue->tail < QUEUE_FIRST_INDEX)
		EXC_THROW(out_of_range);
	queue->buffer[queue->tail] = *finger;
	if (queue->tail >= QUEUE_LAST_ELEMENT_INDEX)
		queue->tail = QUEUE_FIRST_INDEX;
	else
		queue->tail++;
}

Finger *dequeue(Queue *queue)
{
	Finger *element;

	if (NULL == queue)
		EXC_THROW(invalid_pointer);
	if (queue->head > QUEUE_LAST_ELEMENT_INDEX)
		EXC_THROW(out_of_range);
	if (queue->head < QUEUE_FIRST_INDEX)
		EXC_THROW(out_of_range);
	if (queue->head == queue->tail)
	{
		EXC_THROW(queue_underflow);
	}

	element = &queue->buffer[queue->head];
	queue->head++;
	if (queue->head > QUEUE_LAST_ELEMENT_INDEX)
		queue->head = QUEUE_FIRST_INDEX;

	return element;
}
