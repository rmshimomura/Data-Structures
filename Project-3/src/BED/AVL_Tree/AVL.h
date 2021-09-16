#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void* create_tree();
void* insert(void* initial_tree, void* initial_node, void* element, int (*compare_nodes)(void*, void*));
void* get_left(void* node);
void* get_right(void* node);
void* get_node_data(void* node);
void* get_root(void* initial_tree);
int compare_x(void* node, void* element);
void* delete_node(void* initial_tree, void* initial_node, void* element, int (*compare_nodes)(void*, void*), void (*free_data)(void*));
void destroy_AVL_tree(void* initial_tree, void* initial_node, void (*free_data)(void*));
void set_root(void* initialTree, void* new_root);
double get_min_x(void* node);
double get_max_x(void* node);
double get_list_max_x(void* sequence);
void printing_tree(void* initial_node, int space) ;
void recursive_print_tree(void* initial_tree) ;