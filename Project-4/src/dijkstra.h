#include "libs.h"

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

void* dijkstra(void* connections, char* start, char* end, double (*operation_mode)(void*));
void to_string(void* path_node);
void free_helper(void* data);
void* get_dijkstra_vertex(void* data);

#endif