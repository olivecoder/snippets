/*
   resizable array for C
   Robert Oliveira
*/

#include <assert.h> 
#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int *items;
	int n_items;
} vector;

vector vector_new(int n_items) 
{ 
	// returns NULL on failure
	vector v = { NULL, 0};
	v.n_items = n_items;
	v.items = malloc(n_items * sizeof(*v.items));
	return v;
}

void vector_delete(vector *v) 
{
	assert(v->items);
	free(v->items);
	v->items=NULL;
}

int vector_resize(vector *v, int n_items)
{
	void *new_items;
	assert(v!=NULL);
	assert(n_items>0);
	new_items = realloc(v->items, n_items * sizeof(*v->items));
	if ( new_items!=NULL ) { 
		v->items = new_items;
		v->n_items = n_items;
	}
	return new_items!=NULL;
}

int vector_set(vector *v, int index, int item) 
{
	assert(v!=NULL);
	if ( index >= v->n_items ) { 
		vector_resize(v, index+8);
	}
	if ( index < v->n_items ) { 
		v->items[index] = item;
	}
	return index < v->n_items;
}

int vector_test(void) 
{
	vector v = vector_new(5);
	int i;
	for (i=0; i<5; i++) assert(vector_set(&v, i, i*10));
	for (i=5; i<10; i++) assert(vector_set(&v, i, i*10));
	for (i=0; i<10; i++) printf("item[%i] = %i\n", i, v.items[i]);
	vector_delete(&v);
}

main() 
{
	vector_test();
}
