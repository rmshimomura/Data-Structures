#include "libs.h"

#ifndef AVL_H
#define AVL_H

void* create_tree();
void* insert_tree(void* initial_tree, void* initial_node, void* element, int (*compare_nodes)(void*, void*));
void* get_left(void* node);
void* get_right(void* node);
void* get_node_data(void* node);
void* get_root(void* initial_tree);
int compare_x(void* node, void* element);
int height(void* node);
double get_original_x(void* node);
double get_max_w(void* node);
int get_balance(void* initial_node);
void* delete_node(void* initial_tree, void* initial_node, void* element, int (*compare_nodes)(void*, void*), void (*free_data)(void*), bool remove_e);
void destroy_AVL_tree(void* initial_tree, void* initial_node, void (*free_data)(void*));
void set_root(void* initialTree, void* new_root);
double get_min_x(void* node);
double get_max_x(void* node);
double find_max_w(void* sequence);
int check_nodes(void* node1, void* node2);
void printing_tree(void* initial_node, int space);
void recursive_print_tree(void* initial_tree); 

#endif