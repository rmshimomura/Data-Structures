#include "libs.h"

#ifndef VERTEX_H
#define VERTEX_H

void* new_vertex_data(char* id, double x, double y);
void free_vertex_data(void* data);
char* vertex_data_get_id(void* data);
double vertex_data_get_x(void* data);
double vertex_data_get_y(void* data);
void vertex_data_set_id(void* data, char* id);
void vertex_data_set_x(void* data, double x);
void vertex_data_set_y(void* data, double y);

#endif