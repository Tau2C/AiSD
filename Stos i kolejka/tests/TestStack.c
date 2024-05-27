#include "TestStack.h"
#include "../colors/ANSI-color-codes.h"
#include "TestDataTypes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _OK_ GRN "  Ok " reset
#define _OK_n GRN " Ok\n" reset
#define _ERR_ RED "  FATAL ERROR: " reset

struct StackStruct {
  char stackUnderflowProtectionBuffer[1024];
  Stack stack;
  char stackOverflowProtectionBuffer[1024];
} stackWithProtection;

static int stackTestFailed = 0;

/**
Tworzy kopię stosu.
Wskaźniki do elementów są kopiowane. Nie są tworzone kopie elementów.
*/
Stack stackCopy(const Stack *stack) {
  Stack copyOfStack;
  int i;

  stackInitialize(& copyOfStack);
  copyOfStack.top = stack->top;
  for (i = 0; i < STACK_CAPACITY; i++) {
    copyOfStack.buffer[i] = stack->buffer[i];
  }

  return copyOfStack;
}

void printStack(const Stack *stack) {
  Stack copyOfStack;

  copyOfStack = stackCopy(stack);
  printf("--------- stack content ---------\n");
  if (-1 == copyOfStack.top) {
    printf("     empty\n");
  }
  while (copyOfStack.top >= 0) {
    const Finger *element;

    printf("Stack[%d]: ", copyOfStack.top);
    element = pop(&copyOfStack);
    printFingerInfo(element);
  }
  printf("------------------\n");
}

void stackKiller() {
  Stack * stack;
  Finger *element;
  Finger fingers[5];
  
  stack = & stackWithProtection.stack;
  stackInitialize(stack);
  memset(stackWithProtection.stackOverflowProtectionBuffer, 0, sizeof(char)*1024);
  memset(stackWithProtection.stackUnderflowProtectionBuffer, 0, sizeof(char)*1024);
  createFingers(fingers);
  
  EXC_TRY {
    printf("Testing pop on a non-stack object ... ");
    stack = (Stack *) & stackWithProtection.stackUnderflowProtectionBuffer[512];
    element = pop(stack);
    printf(_ERR_ " array of NULLs accepted as a stack!\n");
    stackTestFailed++;
    // exit(-1);
  }
  EXC_CATCH(invalid_pointer) { 
    printf(_OK_ "invalid_pointer captured\n"); 
  }
  EXC_CATCH(stack_function_not_implemented) {
    stackTestFailed++;
    printf(_ERR_ "stack pop function not implemented\n");
  }
  EXC_END;
  EXC_TRY {
    printf("Testing push on a non-stack object ... ");
    stack = (Stack *) & stackWithProtection.stackUnderflowProtectionBuffer[512];
    push(stack, & fingers[0]);
    printf(_ERR_ " array of NULLs accepted as a stack!\n");
    stackTestFailed++;
    // exit(-1);
  }
  EXC_CATCH(invalid_pointer) { 
    printf(_OK_ "invalid_pointer captured\n"); 
  }
  EXC_CATCH(stack_function_not_implemented) {
    stackTestFailed++;
    printf(_ERR_ "stack push function not implemented\n");
  }
  EXC_END;
}

