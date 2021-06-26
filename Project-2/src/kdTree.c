#include "kdTree.h"

#include "circle.h"
#include "rectangle.h"

typedef struct node_kd {
    struct node_kd *left;
    struct node_kd *right;

    void *data;
    bool activate;

} node_kd;

typedef struct tree_kd {
    int size;
    char type;
    double biggest_x;
    double biggest_y;
    node_kd *root;

} tree_kd;

tree KD_create_tree() {
    tree_kd *aux = calloc(1, sizeof(tree_kd));
    aux->size = 0;
    aux->root = NULL;
    aux->biggest_x = 0;
    aux->biggest_y = 0;
    return aux;
}

node KD_get_root_node(tree current) {
    tree_kd *aux = current;
    return aux->root;
}

node KD_get_left_node(node current) {
    node_kd *aux = current;
    return aux->left;
}

node KD_get_right_node(node current) {
    node_kd *aux = current;
    return aux->right;
}

bool KD_get_state(node current) {
    node_kd *aux = current;
    return aux->activate;
}

void KD_set_state(node current, bool state) {
    node_kd *aux = current;
    aux->activate = state;
}

node KD_create_new_node(item element) {
    node_kd *aux = calloc(1, sizeof(node_kd));
    aux->data = element;
    aux->left = aux->right = NULL;
    aux->activate = true;
    return aux;
}

node KD_search_ID(node current, char *id) {
    node_kd *aux = current;

    if (aux) {
        if (!strcmp(get_rectangle_id(aux->data), id)) {
            return aux;
        }

        node_kd *left = KD_search_ID(aux->left, id);

        if (left) {
            return left;
        }

        node_kd *right = KD_search_ID(aux->right, id);

        if (right) {
            return right;
        }
    }
}

void KD_set_root_node(tree current, node modifyRoot) {
    tree_kd *aux = current;
    aux->root = modifyRoot;
}

node KD_insert_rect(tree initialTree, node initialNode, node generator, item element, int level) {
    tree_kd *tree_aux = initialTree;
    node_kd *node_aux = initialNode;
    node_kd *father_node = generator;

    if (level % 2 == 0) {
        // Compare left and right (X axis)

        if (!node_aux) {
            node_aux = KD_create_new_node(element);
            tree_aux->size++;

        } else if (get_rectangle_x(element) >= get_rectangle_x(node_aux->data)) {
            node_aux->right = KD_insert_rect(initialTree, node_aux->right, node_aux, element, level + 1);

        } else if (get_rectangle_x(element) < get_rectangle_x(node_aux->data)) {
            node_aux->left = KD_insert_rect(initialTree, node_aux->left, node_aux, element, level + 1);
        }

    } else if (level % 2 == 1) {
        // Compare up and down (Y axis)

        if (!node_aux) {
            node_aux = KD_create_new_node(element);
            tree_aux->size++;

        } else if (get_rectangle_y(element) >= get_rectangle_y(node_aux->data)) {
            node_aux->right = KD_insert_rect(initialTree, node_aux->right, node_aux, element, level + 1);

        } else if (get_rectangle_y(element) < get_rectangle_y(node_aux->data)) {
            node_aux->left = KD_insert_rect(initialTree, node_aux->left, node_aux, element, level + 1);
        }
    }
    return node_aux;
}

node KD_insert_circ(tree initialTree, node initialNode, node generator, item element, int level) {
    tree_kd *tree_aux = initialTree;
    node_kd *node_aux = initialNode;
    node_kd *father_node = generator;

    if (level % 2 == 0) {
        // Compare left and right (X axis)

        if (!node_aux) {
            node_aux = KD_create_new_node(element);
            tree_aux->size++;

        } else if (get_circle_x(element) >= get_circle_x(node_aux->data)) {
            node_aux->right = KD_insert_circ(initialTree, node_aux->right, node_aux, element, level + 1);

        } else if (get_circle_x(element) < get_circle_x(node_aux->data)) {
            node_aux->left = KD_insert_circ(initialTree, node_aux->left, node_aux, element, level + 1);
        }

    } else if (level % 2 == 1) {
        // Compare up and down (Y axis)

        if (!node_aux) {
            node_aux = KD_create_new_node(element);
            tree_aux->size++;

        } else if (get_circle_y(element) >= get_circle_y(node_aux->data)) {
            node_aux->right = KD_insert_circ(initialTree, node_aux->right, node_aux, element, level + 1);

        } else if (get_circle_y(element) < get_circle_y(node_aux->data)) {
            node_aux->left = KD_insert_circ(initialTree, node_aux->left, node_aux, element, level + 1);
        }
    }
    return node_aux;
}

