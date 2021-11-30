#include "../libs.h"

#ifndef GRAPH_H
#define GRAPH_H

void* create_graph(int size);
void* create_vertex(char* id, double x, double y);
void* graph_get_vertexes(void* connections);
int graph_get_size(void* connections);
void* vertex_get_data(void* v);
void* vertex_get_edges(void* v);
int vertex_get_activated(void* v);
void vertex_set_activated(void* v, bool activated);
void vertex_set_edges(void* v, void* address);
void* return_vertex_address_by_index(void* connections, int index);
void* edge_get_data(void* e);
void* edge_get_from(void* e);
void* edge_get_to(void* e);
void* extract_all_edges(void* connections);
void graph_insert_vertex(void* connections, void* vertex_created);
void* graph_find_vertex(void* connections, char* vertex_id);
void* extract_all_activated_vertexes_from_list(void* sequence);
void graph_insert_edge(void* connections, char* name, char* vertex_1, char* vertex_2, char* left_side_square, char* right_side_square, double length, double average_speed);
void graph_remove_edge(void* connections, char* vertex_1, char* vertex_2, bool remove_vertexes);
void* find_edge(void* v1_edges, void* v2);
int adjacent(void* connections, char* vertex_1, char* vertex_2);
void* list_of_adjacents_by_name(void* connections, char* vertex_1);
void* list_of_adjacents_by_address(void* vertex_1);
void free_graph(void* connections);
void free_edge(void* edge_);
void free_vertex(void* data);
void free_graph_vertexes(void* connections);
void create_graph_with_data(void* connections, FILE* file_roads);

void* extract_all_edges_cx(void* connections, double limiar, void* list_of_modifications);

#endif