void testStackUnderflow() {
  Stack * stack;
  Finger *element;

  stack = & stackWithProtection.stack;
  stackInitialize(stack);
  memset(stackWithProtection.stackOverflowProtectionBuffer, 0, sizeof(char)*1024);
  memset(stackWithProtection.stackUnderflowProtectionBuffer, 0, sizeof(char)*1024);
  
  EXC_TRY {
    printf("Testing stack underflow ...\n");
    element = pop(stack);
    printf(_ERR_ " stack underflow not detected\n");
    stackTestFailed++;
    // exit(-1);
  }
  EXC_CATCH(stack_underflow) { 
    printf(_OK_ "stack underflow captured\n"); 
  }
  EXC_CATCH(stack_function_not_implemented) {
    stackTestFailed++;
    printf(_ERR_ "stack pop function not implemented\n");
  }
  EXC_END;
  EXC_TRY {
    // test for trolling protection
    stack->top = STACK_LAST_ELEMENT_INDEX + 2;
    element = pop(stack);
    stackTestFailed++;
    printf(_ERR_ "POP must throw an exception when stack.top > STACK_LAST_ELEMENT_INDEX\n");
  }
  EXC_CATCH(stack_overflow) {
    printf(_OK_ "captured stack overflow with top > STACK_LAST_ELEMENT_INDEX\n");
  }
  EXC_CATCH(stack_function_not_implemented) {
    stackTestFailed++;
    printf(_ERR_ "stack pop function not implemented\n");
  }
  EXC_END;
  EXC_TRY {
    stack->top = STACK_EMPTY_INDEX - 1;
    element = pop(stack);
    stackTestFailed++;
    printf(_ERR_ "POP must throw an exception when stack.top < STACK_EMPTY_INDEX\n");
  }
  EXC_CATCH(stack_underflow) {
    printf(_OK_ "captured stack underflow with top < STACK_EMPTY_INDEX\n");
  }
  EXC_CATCH(stack_function_not_implemented) {
    stackTestFailed++;
    printf(_ERR_ "stack pop function not implemented\n");
  }
  EXC_END;
}

void testStackOverflow() {
  Stack * stack;
  Finger fingers[5];
  int i;
  static int numberOFStoredElements;
  
  printf("Testing stack overflow ...\n");

  stack = & stackWithProtection.stack;
  stackInitialize(stack);
  memset(stackWithProtection.stackOverflowProtectionBuffer, 0, sizeof(char)*1024);
  memset(stackWithProtection.stackUnderflowProtectionBuffer, 0, sizeof(char)*1024);
  createFingers(fingers);

  EXC_TRY {
    numberOFStoredElements = 0;
    for (i = 0; i <= STACK_CAPACITY; i++) {
      push(stack, &fingers[0]);
      numberOFStoredElements++;
    }
    stackTestFailed++;
    printf(_ERR_ "stack overflow not detected\n");
  }
  EXC_CATCH(stack_overflow) { 
    if (STACK_CAPACITY == numberOFStoredElements) {
      printf(_OK_ "stack overflow captured\n"); 
    } else {
      char message[1024];

      snprintf(message, 1024,
               "stack overflow before the buffer is full. Number of stored "
               "elements = %d. Expected %d\n",
               numberOFStoredElements, STACK_CAPACITY);
      stackTestFailed++;
      printf(_ERR_ "%s", message);
    }
  }
  EXC_CATCH(stack_function_not_implemented) {
    stackTestFailed++;
    printf(_ERR_ "stack pop function not implemented\n");
  }
  EXC_END;
  EXC_TRY {
    // test for trolling protection
    stack->top = STACK_LAST_ELEMENT_INDEX + 2;
    push(stack, &fingers[0]);
    stackTestFailed++;
    printf(_ERR_ "PUSH must throw an exception when stack.top >= STACK_LAST_ELEMENT_INDEX\n");
  }
  EXC_CATCH(stack_overflow) {
    printf(_OK_ "captured stack overflow with top > STACK_LAST_ELEMENT_INDEX\n");
  }
  EXC_CATCH(out_of_range) {
    printf(_OK_ "captured out_of_range with top > STACK_LAST_ELEMENT_INDEX\n");
  }
  EXC_CATCH(stack_function_not_implemented) {
    stackTestFailed++;
    printf(_ERR_ "stack push function not implemented\n");
  }
  EXC_END;
  EXC_TRY {
    stack->top = STACK_EMPTY_INDEX - 1;
    push(stack, &fingers[0]);
    stackTestFailed++;
    printf(_ERR_ "PUSH must throw an exception when stack.top < STACK_EMPTY_INDEX\n");
  }
  EXC_CATCH(stack_underflow) {
    printf(_OK_ "captured stack underflow with top < STACK_LAST_ELEMENT_INDEX\n");
  }
  EXC_CATCH(out_of_range) {
    printf(_OK_ "captured out_of_range with top < STACK_LAST_ELEMENT_INDEX\n");
  }
  EXC_CATCH(stack_function_not_implemented) {
    stackTestFailed++;
    printf(_ERR_ "stack push function not implemented\n");
  }
  EXC_END;
}

