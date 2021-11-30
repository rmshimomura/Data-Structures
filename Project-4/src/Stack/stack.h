#include "../libs.h"

#ifndef STACK_H
#define STACK_H

void* create_stack();
void stack_push(void* sequence, void* element);
int stack_get_size(void* sequence);
void* stack_get_top(void* sequence);
void* stack_get_down(void* current);
void* stack_get_element(void* current);
void* stack_pop(void* sequence);
void stack_free(void* sequence, bool remove_elements);

#endif