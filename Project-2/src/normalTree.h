#include "bibliotecas.h"

#ifndef NORMAL_TREE_H
#define NORMAL_TREE_H

tree NT_create_tree();
node NT_create_new_node(item element);
node NT_get_root_node(tree current);
node NT_get_left_node(node current);
node NT_get_right_node(node current);
int NT_get_size(tree current);
void free_NT_tree(tree initialTree, node initialRoot);
void* NT_get_data(node current);
node NT_insert_shadow(tree initialTree, node initialNode, node generator, item element);
void NT_set_root_node(tree initialTree, node root);
void free_segments_tree(tree initialTree, node initialNode);

#endif