void testPop() {
  Stack * stack;
  Finger fingers[5];

  printf("Testing stack POP ... ");

  stack = & stackWithProtection.stack;
  stackInitialize(stack);
  memset(stackWithProtection.stackOverflowProtectionBuffer, 0, sizeof(char)*1024);
  memset(stackWithProtection.stackUnderflowProtectionBuffer, 0, sizeof(char)*1024);

  createFingers(fingers);
  EXC_TRY {
    Finger *f;

    printf("POP[0] ... ");
    stack->top++;
    stack->buffer[0] = fingers[0];
    f = pop(stack);
    if (STACK_EMPTY_INDEX != stack->top) {
      stackTestFailed++;
      printf(_ERR_ "stack.top must be STACK_EMPTY_INDEX now!\n");
    } else {
      printf(_OK_);
    }
    if (false == fingersEqual(f, &fingers[0])) {
      stackTestFailed++;
      printf(_ERR_ "'pop' did not return the expected element\n");
    } else {
      printf(_OK_);
    }
    printf("POP[N] ... ");
    stack->top = STACK_LAST_ELEMENT_INDEX;
    stack->buffer[STACK_LAST_ELEMENT_INDEX] = fingers[0];
    f = pop(stack);
    if (STACK_LAST_ELEMENT_INDEX - 1 != stack->top) {
      stackTestFailed++;
      printf(_ERR_ "stack.top must be STACK_LAST_ELEMENT_INDEX - 1 now!\n");
    } else {
      printf(_OK_);
    }
    if (false == fingersEqual(f, &fingers[0])) {
      stackTestFailed++;
      printf(_ERR_ "'pop' did not return the expected element\n");
    } else {
      printf(_OK_n);
    }
  }
  EXC_CATCH(stack_underflow) {
    stackTestFailed++;
    printf(_ERR_ "unexpected stack_underflow exception\n");
  }
  EXC_CATCH(stack_overflow) {
    stackTestFailed++;
    printf(_ERR_ "unexpected stack_overflow exception\n");
  }
  EXC_CATCH(out_of_range) {
    stackTestFailed++;
    printf(_ERR_ "unexpected out_of_range exception\n");
  }
  EXC_CATCH(invalid_pointer) {
    stackTestFailed++;
    printf(_ERR_ "unexpected invalid_pointer exception\n");
  }
  EXC_CATCH(stack_function_not_implemented) {
    printf(_ERR_ "stack pop function not implemented\n");
  }
  EXC_END;
}

