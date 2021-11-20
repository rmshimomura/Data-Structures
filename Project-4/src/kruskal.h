#include "libs.h"


#ifndef KRUSKAL_H
#define KRUSKAL_H

void** kruskal(void* edges_list);
void* get_package_list_of_edges (void* data);
void* get_package_root (void* data);
void rv_function_aux(void* edges[], int num_of_edges, void* root, int height, double factor);
void free_package(void* pack);

#endif