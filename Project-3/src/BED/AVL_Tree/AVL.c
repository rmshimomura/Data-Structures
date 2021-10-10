#include "AVL.h"
#include "../DynamicList/dynamicList.h"
#include "../block.h"

typedef struct node {
    struct node* left;
    struct node* right;
    void* data;
    int height;
    double min_x;
    double max_x;
    double original_x;
    double max_w;

} node_t;

typedef struct tree {
    int size;
    node_t* root;

} tree_t;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
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
    node_aux->original_x = get_x(data);
    node_aux->max_w = get_w(data);
    node_aux->min_x = get_x(data);
    node_aux->max_x = get_x(data) + get_w(data);

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

        if(aux1->max_x < main_node->max_x) { 
            /*
            Here we're checking if the max_x value is on the left or right side of the old root.
            If this conditional evaluates true, then the max value is on the right of the old root, else is on the left.
            */
            aux1->max_x = main_node->max_x;
        }

        if(main_node->left){
            
            main_node->min_x = main_node->left->min_x; //min_x value of the now rotate node is going to be the value of his left child

        }else{

            main_node->min_x = main_node->original_x; //If there's no left child get the x coordinate from the first position on the list

        }

        if(main_node->left || main_node->right){

            main_node->max_x = main_node->left->max_x > main_node->right->max_x ? main_node->left->max_x : main_node->right->max_x; //Check which one of its children has a greater max_x

        }else{
            
            main_node->max_x = main_node->original_x + main_node->max_w; //If there's no child, search on the list of blocks this node has

        }

        if(aux1->left){
            if(aux1->right){
                if(aux1->min_x > aux1->left->min_x || aux1->min_x > aux1->right->min_x ){

                    aux1->min_x = min(aux1->left->min_x, aux1->right->min_x);
                }
            }
            if(aux1->min_x > aux1->left->min_x) {
                aux1->min_x = aux1->left->min_x;
            }
        }

        if(aux1->right) {

            if(aux1->right->min_x < aux1->min_x){
                aux1->min_x = aux1->right->min_x;
            }
        }

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

        if(aux1->max_x < main_node->max_x) { 
            /*
            Here we're checking if the max_x value is on the left or right side of the old root.
            If this conditional evaluates true, then the max value is on the right of the old root, else is on the left.
            */
            aux1->max_x = main_node->max_x;
        }

        if(main_node->left){
            
            main_node->min_x = main_node->left->min_x; //min_x value of the now rotate node is going to be the value of his left child

        }else{

            main_node->min_x = main_node->original_x; //If there's no left child get the x coordinate from the first position on the list

        }

        if(main_node->left || main_node->right){

            main_node->max_x = main_node->left->max_x > main_node->right->max_x ? main_node->left->max_x : main_node->right->max_x; //Check which one of its children has a greater max_x

        }else{
            
            main_node->max_x = main_node->original_x + main_node->max_w; //If there's no child, search on the list of blocks this node has

        }

        if(aux1->left){
            if(aux1->right){
                if(aux1->min_x > aux1->left->min_x || aux1->min_x > aux1->right->min_x ){

                    aux1->min_x = min(aux1->left->min_x, aux1->right->min_x);
                }
            }
            if(aux1->min_x > aux1->left->min_x) {
                aux1->min_x = aux1->left->min_x;
            }
        }

        if(aux1->right) {

            if(aux1->right->min_x < aux1->min_x){
                aux1->min_x = aux1->right->min_x;
            }
        }

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

double get_original_x(void* node){
    node_t* aux = node;
    return aux->original_x;
}

double get_max_w(void* node){
    node_t* aux = node;
    return aux->max_w;
}

