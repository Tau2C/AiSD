#include "TestQueue.h"
#include "../colors/ANSI-color-codes.h"
#include "TestDataTypes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _OK_ GRN " Ok " reset
#define _OK_n GRN " Ok\n" reset
#define _ERR_ RED "  FATAL ERROR: " reset

#define EXC_CATCH_ALL \
EXC_CATCH(queue_overflow) {                                    \
  queueTestFailed++;                                           \
  printf(_ERR_ "unexpected queue overflow exception\n");       \
}                                                              \
EXC_CATCH(queue_underflow) {                                   \
  queueTestFailed++;                                           \
  printf(_ERR_ "unexpected queue_underflow exception\n");      \
}                                                              \
EXC_CATCH(out_of_range) {                                      \
  queueTestFailed++;                                           \
  printf(_ERR_ "unexpected out_of_range exception\n");         \
}                                                              \
EXC_CATCH(queue_function_not_implemented) {                    \
  queueTestFailed++;                                           \
  printf(_ERR_ "queue enqueue or dequeue function not implemented\n");\
}

struct __attribute__((aligned(1))) queueForTestingUnderflowStruct {
  char underflowProtectionBuffer[1024];
  Queue queueForTestingUnderflow;
  char overflowProtectionBuffer[1024];
} queueWithProtection;

static int queueTestFailed = 0;

Queue * initializeQueueWithProtection() {
  Queue * queue;

  queue = & queueWithProtection.queueForTestingUnderflow;
  queueInitialize(queue);
  memset(queueWithProtection.underflowProtectionBuffer, 0, sizeof(char)*1024);
  memset(queueWithProtection.overflowProtectionBuffer, 0, sizeof(char)*1024);

  return queue;
}

/**
Tworzy kopię kolejki.
Wskaźniki do elementów są kopiowane. Nie są tworzone kopie elementów.
*/
Queue queueCopy(const Queue *queue) {
  Queue copyOfQueue;
  int i;

  queueInitialize(&copyOfQueue);
  copyOfQueue.head = queue->head;
  copyOfQueue.tail = queue->tail;
  if (copyOfQueue.head < QUEUE_FIRST_INDEX) {
    printf(_ERR_ "queue head < QUEUE_EMPTY_INDEX\n");
    exit(-1);
  }
  if (copyOfQueue.head >= QUEUE_CAPACITY) {
    printf(_ERR_ "queue head >= QUEUE_CAPACITY\n");
    exit(-1);
  }
  if (copyOfQueue.tail < QUEUE_FIRST_INDEX) {
    printf(_ERR_ "queue head < QUEUE_EMPTY_INDEX\n");
    exit(-1);
  }
  if (copyOfQueue.tail >= QUEUE_CAPACITY) {
    printf(_ERR_ "queue head >= QUEUE_CAPACITY\n");
    exit(-1);
  }
  for (i = 0; i < QUEUE_CAPACITY; i++) {
    copyOfQueue.buffer[i] = queue->buffer[i];
  }

  return copyOfQueue;
}

void printQueue(const Queue *queue) {
  Queue copyOfQueue;
  int i;

  copyOfQueue = queueCopy(queue);
  printf("--------- queue content ---------\n");
  if (copyOfQueue.head == copyOfQueue.tail) {
    printf("     empty\n");
  }
  i = 1;
  while (copyOfQueue.head != copyOfQueue.tail) {
    const Finger *element;

    printf("%d. Queue[H=%d, T=%d]: ", i++, copyOfQueue.head, copyOfQueue.tail);
    element = dequeue(&copyOfQueue);
    printFingerInfo(element);
  }
  printf("------------------\n");
}

void queueKiller() {
  Queue * queue;
  Finger *element;
  Finger fingers[5];


  queue = initializeQueueWithProtection();
  createFingers(fingers);

  EXC_TRY {
    printf("Testing dequeue on a non-queue object ... ");
    queue = (Queue *) & queueWithProtection.underflowProtectionBuffer[512];
    queue->tail++;
    element = dequeue(queue);
    printf(_ERR_ " array of NULLs accepted as a queue!\n");
    queueTestFailed++;
    // exit(-1);
  }
  EXC_CATCH(invalid_pointer) { 
    printf(_OK_ "invalid_pointer captured\n"); 
  }
  EXC_CATCH(queue_function_not_implemented) {
    queueTestFailed++;
    printf(_ERR_ "queue dequeue function not implemented\n");
  }
  EXC_END;
  EXC_TRY {
    printf("Testing enqueue on a non-queue object ... ");
    queue = (Queue *) & queueWithProtection.underflowProtectionBuffer[512];
    enqueue(queue, &fingers[0]);
    printf(_ERR_ " array of NULLs accepted as a queue!\n");
    queueTestFailed++;
    // exit(-1);
  }
  EXC_CATCH(invalid_pointer) { 
    printf(_OK_ "invalid_pointer captured\n"); 
  }
  EXC_CATCH(queue_function_not_implemented) {
    queueTestFailed++;
    printf(_ERR_ "queue dequeue function not implemented\n");
  }
  EXC_END;
}

