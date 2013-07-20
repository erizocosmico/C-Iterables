#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.c"

#define ITEM get_range_int_var(current_range) 
#define VAR get_range_var(current_range)
#define INDEX get_range_index(current_range)
#define SIZE get_range_size(current_range)
#define foreach(range) push_range(range);while(range_next())
#define INTVAR *((int*) get_range_var(current_range))
#define FLOATVAR *((float*) get_range_var(current_range))
#define DOUBLEVAR *((double*) get_range_var(current_range))
#define SHORTVAR *((short*) get_range_var(current_range))
#define CHARVAR *((char*) get_range_var(current_range))
#define LONGVAR *((long*) get_range_var(current_range))
#define LONGLONGVAR *((long long*) get_range_var(current_range))
#define STRVAR ((char*) get_range_var(current_range))

typedef struct {
	int init;
	int end;
	void* source;
	size_t item_size;
	size_t items;
} t_range_constraints;

extern struct iterable* range_stack;
extern struct iterable* current_range;

extern struct iterable* irange(int, int);
extern struct iterable* arange(void* array, size_t length, size_t item_size);
extern void end_range();
extern void push_range(struct iterable* range);
extern short is_int_range(struct iterable* range);
extern int get_range_int_var(struct iterable* range);
extern void* get_range_var(struct iterable* range);
extern short range_has_next(struct iterable* range);
extern short range_next();
extern int get_range_index(struct iterable* range);
extern int get_range_size(struct iterable* range);
extern struct iterable* create_range(t_range_constraints constraints);
extern void free_ranges();
extern short range_has_next(struct iterable* iter);
extern void* range_get_next(struct iterable* iter);
extern void range_incr_index(struct iterable* iter);
extern void range_reset_index(struct iterable* iter);
extern void free_range(struct iterable* iter);

struct range_base_func_table {
	short (*has_next) (struct iterable*iter);
	void* (*next_item) (struct iterable* iter);
	void (*incr_index) (struct iterable* iter);
	void (*reset_index) (struct iterable* iter);
};

struct range_data {
	size_t item_size;
	size_t size;
	size_t index;
	void* items;
};