void* insert(void* initial_tree, void* initial_node, void* element, int (*compare_nodes)(void*, void*)) {

    tree_t* tree_aux = initial_tree;
    node_t* node_aux = initial_node;

    if (!node_aux) {
        tree_aux->size++;
        return new_node(element);
    }
    if (compare_nodes(node_aux, element) == 1) {

        if(get_x(element) < node_aux->min_x) node_aux->min_x = get_x(element);
        
        if(get_x(element) + get_w(element) > node_aux->max_x) node_aux->max_x = get_x(element) + get_w(element);
        
        node_aux->right = insert(tree_aux, node_aux->right, element, compare_nodes);

    } else if (compare_nodes(node_aux, element) == -1) {

        if(get_x(element) < node_aux->min_x) node_aux->min_x = get_x(element);
        
        if(get_x(element) + get_w(element) > node_aux->max_x) node_aux->max_x = get_x(element) + get_w(element);

        node_aux->left = insert(tree_aux, node_aux->left, element, compare_nodes);

    } else {

        if(get_w(element) > node_aux->max_w){
            node_aux->max_w = get_w(element);
        }
        insert_list(get_node_data(node_aux), element);
    }

    node_aux->height = 1 + max(height(node_aux->left), height(node_aux->right));
    
    int balance = get_balance(initial_node);

    if (balance > 1 && compare_nodes(node_aux->left, element) == -1) {
        //LL
        return right_rotate(initial_node);
    }

    if (balance < -1 && compare_nodes(node_aux->right, element) == 1) {
        //RR
        return left_rotate(initial_node);
    }

    if (balance > 1 && compare_nodes(node_aux->left, element) == 1) {
        //LR
        node_aux->left = left_rotate(node_aux->left);
        return right_rotate(initial_node);
    }

    if (balance < -1 && compare_nodes(node_aux->right, element) == -1) {
        //RL
        node_aux->right = right_rotate(node_aux->right);
        return left_rotate(initial_node);
    }

    return node_aux;
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

void update_min_and_max(void* initial_node){

    node_t* aux = initial_node;

    if(aux->left) {

        if(aux->left->min_x < aux->min_x) {
            aux->min_x = aux->left->min_x;
        }

        if(aux->left->max_x > aux->max_x) {
            aux->max_x = aux->left->max_x;
        }

    }

    if(aux->right) {

        if(aux->right->min_x < aux->min_x) {
            aux->min_x = aux->right->min_x;
        }

        if(aux->right->max_x > aux->max_x) {
            aux->max_x = aux->right->max_x;
        }

    }

}

void* delete_node(void* initial_tree, void* initial_node, void* element, int (*compare_nodes)(void*, void*), void (*free_data)(void*)) {
    
    if (!initial_node || !initial_tree) return initial_node;

    tree_t* tree_aux = initial_tree;
    node_t* node_aux = initial_node;

    if (compare_nodes(node_aux, element) == 1) {
        node_aux->right = delete_node(tree_aux, node_aux->right, element, compare_nodes, free_data);
        if(node_aux->right) update_min_and_max(node_aux->right);

    } else if (compare_nodes(node_aux, element) == -1) {
        node_aux->left = delete_node(tree_aux, node_aux->left, element, compare_nodes, free_data);
        if(node_aux->left) update_min_and_max(node_aux->left);

    } else {

        if(get_size(node_aux->data) > 1){ //Here, we have more than one block, so removing the node is unnecessary

            if(get_x(element) + get_w(element) == node_aux->max_x){
                
                //Check if the block that is going to be removed is the block that gives the maximum value to the node

                remove_node(node_aux->data, element, free_single_block); //Search on the list for the block that we need to remove
                
                //After removing the block, element won't exist anymore, so we need to update the rest of the path made until here, using update_max()

                node_aux->max_w = find_max_w(node_aux->data);
                node_aux->max_x = node_aux->original_x + node_aux->max_w;
                
            }else{

                remove_node(node_aux->data, element, free_single_block);

            }

        } else { //Here, we are considering that there is only one block on this node, so it's necessary to remove the node

            if (!(node_aux->left) || !(node_aux->right)) {  //One or no child

                node_t* temp = node_aux->left ? node_aux->left : node_aux->right;

                if (!temp) { //No child case, so this is a leaf!

                    free_data(node_aux->data);
                    free(node_aux);

                    return temp;

                } else {  //One child

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
                node_aux->min_x = temp->min_x;
                node_aux->max_x = temp->max_x;
                node_aux->max_w = temp->max_w;
                node_aux->original_x = temp->original_x;

                node_aux->right = delete_node(tree_aux, node_aux->right, temp->data, compare_nodes, free_data);
                
            }
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

void* get_root(void* initial_tree){
    return ((tree_t*)initial_tree)->root;
}

void set_root(void* initialTree, void* new_root){
    tree_t* aux = initialTree;
    aux->root = new_root;
}

int compare_x(void* node, void* element) {

	//Node is going to be a node from the tree
    //Element is going to be a block from .geo file

	node_t* aux1 = node; 

	if(get_x(element) > aux1->original_x) return 1; //Go to right

	else if(get_x(element) < aux1->original_x) return -1; //Go to left

	else return 0;

}

double get_min_x(void* node){
    node_t* aux = node;
    return aux->min_x;
}

double get_max_x(void* node){
    node_t* aux = node;
    return aux->max_x;
}

double find_max_w(void* sequence){
    
    double biggest_w = 0;
    
    for(void* aux = get_head(sequence); aux; aux = get_next(aux)){

        if(get_w(get_list_element(aux)) > biggest_w) {
            
            biggest_w = get_w(get_list_element(aux));

        }

    }

    return biggest_w;
}

void printing_tree(void* initial_node, int space) {
    node_t* aux = initial_node;

    if (!aux) return;

    space += 10;

    printing_tree(aux->right, space);
    puts(" ");

    for (int i = 10; i < space; i++) printf(" ");

    printf("[%.2lf][%.2lf]\n", aux->min_x, aux->max_x);

    printing_tree(aux->left, space);
}

void recursive_print_tree(void* initial_tree) {
    tree_t* tree_to_print = initial_tree;
    printing_tree(tree_to_print->root, 0);
}