void testQueueUnderflow() {
  Finger *element;
  Queue * queue;

  queue = initializeQueueWithProtection();

  EXC_TRY {
    printf("Testing queue underflow ... ");
    element = dequeue(queue);
    printf(_ERR_ "queue underflow not detected\n");
    queueTestFailed++;
  }
  EXC_CATCH(queue_underflow) { 
    printf(_OK_ "queue underflow captured\n"); 
  }
  EXC_CATCH(queue_function_not_implemented) {
    queueTestFailed++;
    printf(_ERR_ "queue dequeue function not implemented\n");
  }
  EXC_END;
  EXC_TRY {
    // test for trolling protection
    queue->head = QUEUE_LAST_ELEMENT_INDEX + 2;
    element = dequeue(queue);
    queueTestFailed++;
    printf(_ERR_ "DEQUEUE must throw an exception when queue.head > "
                 "QUEUE_LAST_ELEMENT_INDEX\n");
  }
  EXC_CATCH(queue_overflow) {
    printf(_OK_ "captured queue_overflow with head > QUEUE_LAST_ELEMENT_INDEX\n");
  }
  EXC_CATCH(out_of_range) {
    printf(_OK_ "captured out_of_range with head > QUEUE_LAST_ELEMENT_INDEX\n");
  }
  EXC_CATCH(queue_function_not_implemented) {
    queueTestFailed++;
    printf(_ERR_ "DEQUEUE function not implemented\n");
  }
  EXC_END;
  EXC_TRY {
      queue->head = QUEUE_FIRST_INDEX - 1;
    element = dequeue(queue);
    queueTestFailed++;
    printf(_ERR_ "DEQUEUE must throw an exception when queue.head < QUEUE_FIRST_INDEX\n");
  }
  EXC_CATCH(queue_underflow) {
    printf(_OK_ "captured queue_underflow with queue.head < QUEUE_FIRST_INDEX\n");
  }
  EXC_CATCH(out_of_range) {
    printf(_OK_ "captured out_of_range with queue.head < QUEUE_FIRST_INDEX\n");
  }
  EXC_CATCH(queue_function_not_implemented) {
    queueTestFailed++;
    printf(_ERR_ "DEQUEUE function not implemented\n");
  }
  EXC_END;
}

void testQueueOverflow() {
  Queue * queue;
  Finger fingers[5];
  int index;
  static int numberOFStoredElements;

  printf("Testing queue overflow ... ");
  queue = initializeQueueWithProtection();

  createFingers(fingers);

  EXC_TRY {
    numberOFStoredElements = 0;
    for (index = 0; index <= QUEUE_CAPACITY; index++) {
      enqueue(queue, &fingers[0]);
      numberOFStoredElements++;
    }
    queueTestFailed++;
    printf(_ERR_ "queue overflow not detected\n");
  }
  EXC_CATCH(queue_overflow) {
    if (QUEUE_CAPACITY == numberOFStoredElements) {
      printf(_OK_ "queue overflow captured\n");
    } else {
      char message[1024];

      snprintf(message, 1024,
               "queue overflow before the buffer is full. Number of stored "
               "elements = %d. Expected %d\n",
               numberOFStoredElements, QUEUE_CAPACITY);
      printf(_ERR_ "%s", message);
      queueTestFailed++;
    }
  }
  EXC_CATCH(queue_underflow) {
    queueTestFailed++;
    printf(_ERR_ "unexpected queue underflow captured\n");
  }
  EXC_CATCH(queue_function_not_implemented) {
    queueTestFailed++;
    printf(_ERR_ "queue enqueue function not implemented\n");
  }
  EXC_END;
  EXC_TRY {
    // test for trolling protection
    queue->tail = QUEUE_LAST_ELEMENT_INDEX + 2;
    enqueue(queue, &fingers[0]);
    queueTestFailed++;
    printf(_ERR_ "ENQUEUE must throw an exception when queue.tail > "
                 "QUEUE_LAST_ELEMENT_INDEX\n");
  }
  EXC_CATCH(queue_overflow) {
    printf(_OK_
           "captured queue_overflow with tail > QUEUE_LAST_ELEMENT_INDEX\n");
  }
  EXC_CATCH(out_of_range) {
    printf(_OK_ "captured out_of_range with tail > QUEUE_LAST_ELEMENT_INDEX\n");
  }
  EXC_CATCH(queue_function_not_implemented) {
    queueTestFailed++;
    printf(_ERR_ "ENQUEUE function not implemented\n");
  }
  EXC_END;
  EXC_TRY {
    queue->tail = QUEUE_FIRST_INDEX - 2;
    enqueue(queue, &fingers[0]);
    queueTestFailed++;
    printf(_ERR_ "ENQUEUE must throw an exception when queue.tail < QUEUE_FIRST_INDEX\n");
  }
  EXC_CATCH(queue_underflow) {
    printf(_OK_
           "captured queue_underflow with queue.tail < QUEUE_FIRST_INDEX\n");
  }
  EXC_CATCH(out_of_range) {
    printf(_OK_ "captured out_of_range with queue.tail < QUEUE_FIRST_INDEX\n");
  }
  EXC_CATCH(queue_function_not_implemented) {
    queueTestFailed++;
    printf(_ERR_ "DEQUEUE function not implemented\n");
  }
  EXC_END;
}

