struct iterable {
	struct iterable_func_table *funcs;
	void *data;
};

struct iterable_func_table {
	short (*has_next) (struct iterable* iter);
	void* (*next_item) (struct iterable* iter);
	void (*incr_index) (struct iterable* iter);
	void (*reset_index) (struct iterable* iter);
};

extern void* iterable_get_next(struct iterable* iter);
extern short iterable_has_next(struct iterable* iter);