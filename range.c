#include "range.h"

struct iterable* range_stack = NULL;
struct range_base_func_table range_func_table = {
	range_has_next,
	range_get_next,
	range_incr_index,
	range_reset_index
};
struct iterable* current_range;

struct iterable* irange(int start, int end)
{
	t_range_constraints constraints;
	constraints.init = start;
	constraints.end = end;
	constraints.source = NULL;
	return create_range(constraints);
}

struct iterable* arange(void* array, size_t length, size_t item_size)
{
	t_range_constraints constraints;
	constraints.source = array;
	constraints.item_size = item_size;
	constraints.items = length;
	return create_range(constraints);
}

void end_range()
{
	current_range = NULL;
}

void push_range(struct iterable* range)
{
	if (range_stack == NULL)
		range_stack = stack_new(sizeof(*range));
	stack_push(range_stack, (void*) range);
}

int get_range_index(struct iterable* range)
{
	if (range == NULL)
		return 0;
	return ((struct range_data*) range->data)->index;
}

int get_range_size(struct iterable* range)
{
	if (range == NULL)
		return 0;
	return ((struct range_data*) range->data)->size;
}

int get_range_int_var(struct iterable* range)
{
	if (range == NULL)
		return 0;
	return *((int*) range->funcs->next_item(range));
}

void* get_range_var(struct iterable* range)
{
	if (range == NULL)
		return NULL;
	return range->funcs->next_item(range);
}

short range_next()
{
	struct iterable* range;
	
	if (current_range == NULL)
		current_range = (struct iterable*) stack_pop(range_stack);
	range = current_range;
	
	short has_next = range->funcs->has_next(range);
	if (!has_next)
		current_range = NULL;
	else
		((struct range_data*) range->data)->index++;
	
	return has_next;
}

void free_ranges()
{
	free_stack(range_stack);
}

struct iterable* create_range(t_range_constraints constraints)
{
	int i, pos = 0;
	struct iterable* range = malloc(sizeof(*range));
	struct range_data* data = malloc(sizeof(*data));
	range->funcs = (struct iterable_func_table*) &range_func_table;
	range->data = data;
	if (constraints.source == NULL)
	{
		data->size = constraints.end - constraints.init;
		data->item_size = sizeof(int);
		data->items = malloc(sizeof(int) * (data->size + 1));
		for (i = constraints.init; i < constraints.end; i++)
			((int*) data->items)[pos++] = i;
	}
	else
	{
		data->size = constraints.items;
		data->items = constraints.source;
		data->item_size = constraints.item_size;
	}
	data->index = -1;
	
	return range;
}

short range_has_next(struct iterable* iter)
{
	struct range_data* data = (struct range_data*) iter->data;
	return ((int) data->index + 1) < ((int) data->size);
}

void* range_get_next(struct iterable* iter)
{
	struct range_data* data = (struct range_data*) iter->data;
	return (void*) (((char*) data->items) + (data->item_size * data->index));
}

void range_incr_index(struct iterable* iter)
{
	struct range_data* data = (struct range_data*) iter->data;
	data->index++;
}

void range_reset_index(struct iterable* iter)
{
	struct range_data* data = (struct range_data*) iter->data;
	data->index = -1;
}

void free_range(struct iterable* iter)
{
	struct range_data* data = (struct range_data*) iter->data;
	free(data->items);
	free(data);
	free(iter);
}