void testDequeue() {
  Queue * queue;
  Finger fingers[5];
  int i;

  printf("Testing dequeue on QUEUE_FIRST_INDEX ... ");
  queue = initializeQueueWithProtection();
  createFingers(fingers);

  EXC_TRY {
    Finger *f;

    queue->tail++;
    queue->buffer[0] = fingers[0];
    f = dequeue(queue);
    if (QUEUE_FIRST_INDEX + 1 != queue->head) {
      queueTestFailed++;
      printf(_ERR_ "queue.head must be QUEUE_FIRST_INDEX + 1 now!\n");
    } else {
      printf(_OK_);
    }
    if (QUEUE_FIRST_INDEX + 1 != queue->tail) {
      queueTestFailed++;
      printf(_ERR_ "queue.tail must be QUEUE_FIRST_INDEX + 1 now!\n");
    } else {
      printf(_OK_);
    }
    if (false == fingersEqual(f, &fingers[0])) {
      queueTestFailed++;
      printf(_ERR_ "'dequeue' did not return the expected element\n");
    } else {
      printf(_OK_n);
    }
  }
  EXC_CATCH_ALL
  EXC_END
}

void testDequeueWithTailOnEnd() {
  Queue * queue;
  Finger fingers[5];
  int i;

  printf("Testing dequeue on QUEUE_LAST_ELEMENT_INDEX  ... ");
  queue = initializeQueueWithProtection();
  createFingers(fingers);

  EXC_TRY {
    Finger *f;

    queue->head = QUEUE_LAST_ELEMENT_INDEX;
    queue->tail = QUEUE_FIRST_INDEX;
    queue->buffer[QUEUE_LAST_ELEMENT_INDEX] = fingers[0];
    f = dequeue(queue);
    if (QUEUE_FIRST_INDEX != queue->head) {
      queueTestFailed++;
      printf(_ERR_ "queue.head must be QUEUE_FIRST_INDEX now!\n");
    } else {
      printf(_OK_);
    }
    if (QUEUE_FIRST_INDEX != queue->tail) {
      queueTestFailed++;
      printf(_ERR_ "queue.tail must be QUEUE_FIRST_INDEX  now!\n");
    } else {
      printf(_OK_);
    }
    if (false == fingersEqual(f, &fingers[0])) {
      queueTestFailed++;
      printf(_ERR_ "'dequeue' did not return the expected element\n");
    } else {
      printf(_OK_n);
    }
  }
  EXC_CATCH_ALL
  EXC_END;
}

