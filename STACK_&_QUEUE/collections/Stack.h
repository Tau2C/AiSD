/** 
  Stos.
  Implementacja stosu z użyciem tablicy
*/
#ifndef STACK_1FDI_PRZ
#define STACK_1FDI_PRZ

#include "../dataTypes/DataTypes.h"
#include "../exception/excdefs.h"
#include "../exception/exception.h"

/**
początkowa wartość indeksu w tablicy buffer
*/
#define STACK_EMPTY_INDEX -1
/**
rozmiar bufora stosu
*/
#define STACK_CAPACITY 10
/**
maksymalna dozwolona wartość indeksu w tablicy buffer
*/
#define STACK_LAST_ELEMENT_INDEX (STACK_CAPACITY-1)


EXC_DECLARE(stack_function_not_implemented);
EXC_DECLARE(stack_overflow);
EXC_DECLARE(stack_underflow);

/**
Implementacja stosu za pomocą tablicy
*/
typedef struct SStackAsArray {
  /**
    indeks szczytu stosu w tablicy bufferEMPTY
  */
  int top;
  /**
    tablica przechowująca elementy stosu
  */
  Finger buffer[STACK_CAPACITY];
} Stack;

/**
  Initializes the given stack.
  @param stack a stack to initialize
*/
void stackInitialize(Stack * stack);
void push(Stack * stack, const Finger * finger);
Finger * pop(Stack * stack);
bool isStackEmpty(const Stack * stack);

#endif
