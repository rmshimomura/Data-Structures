#include "bibliotecas.h"
#ifndef DYNAMICLIST_H_INCLUDED
#define DYNAMICLIST_H_INCLUDED

void* create_list();
int get_size(void* sequence);
void* insert(void* sequence, void* element);
void remove_node(void* sequence, void* current);
void* get_item(void* sequence, void* current);
void* get_head(void* sequence);
void* get_next(void* sequence, void* current);
void* getLast(void* sequence);
void* get_previous(void* sequence, void* current);
void free_list(void* sequence);
void* at_pos(void* sequence, int index);
void free_list_of_segments(void* sequence);
void free_list_of_trees_shadows(void* sequence);
double get_data_radiation(void* node);
void set_data_radiation(void* node, double radiation);
double get_data_x_meteor(void* node);
void set_data_x_meteor(void* node, double xMeteor);
double get_data_y_meteor(void* node);
void set_data_y_meteor(void* node, double yMeteor);

#endif