void testPush() {
  Stack * stack;
  Finger fingers[5];

  printf("Testing stack PUSH ... ");
  stack = & stackWithProtection.stack;
  stackInitialize(stack);
  memset(stackWithProtection.stackOverflowProtectionBuffer, 0, sizeof(char)*1024);
  memset(stackWithProtection.stackUnderflowProtectionBuffer, 0, sizeof(char)*1024);

  createFingers(fingers);
  EXC_TRY {
    Finger *f;

    printf("PUSH[0] ... ");
    push(stack, &fingers[0]);
    if (STACK_EMPTY_INDEX + 1 != stack->top) {
      stackTestFailed++;
      printf(_ERR_ "stack.top must be STACK_EMPTY_INDEX+1 now!\n");
    } else {
      printf(_OK_);
    }
    f = &stack->buffer[0];
    if (false == fingersEqual(f, &fingers[0])) {
      stackTestFailed++;
      printf(_ERR_ "'push' did not store the passed element\n");
    } else {
      printf(_OK_);
    }
    printf("PUSH[LAST] ... ");
    stack->top = STACK_LAST_ELEMENT_INDEX - 1;
    push(stack, &fingers[0]);
    if (STACK_LAST_ELEMENT_INDEX != stack->top) {
      stackTestFailed++;
      printf(_ERR_ "stack.top must be STACK_LAST_ELEMENT_INDEX now!\n");
    } else {
      printf(_OK_);
    }
    f = &stack->buffer[STACK_LAST_ELEMENT_INDEX];
    if (false == fingersEqual(f, &fingers[0])) {
      stackTestFailed++;
      printf(_ERR_ "'push' did not store the passed element\n");
    } else {
      printf(_OK_n);
    }
  }
  EXC_CATCH(stack_underflow) {
    stackTestFailed++;
    printf(_ERR_ "unexpected stack_underflow exception\n");
  }
  EXC_CATCH(stack_overflow) {
    stackTestFailed++;
    printf(_ERR_ "unexpected stack_overflow exception\n");
  }
  EXC_CATCH(out_of_range) {
    stackTestFailed++;
    printf(_ERR_ "unexpected out_of_range exception\n");
  }
  EXC_CATCH(invalid_pointer) {
    stackTestFailed++;
    printf(_ERR_ "unexpected invalid_pointer exception\n");
  }
  EXC_CATCH(stack_function_not_implemented) {
    stackTestFailed++;
    printf(_ERR_ "stack push function not implemented\n");
  }
  EXC_END;
}

void testStack() {
  Stack stack;
  Finger fingers[5];
  Finger *f, *f2;

  printf("=============================================\n");
  printf("                  Testing stack\n");
  printf("=============================================\n");
  createFingers(fingers);
  stackInitialize(&stack);
  printStack(&stack);
  testStackUnderflow();
  testPop();
  testPush();
  printf("Testing push == pop ... ");
  EXC_TRY {
    push(&stack, &fingers[0]);
    f = pop(&stack);
    if (false == fingersEqual(f, &fingers[0])) {
      stackTestFailed++;
      printf(_ERR_ "pop did not return pushed element\n");
      // exit(-1);
    } else {
      printf(_OK_n);
    }
  }
  EXC_CATCH(stack_function_not_implemented) {
    stackTestFailed++;
    printf(_ERR_ "pop or push not implemented\n");
  }
  EXC_END;
  printf("Testing push1, push2 == pop2, pop1 ... ");
  EXC_TRY {
    push(&stack, &fingers[0]);
    push(&stack, &fingers[1]);
    f2 = pop(&stack);
    f = pop(&stack);
    if (false == fingersEqual(f2, &fingers[1])) {
      stackTestFailed++;
      printf(_ERR_ "pop did not return pushed element 2\n");
      // exit(-1);
    } else {
      printf(_OK_);
    }
    if (false == fingersEqual(f, &fingers[0])) {
      stackTestFailed++;
      printf(_ERR_ "pop did not return pushed element 1\n");
      // exit(-1);
    } else {
      printf(_OK_n);
    }
  }
  EXC_CATCH(stack_function_not_implemented) {
    stackTestFailed++;
    printf(_ERR_ "pop or push not implemented\n");
  }
  EXC_END;
  printf("Testing if stack is empty ... ");
  if (STACK_EMPTY_INDEX != stack.top) {
    stackTestFailed++;
    printf(_ERR_ "stack must be empty now\n");
    exit(-1);
  } else {
    printf(_OK_n);
  }
  EXC_TRY {
    push(&stack, &fingers[0]);
    push(&stack, &fingers[1]);
    push(&stack, &fingers[2]);
    push(&stack, &fingers[3]);
    push(&stack, &fingers[4]);
    printStack(&stack);
  }
  EXC_CATCH(stack_function_not_implemented) {
    stackTestFailed++;
    printf(_ERR_ "pop or push not implemented\n");
  }
  EXC_END;
  testStackOverflow();
  stackKiller();
  printf("=============================================\n");
  if(stackTestFailed) {
    printf(RED "          Test failed\n" reset);
  } else {
    printf(GRN "          Test succeed\n" reset);
  }
  printf("=============================================\n");
}
