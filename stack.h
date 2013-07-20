#include "iterable.c"

extern struct iterable* stack_new(size_t item_size);
extern short stack_has_next(struct iterable* iter);
extern void* stack_get_next(struct iterable* iter);
extern void stack_incr_index(struct iterable* iter);
extern void stack_reset_index(struct iterable* iter);
extern void stack_push(struct iterable* iter, void* item);
extern void* stack_pop(struct iterable* iter);
extern void free_stack(struct iterable* iter);

struct stack_base_func_table {
	short (*has_next) (struct iterable*iter);
	void* (*next_item) (struct iterable* iter);
	void (*incr_index) (struct iterable* iter);
	void (*reset_index) (struct iterable* iter);
	void (*push) (struct iterable* iter, void* item);
	void* (*pop) (struct iterable* iter);
};

struct stack_data {
	size_t item_size;
	size_t size;
	size_t index;
	void* items;
};