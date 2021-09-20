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

            main_node->min_x = get_x(get_list_element(get_head(main_node->data))); //If there's no left child get the x coordinate from the first position on the list

        }

        if(main_node->left || main_node->right){

            main_node->max_x = main_node->left->max_x > main_node->right->max_x ? main_node->left->max_x : main_node->right->max_x; //Check which one of its children has a greater max_x

        }else{
            
            main_node->max_x = get_list_max_x(main_node->data); //If there's no child, search on the list of blocks this node has

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

            main_node->min_x = get_x(get_list_element(get_head(main_node->data))); //If there's no left child get the x coordinate from the first position on the list

        }

        if(main_node->left || main_node->right){

            main_node->max_x = main_node->left->max_x > main_node->right->max_x ? main_node->left->max_x : main_node->right->max_x; //Check which one of its children has a greater max_x

        }else{
            
            main_node->max_x = get_list_max_x(main_node->data); //If there's no child, search on the list of blocks this node has

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

void* delete_node(void* initial_tree, void* initial_node, void* element, int (*compare_nodes)(void*, void*), void (*free_data)(void*)) {
    if (!initial_node || !initial_tree) return initial_node;
    //TODO need to fix min_x and max_x !!
    tree_t* tree_aux = initial_tree;
    node_t* node_aux = initial_node;

    if (compare_nodes(node_aux, element) == 1) {
        node_aux->right = delete_node(tree_aux, node_aux->right, element, compare_nodes, free_data);

    } else if (compare_nodes(node_aux, element) == -1) {
        node_aux->left = delete_node(tree_aux, node_aux->left, element, compare_nodes, free_data);

    } else {

        /*TESTING AREA, DANGEROUS BEHAVIOR :P */

        if(get_size(node_aux->data) > 1){

            int flag = 0; //Check if the node that is going to be removed is the node that gives the maximun value to the node

            if(get_x(element) + get_w(element) == node_aux->max_x){
                //TODO
            }

            remove_node(node_aux->data, element, free);
            //TODO update min and max

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

        /*END OF THE TESTING AREA*/

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

	if(get_x(element) > get_x(get_list_element(get_head(aux1->data)))) return 1; //Go to right

	else if(get_x(element) < get_x(get_list_element(get_head(aux1->data)))) return -1; //Go to left

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

double get_list_max_x(void* sequence){
    double biggest_x = 0;
    for(void* aux = get_head(sequence); aux; aux = get_next(aux)){

        if(get_x(get_list_element(aux)) + get_w(get_list_element(aux)) > biggest_x) {
            
            biggest_x = get_x(get_list_element(aux)) + get_w(get_list_element(aux));

        }

    }

    return biggest_x;
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