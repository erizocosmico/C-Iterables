#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.c"
#include <assert.h>

int main(int argc, char** argv)
{
	struct iterable* stack = stack_new(sizeof(int));
	int i, stack_contents[20], pop;
	
	for (i = 0; i < 20; i++)
	{
		printf("Push: %d\n", i);
		stack_push(stack, (void*) &i);
		stack_contents[19 - i] = i;
	}
	
	for (i = 0; i < 20; i++)
	{
		pop = *((int*)stack_pop(stack));
		assert(stack_contents[i] == pop);
		printf("Pop: %d\n", pop);
	}

	return 0;
}