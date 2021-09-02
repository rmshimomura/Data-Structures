#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void* dynamic_list;

void* create_list();
int get_size(void* sequence);
void* insert(void* sequence, void* element);
void remove_node(void* sequence, void* current);
void* get_item(void* current);
void* get_head(void* sequence);
void* get_next(void* current);
void* getLast(void* sequence);
void* get_previous(void* current);
void free_list(void* sequence);
void* at_pos(void* sequence, int index);