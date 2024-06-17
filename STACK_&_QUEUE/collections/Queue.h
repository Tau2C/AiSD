/** 
  Kolejka.
  Implementacja kolejki z użyciem tablicy
*/
#ifndef QUEUE_1FDI_PRZ
#define QUEUE_1FDI_PRZ

#include "../dataTypes/DataTypes.h"
#include "../exception/excdefs.h"
#include "../exception/exception.h"

/**
początkowa wartość indeksu w tablicy buffer
*/
#define QUEUE_FIRST_INDEX 0
/**
rozmiar bufora kolejki
*/
#define QUEUE_CAPACITY 10
/**
maksymalna dozwolona wartość indeksu w tablicy buffer
*/
#define QUEUE_LAST_ELEMENT_INDEX (QUEUE_CAPACITY-1)

/**
wyjątek: funkcja nie zaprogramowana
*/
EXC_DECLARE(queue_function_not_implemented);
/**
wyjątek: bufor kolejki się przepełnił
*/
EXC_DECLARE(queue_overflow);
/**
wyjątek: kolejka jest pusta (nie da się pobrać elementu)
*/
EXC_DECLARE(queue_underflow);
/**
Implementacja kolejki za pomocą tablicy
*/
typedef struct SQueueAsArray {
  /**
    indeks początku kolejki w tablicy buffer
  */
  int head;
  /**
    indeks końca kolejki w tablicy buffer
  */
  int tail;
  /**
    tablica przechowująca elementy kolejki
  */
  Finger buffer[10];
} Queue;

/**
  Initializes the given queue.
  @param queue a queue to initialize
*/
void queueInitialize(Queue * queue);
/**
  Funkcja ENQUEUE, K.2.7 str. 39 w skrypcie
*/
void enqueue(Queue * queue, const Finger * finger);
/**
  Funkcja DEQUEUE, K.2.8 str. 39 w skrypcie
*/
Finger * dequeue(Queue * queue);

#endif
