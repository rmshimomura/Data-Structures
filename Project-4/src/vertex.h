#include "libs.h"

void* new_vertex_data(char* id, double x, double y);
void free_vertex_data(void* data);
char* vertex_get_id(void* data);
double vertex_get_x(void* data);
double vertex_get_y(void* data);
void vertex_set_id(void* data, char* id);
void vertex_set_x(void* data, double x);
void vertex_set_y(void* data, double y);