#include "bibliotecas.h"

#ifndef KD_TREE_H
#define KD_TREE_H
tree KD_create_tree();
node KD_get_root_node(tree current);
node KD_create_new_node(item element);
node KD_insert_rect(tree initialTree, node initialNode, node generator, item element, int level);
node KD_insert_circ(tree initialTree, node initialNode, node generator, item element, int level);
void inorder(node initialRoot);
void KD_set_root_node(node primeRoot, node modifyRoot);
node KD_get_left_node(node current);
node KD_get_right_node(node current);
void KD_destroy_rect_tree(tree initialTree, node initialRoot);
void KD_destroy_circ_tree(tree initialTree, node initialRoot);
bool KD_get_state(node current);
int KD_get_size(tree initialTree);
void set_type(tree initialTree, char type);
char get_type(tree initialTree);
int KD_get_size(tree initialTree);
void* KD_get_data(node current);
void KD_set_state(node current, bool state);
node KD_search_ID(node current, char* id);
void KD_set_size(tree initialTree, int size);
void rectangle_in_order(node initialNode);
void circle_in_order(node initialNode);
void KD_set_root_node(tree current, node modifyRoot);
void set_biggest_x(tree initialTree, double value);
void set_biggest_y(tree initialTree, double value);
double get_biggest_x(tree initialTree);
double get_biggest_y(tree initialTree);

#endif