#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef void* dynamic_list;

void* create_list();
int get_size(void* sequence);
void insert_list(void* sequence, void* element);
void remove_node(void* sequence, void* node_to_remove, void (*free_node)(void*), bool remove_elements);
void* get_list_element(void* current);
void* get_head(void* sequence);
void* get_next(void* current);
void* getLast(void* sequence);
void* get_previous(void* current);
void free_list(void* sequence, bool remove_elements, void (*free_node)(void*));
void* at_pos(void* sequence, int index);