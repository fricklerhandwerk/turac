#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../inc/card.h"
#include "../inc/stack.h"
#include "../inc/rules.h"
#include "../inc/cmd_view.h"

#define SIZE 36

int testStackInitDestroy(void)
{
	printf("Initializing stack with size %d...\n",SIZE);
	stackT *stack = stackInit(SIZE);
	printf("Stack size: %d\nStack top: %d\n",stack->size,stack->top);
	if (stack != NULL && stack->size == SIZE && stack->top == -1)
	{
		printf("OK.\n");
	}
	else
	{
		printf("MEMORY FAIL!\n");
		return(EXIT_FAILURE);
	}
	
	printf("Deallocating stack again...\n");
	stackDestroy(&stack);
	
	//printf("stack size: %d\n",stack->size);
	if (stack == NULL)
	{
		printf("OK.\n");
		return(EXIT_SUCCESS);
	}
	printf("Something went wrong!\n");
	return(EXIT_FAILURE);
}

int main()
{

	testStackInitDestroy();
	return(0);
}