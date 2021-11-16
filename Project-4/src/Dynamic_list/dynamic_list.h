#include "../libs.h"

#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

void* create_list();
int get_size(void* sequence);
void* insert_list(void* sequence, void* element);
void* insert_first(void* sequence, void* element);
void* remove_node(void* sequence, void* node_to_remove, void (*free_node)(void*), bool remove_elements);
void list_sort(void* list_, int (*cmp)(void*, void*));
void* get_list_element(void* current);
void* get_head(void* sequence);
void* get_end(void* sequence);
void* get_next(void* current);
void* getLast(void* sequence);
void* get_previous(void* current);
void free_list(void* sequence, bool remove_elements, void (*free_node)(void*));
void* at_pos(void* sequence, int index);
void* find_element(void* sequence, void* match, int (*compare_info)(void*, void*));

void* find_element_by_vertex_name(void* sequence, void* match);
void free_block_list(void* sequence);

#endif