void rectangle_in_order(node initialNode) {
    node_kd *aux = initialNode;

    if (aux != NULL) {
        rectangle_in_order(aux->left);
        if (get_rectangle_x(aux->data)) {
            printf("[x = %.2lf] ", get_rectangle_x(aux->data));
        }
        if (get_rectangle_y(aux->data)) {
            printf("[y = %.2lf] ", get_rectangle_y(aux->data));
        }
        if (get_rectangle_width(aux->data)) {
            printf("[width = %.2lf] ", get_rectangle_width(aux->data));
        }
        if (get_rectangle_height(aux->data)) {
            printf("[height = %.2lf] ", get_rectangle_height(aux->data));
        }
        if (get_rectangle_id(aux->data)) {
            printf("[id = %s] ", get_rectangle_id(aux->data));
        }
        if (get_rectangle_fill(aux->data)) {
            printf("[fill = %s] ", get_rectangle_fill(aux->data));
        }
        if (get_rectangle_stroke(aux->data)) {
            printf("[stroke = %s] ", get_rectangle_stroke(aux->data));
        }
        if (get_rectangle_center_x(aux->data)) {
            printf("[CenterX = %.2lf] ", get_rectangle_center_x(aux->data));
        }
        if (get_rectangle_center_y(aux->data)) {
            printf("[CenterY = %.2lf] ", get_rectangle_center_y(aux->data));
        }
        printf("[Address = %p] ", aux);
        printf("\n");
        rectangle_in_order(aux->right);
    }
}

void circle_in_order(node initialNode) {
    node_kd *aux = initialNode;

    if (aux != NULL) {
        circle_in_order(aux->left);
        if (get_circle_x(aux->data)) {
            printf("[x = %.2lf] ", get_circle_x(aux->data));
        }
        if (get_circle_y(aux->data)) {
            printf("[y = %.2lf] ", get_circle_y(aux->data));
        }
        if (get_circle_original_x(aux->data)) {
            printf("[originalX = %.2lf] ", get_circle_original_x(aux->data));
        }
        if (get_circle_original_y(aux->data)) {
            printf("[originalY = %.2lf] ", get_circle_original_y(aux->data));
        }
        if (get_circle_radius(aux->data)) {
            printf("[radius = %.2lf] ", get_circle_radius(aux->data));
        }
        if (get_circle_id(aux->data)) {
            printf("[id = %s] ", get_circle_id(aux->data));
        }
        if (get_circle_fill(aux->data)) {
            printf("[fill = %s] ", get_circle_fill(aux->data));
        }
        if (get_circle_stroke(aux->data)) {
            printf("[stroke = %s] ", get_circle_stroke(aux->data));
        }
        if (get_run_to(aux->data)) {
            printf("[Run to = %s] ", get_rectangle_id(KD_get_data(get_run_to(aux->data))));
        }
        printf("\n");
        circle_in_order(aux->right);
    }
}

void KD_destroy_rect_tree(tree initialTree, node initialRoot) {
    tree_kd *auxTree = initialTree;
    node_kd *auxRoot = initialRoot;

    if (auxRoot != NULL) {
        KD_destroy_rect_tree(auxTree, auxRoot->left);

        if (auxRoot->data != NULL) {
            if (get_vector_of_people_started(auxRoot->data)) {
                free_vector_of_people(auxRoot->data);
            }
        }

        free(auxRoot->data);
        KD_destroy_rect_tree(auxTree, auxRoot->right);
        free(auxRoot);
    }
}

void KD_destroy_circ_tree(tree initialTree, node initialRoot) {
    tree_kd *auxTree = initialTree;
    node_kd *auxRoot = initialRoot;

    if (auxRoot != NULL) {
        KD_destroy_circ_tree(auxTree, auxRoot->left);
        free(auxRoot->data);
        KD_destroy_circ_tree(auxTree, auxRoot->right);
        free(auxRoot);
    }
}

int KD_get_size(tree initialTree) {
    tree_kd *aux = initialTree;
    return aux->size;
}

void KD_set_size(tree initialTree, int size) {
    tree_kd *aux = initialTree;
    aux->size = size;
}

void set_type(tree initialTree, char type) {
    tree_kd *aux = initialTree;
    aux->type = type;
}

char get_type(tree initialTree) {
    tree_kd *aux = initialTree;
    return aux->type;
}

void *KD_get_data(node current) {
    node_kd *aux = current;
    return aux->data;
}

void set_biggest_x(tree initialTree, double value) {
    tree_kd *aux = initialTree;
    aux->biggest_x = value;
}

void set_biggest_y(tree initialTree, double value) {
    tree_kd *aux = initialTree;
    aux->biggest_y = value;
}

double get_biggest_x(tree initialTree) {
    tree_kd *aux = initialTree;
    return aux->biggest_x;
}

double get_biggest_y(tree initialTree) {
    tree_kd *aux = initialTree;
    return aux->biggest_y;
}