void testEnqueueWithHeadOnEnd() {
  Queue * queue;
  Finger fingers[5];
  int i;

  printf("Testing enqueue on QUEUE_LAST_ELEMENT_INDEX  ... ");
  queue = initializeQueueWithProtection();
  createFingers(fingers);

  EXC_TRY {
    Finger *f;

    queue->head = QUEUE_LAST_ELEMENT_INDEX;
    queue->tail = QUEUE_LAST_ELEMENT_INDEX;
    enqueue(queue, &fingers[0]);
    if (QUEUE_FIRST_INDEX != queue->tail) {
      queueTestFailed++;
      printf(_ERR_ "queue.tail must be QUEUE_FIRST_INDEX now!\n");
    } else {
      printf(_OK_);
    }
    if (QUEUE_LAST_ELEMENT_INDEX != queue->head) {
      queueTestFailed++;
      printf(_ERR_ "queue.head  must be QUEUE_LAST_ELEMENT_INDEX now!\n");
    } else {
      printf(_OK_);
    }
    if (false == fingersEqual(&queue->buffer[QUEUE_LAST_ELEMENT_INDEX], &fingers[0])) {
      queueTestFailed++;
      printf(_ERR_ "enqueue: buffer[QUEUE_LAST_ELEMENT_INDEX] has unexpected object\n");
    } else {
      printf(_OK_);
    }
  }
  EXC_CATCH_ALL
  EXC_END;
  printf(" test finished\n");
}

void testEnqueueWithDequeue() {
  Finger *f;
  Queue * queue;
  Finger fingers[5];

  printf("Testing enqueue == dequeue ... ");
  queue = initializeQueueWithProtection();
  createFingers(fingers);
  
  EXC_TRY {
    enqueue(queue, &fingers[0]);
    f = dequeue(queue);
    if (false == fingersEqual(f, &fingers[0])) {
      queueTestFailed++;
      printf(_ERR_ "dequeue did not return enqueued element\n");
    } else {
      printf(_OK_);
    }
    if (queue->head != QUEUE_FIRST_INDEX + 1) {
      queueTestFailed++;
      printf(_ERR_ "queue.head must be QUEUE_FIRST_INDEX + 1 now\n");
    } else {
      printf(_OK_);
    }
    if (queue->tail != QUEUE_FIRST_INDEX + 1) {
      queueTestFailed++;
      printf(_ERR_ "queue.head must be QUEUE_FIRST_INDEX+1 now\n");
    } else {
      printf(_OK_);
    }
    if (queue->tail != queue->head) {
      queueTestFailed++;
      printf(_ERR_ "queue.tail must be queue.head now\n");
    } else {
      printf(_OK_n);
    }
  }
  EXC_CATCH_ALL
  EXC_END;
}

void testQueue() {
  Queue * queue;
  Finger fingers[5];
  Finger *f, *f2;

  printf("=============================================\n");
  printf("                  Testing queue\n");
  printf("=============================================\n");
  queue = initializeQueueWithProtection();
  createFingers(fingers);
  printQueue(queue);

  testQueueUnderflow();
  testDequeue();
  testDequeueWithTailOnEnd();
  testEnqueueWithHeadOnEnd();
  testEnqueueWithDequeue();

  queue = initializeQueueWithProtection();
  // =============================================
  printf("Testing ENQ1, ENQ2 == DEQ1, DEQ2 ... ");
  EXC_TRY {
    enqueue(queue, &fingers[0]);
    enqueue(queue, &fingers[1]);
    f2 = dequeue(queue);
    f = dequeue(queue);
    if (false == fingersEqual(f2, &fingers[0])) {
      queueTestFailed++;
      printf(_ERR_ "dequeue did not return enqueuedd element 1\n");
      exit(-1);
    } else {
      printf(_OK_);
    }
    if (false == fingersEqual(f, &fingers[1])) {
      queueTestFailed++;
      printf(_ERR_ "dequeue did not return enqueuedd element 2\n");
      exit(-1);
    } else {
      printf(_OK_n);
    }
  }
  EXC_CATCH_ALL
  EXC_END;
  printf("Testing if queue is empty ... ");
  if (queue->head != queue->tail) {
    queueTestFailed++;
    printf(_ERR_ "queue must be empty now\n");
    exit(-1);
  } else {
    printf(_OK_n);
  }
  EXC_TRY {
    enqueue(queue, &fingers[0]);
    enqueue(queue, &fingers[1]);
    enqueue(queue, &fingers[2]);
    enqueue(queue, &fingers[3]);
    enqueue(queue, &fingers[4]);
    printQueue(queue);
  }
  EXC_CATCH_ALL
  EXC_END;
  testQueueOverflow();
  queueKiller();
  printf("=============================================\n");
  if(queueTestFailed) {
    printf(RED "          Test failed\n" reset);
  } else {
    printf(GRN "          Test succeed\n" reset);
  }
  printf("=============================================\n");
}
