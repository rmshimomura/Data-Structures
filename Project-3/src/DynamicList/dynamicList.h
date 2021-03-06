#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef DYNAMIC_LIST
#define DYNAMIC_LIST

typedef void* dynamic_list;

void* create_list();
int get_size(void* sequence);
void* insert_list(void* sequence, void* element);
void remove_node(void* sequence, void* current, void(free_data)(void*));
void free_list_hash(void* sequence);
void* get_list_element(void* current);
void* get_head(void* sequence);
void* get_next(void* current);
void* getLast(void* sequence);
void* get_previous(void* current);
void free_list(void* sequence, void (*freeList)(void*));
void* at_pos(void* sequence, int index);
void free_block_list(void* sequence);
void remove_node_special(void* sequence, void* current);
void* find_item(void* sequence, void* match, int (*compare_info)(void*, void*));

#endif