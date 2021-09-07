#include "AVL.h"
#include "../DynamicList/dynamicList.h"

typedef struct node {
    struct node* left;
    struct node* right;
    void* data;
    int height;

} node_t;

typedef struct tree {
    int size;
    node_t* root;

} tree_t;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(void* node) {
    
    if (!node) return 0;

    return ((node_t*)node)->height;
}

void* create_tree(){
    tree_t* new_tree = calloc(1, sizeof(tree_t));
    new_tree->root = NULL;
    new_tree->size = 0;
    return new_tree;
}

void* new_node(void* data) {

    node_t* node_aux = calloc(1, sizeof(node_t));
    node_aux->data = create_list();
    insert_list(node_aux->data, data);
    node_aux->left = NULL;
    node_aux->right = NULL;
    node_aux->height = 1;
    return node_aux;
    
}

int get_balance(void* initial_node) {
    
    if (!initial_node)
        return 0;
        
    node_t* left = initial_node;
    node_t* right = initial_node;

    return height(left->left) - height(right->right);
    
}

void* right_rotate(void* initial_node) {
    
    if (initial_node) {
        node_t* main_node = initial_node;

        node_t* aux1 = main_node->left;
        node_t* aux2 = aux1->right;

        aux1->right = initial_node;
        main_node->left = aux2;

        main_node->height = max(height(main_node->left), height(main_node->right)) + 1;
        aux1->height = max(height(aux1->left), height(aux1->right)) + 1;

        return aux1;
    }
}

void* left_rotate(void* initial_node) {
    if (initial_node) {
        node_t* main_node = initial_node;

        node_t* aux1 = main_node->right;
        node_t* aux2 = aux1->left;

        aux1->left = initial_node;
        main_node->right = aux2;

        main_node->height = max(height(main_node->left), height(main_node->right)) + 1;
        aux1->height = max(height(aux1->left), height(aux1->right)) + 1;

        return aux1;
    }
}

void* smallest_node(void* node) {
    node_t* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

void* insert(void* initial_tree, void* initial_node, void* element, int (*compare_nodes)(void*, void*)) {

    tree_t* tree_aux = initial_tree;
    node_t* node_aux = initial_node;

    if (!node_aux) {
        tree_aux->size++;
        return new_node(element);
    }
    if (compare_nodes(get_list_element(get_head(node_aux->data)), element) == 1) {
        node_aux->right = insert(tree_aux, node_aux->right, element, compare_nodes);

    } else if (compare_nodes(node_aux, element) == -1) {
        node_aux->left = insert(tree_aux, node_aux->left, element, compare_nodes);

    } else {
        insert_list(get_node_data(node_aux), element);
    }

    node_aux->height = 1 + max(height(node_aux->left), height(node_aux->right));
    
    int balance = get_balance(initial_node);

    if (balance > 1 && compare_nodes(get_list_element(get_head(node_aux->left->data)), element) == -1) {
        //LL
        return right_rotate(initial_node);
    }

    if (balance < -1 && compare_nodes(get_list_element(get_head(node_aux->right->data)), element) == 1) {
        //RR
        return left_rotate(initial_node);
    }

    if (balance > 1 && compare_nodes(get_list_element(get_head(node_aux->left->data)), element) == 1) {
        //LR
        node_aux->left = left_rotate(node_aux->left);
        return right_rotate(initial_node);
    }

    if (balance < -1 && compare_nodes(get_list_element(get_head(node_aux->right->data)), element) == -1) {
        //RL
        node_aux->right = right_rotate(node_aux->right);
        return left_rotate(initial_node);
    }

    return node_aux;
}

void printing_tree(void* initial_node, int space) {
    node_t* aux = initial_node;

    if (!aux) return;

    space += 10;

    printing_tree(aux->right, space);
    puts(" ");

    for (int i = 10; i < space; i++) printf(" ");

    printf("[%d]/-/[%d]\n", *((int*)aux->data), aux->height);

    printing_tree(aux->left, space);
}

void recursive_print_tree(void* initial_tree) {
    tree_t* tree_to_print = initial_tree;
    printing_tree(tree_to_print->root, 0);
}

void* get_left(void* node) {
    return ((node_t*)(node))->left;
}

void* get_right(void* node) {
    return ((node_t*)(node))->right;
}

void* get_node_data(void* node) {
    return ((node_t*)(node))->data;
}

void* delete_node(void* initial_tree, void* initial_node, void* element, int (*compare_nodes)(void*, void*), void (*free_data)(void*)) {
    if (!initial_node || !initial_tree) return initial_node;

    tree_t* tree_aux = initial_tree;
    node_t* node_aux = initial_node;

    if (compare_nodes(node_aux, element) == 1) {
        node_aux->right = delete_node(tree_aux, node_aux->right, element, compare_nodes, free_data);

    } else if (compare_nodes(node_aux, element) == -1) {
        node_aux->left = delete_node(tree_aux, node_aux->left, element, compare_nodes, free_data);

    } else {
        if (!(node_aux->left) || !(node_aux->right)) {  //One or no child

            node_t* temp = node_aux->left ? node_aux->left : node_aux->right;

            if (!temp) {

                free(node_aux);
                free_data(node_aux->data);
                return temp;

            } else {  

                if (!node_aux->left) {
                    node_t* aux = node_aux->right;
                    free_data(node_aux->data);
                    
                    free(node_aux);
                    return aux;
                } else if (!node_aux->right) {
                    node_t* aux = node_aux->left;
                    free_data(node_aux->data);
                    free(node_aux);
                    return aux;
                }
            }

        } else {

            node_t* temp = smallest_node(node_aux->right);

            node_aux->data = temp->data;

            node_aux->right = delete_node(tree_aux, node_aux->right, temp->data, compare_nodes, free_data);
        }
    }

    if (!node_aux) return initial_node;

    node_aux->height = 1 + max(height(node_aux->left), height(node_aux->right));

    int balance = get_balance(initial_node);

    if (balance > 1 && get_balance(node_aux->left) >= 0) {
        //LL
        return right_rotate(initial_node);
    }

    if (balance < -1 && get_balance(node_aux->left) <= 0) {
        //RR
        return left_rotate(initial_node);
    }

    if (balance > 1 && get_balance(node_aux->left) < 0) {
        //LR
        node_aux->left = left_rotate(node_aux->left);
        return right_rotate(initial_node);
    }

    if (balance < -1 && get_balance(node_aux->right) > 0) {
        //RL
        node_aux->right = right_rotate(node_aux->right);
        return left_rotate(initial_node);
    }

    return node_aux;
}

void destroy_AVL_tree(void* initial_tree, void* initial_node, void (*free_data)(void*)) {
    tree_t* aux_tree = initial_tree;
    node_t* aux_node = initial_node;
    if (aux_node) {
        destroy_AVL_tree(aux_tree, aux_node->left, free_data);
        destroy_AVL_tree(aux_tree, aux_node->right, free_data);

        free_data(aux_node->data);
        free(aux_node);
    }
}

void pre_order(void* initial_node) {
    if (initial_node) {
        node_t* aux = initial_node;
        pre_order(aux->left);
        pre_order(aux->right);
    }
}

void* get_root(void* initial_tree){
    return ((tree_t*)initial_tree)->root;
}