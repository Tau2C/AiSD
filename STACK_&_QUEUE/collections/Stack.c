#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

EXC_DEFINE(stack_function_not_implemented, EXC_NUM_USER_DEFINED + 1, "function not implemented");
EXC_DEFINE(stack_overflow, EXC_NUM_USER_DEFINED + 2, "stack overflow");
EXC_DEFINE(stack_underflow, EXC_NUM_USER_DEFINED + 3, "stack underflow");

void stackInitialize(Stack *stack)
{
	unsigned int i;
	if (NULL == stack)
	{
		printf("Stack::init stack is NULL");
		exit(-1);
	}
	stack->top = STACK_EMPTY_INDEX;
	for (i = 0; i < STACK_CAPACITY; i++)
	{
		stack->buffer[i].id = 0;
		stack->buffer[i].name[0] = '\x0';
	}
}

/**
  Funkcja PUSH, K.2.4 str. 37 w skrypcie
*/
void push(Stack *stack, const Finger *finger) EXC_THROWS(stack_overflow)
{
	if (stack == NULL || stack->buffer == NULL)
		EXC_THROW(invalid_pointer);
	if (stack->top >= STACK_LAST_ELEMENT_INDEX)
	{
		EXC_THROW(stack_overflow);
	}
	if (stack->top < STACK_EMPTY_INDEX)
	{
		EXC_THROW(stack_underflow);
	}

	stack->top += 1;
	stack->buffer[stack->top] = *finger;
}

/**
	Funkcja POP, K.2.5 str. 38 w skrypcie
*/
Finger *pop(Stack *stack) EXC_THROWS(stack_underflow | stack_overflow)
{
	if (stack == NULL || stack->buffer == NULL)
		EXC_THROW(invalid_pointer);
	if (isStackEmpty(stack) || stack->top < STACK_EMPTY_INDEX)
		EXC_THROW(stack_underflow);
	if (stack->top > STACK_LAST_ELEMENT_INDEX)
		EXC_THROW(stack_overflow);
	stack->top -= 1;
	return &stack->buffer[stack->top + 1];
}

/**
  Funkcja STOS-PUSTY, K.2.6 str. 38 w skrypcie
*/
bool isStackEmpty(const Stack *stack)
{
	if (STACK_EMPTY_INDEX == stack->top)
	{
		return true;
	}
	else
	{
		return false;
	}
}
