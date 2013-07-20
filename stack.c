#import "stack.h"

struct stack_base_func_table stack_func_table = {
	stack_has_next,
	stack_get_next,
	stack_incr_index,
	stack_reset_index,
	stack_push,
	stack_pop
};

struct iterable* stack_new(size_t item_size)
{
	struct iterable* stack = malloc(sizeof(*stack));
	struct stack_data* sdata = malloc(sizeof(*sdata));
	stack->funcs = (struct iterable_func_table*) &stack_func_table;
	stack->data = sdata;
	
	sdata->item_size = item_size;
	sdata->size = 0;
	sdata->items = NULL;
	sdata->index = -1;
	
	return stack;
}

void free_stack(struct iterable* iter)
{
	struct stack_data* data = (struct stack_data*) iter->data;
	free(data->items);
	free(data);
	free(iter);
}

short stack_has_next(struct iterable* iter)
{
	struct stack_data* data = (struct stack_data*) iter->data;
	return ((int) data->index + 1) < ((int) data->size);
}

void* stack_get_next(struct iterable* iter)
{
	struct stack_data* data = (struct stack_data*) iter->data;
	return (void*) (((char*) data->items) + (data->item_size * data->size) - (data->index) * data->item_size);
}

void stack_incr_index(struct iterable* iter)
{
	struct stack_data* data = (struct stack_data*) iter->data;
	data->index++;
}

void stack_reset_index(struct iterable* iter)
{
	struct stack_data* data = (struct stack_data*) iter->data;
	data->index = -1;
}

void stack_push(struct iterable* iter, void* item)
{
	struct stack_data* data = (struct stack_data*) iter->data;
	data->size++;
	if (data->items == NULL)
		data->items = malloc(data->item_size * (data->size + 1));
	else
		data->items = realloc(data->items, data->item_size * (data->size + 1));
	memcpy((void*) (((char*) data->items) + (data->item_size * data->size)), item, data->item_size);
}

void* stack_pop(struct iterable* iter)
{
	struct stack_data* data = (struct stack_data*) iter->data;
	data->size--;
	return (void*) (((char*) data->items) + (data->item_size * (data->size + 1)));
}
