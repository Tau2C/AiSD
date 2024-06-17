#include <stdio.h>
#include "collections/LinkedList.h"
#include "tests/TestDataTypes.h"
#include "tests/TestStack.h"
#include "tests/TestQueue.h"
#include "exception/exception.h"

int main(void)
{
	testStack();
	testQueue();
	return 0;
}
