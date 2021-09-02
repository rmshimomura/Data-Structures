#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void* dynamic_list;

void* create_list();
int get_size(void* sequence);
void* insert(void* sequence, void* element);
void remove_node(void* sequence, void* current, void (free_data)(void*));
void* get_item(void* current);
void* get_head(void* sequence);
void* get_next(void* current);
void* getLast(void* sequence);
void* get_previous(void* current);
void free_list(void* sequence, void (*freeList)(void*));
void* at_pos(void* sequence, int index);
void* findItem(void* sequence, void* match);