#include "range.c"
#include <assert.h>

int main(int argc, char** argv)
{
	int range[] = {4,5,6,7,8,9,10,11,12,13,14};
	int array[] = {1, 5, 38, -9, 5};
	char cArray[] = "Hola mundo";
	struct iterable* stack = stack_new(sizeof(int));
	int i, stack_contents[20], pop;
	
	for (i = 0; i < 20; i++)
	{
		stack_push(stack, (void*) &i);
		stack_contents[19 - i] = i;
	}
	
	puts("FOREACH STACK TEST");
	
	foreach(stack)
	{
		assert(stack_contents[INDEX] == INTVAR);
		printf("%d => %d\n", INDEX, INTVAR);
	}
	
	puts("\nFOREACH INT RANGE TEST");
	
	foreach (irange(4, 15))
	{
		assert(range[INDEX] == ITEM);
		printf("%d => %d\n", INDEX, ITEM);
	}
	
	puts("\nFOREACH INT ARRAY RANGE TEST");
	
	foreach (arange(array, 5, sizeof(int)))
	{
		assert(array[INDEX] == INTVAR);
		printf("%d => %d\n", INDEX, INTVAR);
	}
	
	puts("\nFOREACH CHAR ARRAY RANGE TEST");
	
	foreach (arange(cArray, 10, sizeof(char)))
	{
		assert(cArray[INDEX] == CHARVAR);
		printf("%d => %c\n", INDEX, CHARVAR);
	}
	
	free_ranges();
	return 0;
}