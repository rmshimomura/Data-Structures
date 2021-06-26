#include "normalTree.h"

#include "dynamicList.h"
#include "polygon.h"
#include "segments.h"

typedef struct node_t {
    struct node_t* left;
    struct node_t* right;
    void* data;
    bool activated;

} node_t;

typedef struct tree_t {
    int size;
    node_t* root;

} tree_t;

tree NT_create_tree() {
    tree_t* aux = calloc(1, sizeof(tree_t));
    aux->size = 0;
    aux->root = NULL;
    return aux;
}

node NT_create_new_node(item element) {
    node_t* aux = calloc(1, sizeof(node_t));
    aux->data = element;
    aux->left = aux->right = NULL;
    aux->activated = false;
    return aux;
}

int NT_get_size(tree current) {
    tree_t* aux = current;
    return aux->size;
}

node NT_get_root_node(tree current) {
    tree_t* aux = current;
    return aux->root;
}

node NT_get_left_node(node current) {
    node_t* aux = current;
    return aux->left;
}

node NT_get_right_node(node current) {
    node_t* aux = current;
    return aux->right;
}

bool NT_get_state(node current) {
    node_t* aux = current;
    return aux->activated;
}

void NT_set_state(node current, bool state) {
    node_t* aux = current;
    aux->activated = state;
}

node NT_insert_shadow(tree initialTree, node initialNode, node generator, item element) {
    tree_t* treeAux = initialTree;
    node_t* nodeAux = initialNode;

    if (!nodeAux) {
        nodeAux = NT_create_new_node(element);
        treeAux->size++;

    } else if (get_minimum_x(element) >= get_minimum_x(nodeAux->data)) {
        nodeAux->right = NT_insert_shadow(initialTree, nodeAux->right, nodeAux, element);

    } else if (get_minimum_x(element) < get_minimum_x(nodeAux->data)) {
        nodeAux->left = NT_insert_shadow(initialTree, nodeAux->left, nodeAux, element);
    }

    return nodeAux;
}

void free_NT_tree(tree initialTree, node initialRoot) {
    tree_t* auxTree = initialTree;
    node_t* auxRoot = initialRoot;

    if (initialRoot) {
        if (auxRoot->left)
            free_NT_tree(auxTree, auxRoot->left);
        if (auxRoot->data != NULL) {
            free_shadow_polygons_array(auxRoot->data);
        }
        free(auxRoot->data);
        if (auxRoot->right)
            free_NT_tree(auxTree, auxRoot->right);
        free(auxRoot);
    }
}

void free_segments_tree(tree initialTree, node initialNode) {
    node_t* auxRoot = initialNode;

    if (auxRoot->left)
        free_segments_tree(initialTree, auxRoot->left);

    auxRoot->data = NULL;

    if (auxRoot->right)
        free_segments_tree(initialTree, auxRoot->right);

    free(auxRoot);
}

void* NT_get_data(node current) {
    node_t* aux = current;
    return aux->data;
}

void NT_set_root_node(tree initialTree, node root) {
    tree_t* treeAux = initialTree;
    treeAux->root = root;
}
