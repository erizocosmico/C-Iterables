#include "iterable.h"

void* iterable_get_next(struct iterable* iter)
{
	short has_next = iter->funcs->has_next(iter);
	void* next_item = NULL;
	if (has_next)
	{
		next_item = iter->funcs->next_item(iter);
		iter->funcs->incr_index(iter);
	}
	
	return next_item;
}

short iterable_has_next(struct iterable* iter)
{
	return iter->funcs->has_next(iter);
}