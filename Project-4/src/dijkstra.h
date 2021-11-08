#include "libs.h"

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

void* dijkstra(void* connections, char* start, char* end);
void to_string(void* path_node);

#endif