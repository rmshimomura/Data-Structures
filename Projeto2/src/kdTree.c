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
    double biggestX;
    double biggestY;
    node_kd *root;


} tree_kd;

tree KDcreateTree() {

    tree_kd *aux = calloc(1, sizeof(tree_kd));
    aux->size = 0;
    aux->root = NULL;
    aux->biggestX = 0;
    aux->biggestY = 0;
    return aux;

}

node KDgetRootNode(tree current) {

    tree_kd *aux = current;
    return aux->root;

}

node KDgetLeftNode(node current) {

    node_kd *aux = current;
    return aux->left;

}

node KDgetRightNode(node current) {

    node_kd *aux = current;
    return aux->right;

}

bool KDgetState(node current) {

    node_kd *aux = current;
    return aux->activate;

}

void KDsetState(node current, bool state) {

    node_kd *aux = current;
    aux->activate = state;

}

node KDcreateNewNode(item element) {

    node_kd *aux = calloc(1, sizeof(node_kd));
    aux->data = element;
    aux->left = aux->right = NULL;
    aux->activate = true;
    return aux;

}

node KDsearchID(node current, char *id) {

    node_kd *aux = current;

    if (aux) {

        if (!strcmp(getRectangleId(aux->data), id)) {

            return aux;
        
        }

        node_kd *left = KDsearchID(aux->left, id);

        if (left) {

            return left;
        
        }

        node_kd *right = KDsearchID(aux->right, id);

        if (right) {

            return right;
        
        }
    
    }

}

void KDsetRootNode(tree current, node modifyRoot) {

    tree_kd *aux = current;
    aux->root = modifyRoot;

}

node KDinsertRect(tree initialTree, node initialNode, node generator, item element, int level) {

    tree_kd *tree_aux = initialTree;
    node_kd *node_aux = initialNode;
    node_kd *father_node = generator;

    if (level % 2 == 0) {
        // Compare left and right (X axis)

        if (!node_aux) {

            node_aux = KDcreateNewNode(element);
            tree_aux->size++;
            
        
        } else if (getRectangleX(element) >= getRectangleX(node_aux->data)) {

            node_aux->right = KDinsertRect(initialTree, node_aux->right, node_aux, element, level + 1);

        
        } else if (getRectangleX(element) < getRectangleX(node_aux->data)) {

            node_aux->left = KDinsertRect(initialTree, node_aux->left, node_aux, element, level + 1);
        
        }

    
    } else if (level % 2 == 1) {
        
        // Compare up and down (Y axis)

        if (!node_aux) {

            node_aux = KDcreateNewNode(element);
            tree_aux->size++;
            

        
        } else if (getRectangleY(element) >= getRectangleY(node_aux->data)) {

            node_aux->right = KDinsertRect(initialTree, node_aux->right, node_aux, element, level + 1);

        
        } else if (getRectangleY(element) < getRectangleY(node_aux->data)) {

            node_aux->left = KDinsertRect(initialTree, node_aux->left, node_aux, element, level + 1);
        
        }
    
    }
    return node_aux;

}

node KDinsertCirc(tree initialTree, node initialNode, node generator, item element, int level) {

    tree_kd *tree_aux = initialTree;
    node_kd *node_aux = initialNode;
    node_kd *father_node = generator;

    if (level % 2 == 0) {
          // Compare left and right (X axis) 

        if (!node_aux) {

            node_aux = KDcreateNewNode(element);
            tree_aux->size++;
            
        
        } else if (getCircleX(element) >= getCircleX(node_aux->data)) {

            node_aux->right = KDinsertCirc(initialTree, node_aux->right, node_aux, element, level + 1);

        
        } else if (getCircleX(element) < getCircleX(node_aux->data)) {

            node_aux->left = KDinsertCirc(initialTree, node_aux->left, node_aux, element, level + 1);
        
        }

    
    } else if (level % 2 == 1) {
          // Compare up and down (Y axis)

        if (!node_aux) {

            node_aux = KDcreateNewNode(element);
            tree_aux->size++;
            

        
        } else if (getCircleY(element) >= getCircleY(node_aux->data)) {

            node_aux->right = KDinsertCirc(initialTree, node_aux->right, node_aux, element, level + 1);

        
        } else if (getCircleY(element) < getCircleY(node_aux->data)) {

            node_aux->left = KDinsertCirc(initialTree, node_aux->left, node_aux, element, level + 1);
        
        }
    
    }
    return node_aux;

}

void rectangleinorder(node initialNode) {

    node_kd *aux = initialNode;

    if (aux != NULL) {

        rectangleinorder(aux->left);
        if (getRectangleX(aux->data)) {

            printf("[x = %.2lf] ", getRectangleX(aux->data));
        
        }
        if (getRectangleY(aux->data)) {

            printf("[y = %.2lf] ", getRectangleY(aux->data));
        
        }
        if (getRectangleWidth(aux->data)) {

            printf("[width = %.2lf] ", getRectangleWidth(aux->data));
        
        }
        if (getRectangleHeight(aux->data)) {

            printf("[height = %.2lf] ", getRectangleHeight(aux->data));
        
        }
        if (getRectangleId(aux->data)) {

            printf("[id = %s] ", getRectangleId(aux->data));
        
        }
        if (getRectangleFill(aux->data)) {

            printf("[fill = %s] ", getRectangleFill(aux->data));
        
        }
        if (getRectangleStroke(aux->data)) {

            printf("[stroke = %s] ", getRectangleStroke(aux->data));
        
        }
        if (getRectangleCenterX(aux->data)) {

            printf("[CenterX = %.2lf] ", getRectangleCenterX(aux->data));
        
        }
        if (getRectangleCenterY(aux->data)) {

            printf("[CenterY = %.2lf] ", getRectangleCenterY(aux->data));
        
        }
        printf("[Address = %p] ", aux);
        printf("\n");
        rectangleinorder(aux->right);
    
    }

}

void circleinorder(node initialNode) {

    node_kd *aux = initialNode;

    if (aux != NULL) {

        circleinorder(aux->left);
        if (getCircleX(aux->data)) {

            printf("[x = %.2lf] ", getCircleX(aux->data));
        
        }
        if (getCircleY(aux->data)) {

            printf("[y = %.2lf] ", getCircleY(aux->data));
        
        }
        if (getCircleOriginalX(aux->data)) {

            printf("[originalX = %.2lf] ", getCircleOriginalX(aux->data));
        
        }
        if (getCircleOriginalY(aux->data)) {

            printf("[originalY = %.2lf] ", getCircleOriginalY(aux->data));
        
        }
        if (getCircleRadius(aux->data)) {

            printf("[radius = %.2lf] ", getCircleRadius(aux->data));
        
        }
        if (getCircleId(aux->data)) {

            printf("[id = %s] ", getCircleId(aux->data));
        
        }
        if (getCircleFill(aux->data)) {

            printf("[fill = %s] ", getCircleFill(aux->data));
        
        }
        if (getCircleStroke(aux->data)) {

            printf("[stroke = %s] ", getCircleStroke(aux->data));
        
        }
        if (getRunTo(aux->data)) {

            printf("[Run to = %s] ", getRectangleId(KDgetData(getRunTo(aux->data))));
        
        }
        printf("\n");
        circleinorder(aux->right);
    
    }

}

void KDdestroyRectTree(tree initialTree, node initialRoot) {

    tree_kd *auxTree = initialTree;
    node_kd *auxRoot = initialRoot;

    if (auxRoot != NULL) {

        KDdestroyRectTree(auxTree, auxRoot->left);
        
        if (auxRoot->data != NULL) {

            if (getVectorOfPeopleStarted(auxRoot->data)) {

                freeVectorOfPeople(auxRoot->data);
            
            }
        
        }
        
        free(auxRoot->data);
        KDdestroyRectTree(auxTree, auxRoot->right);
        free(auxRoot);
    
    }

}

void KDdestroyCircTree(tree initialTree, node initialRoot) {

    tree_kd *auxTree = initialTree;
    node_kd *auxRoot = initialRoot;

    if (auxRoot != NULL) {

        KDdestroyCircTree(auxTree, auxRoot->left);
        free(auxRoot->data);
        KDdestroyCircTree(auxTree, auxRoot->right);
        free(auxRoot);
    
    }

}

int KDgetSize(tree initialTree) {

    tree_kd *aux = initialTree;
    return aux->size;

}

void KDsetSize(tree initialTree, int size) {

    tree_kd *aux = initialTree;
    aux->size = size;

}

void setType(tree initialTree, char type) {

    tree_kd *aux = initialTree;
    aux->type = type;

}

char getType(tree initialTree) {

    tree_kd *aux = initialTree;
    return aux->type;

}

void *KDgetData(node current) {

    node_kd *aux = current;
    return aux->data;

}

void setBiggestX(tree initialTree, double value) {

    tree_kd *aux = initialTree;
    aux->biggestX = value;

}

void setBiggestY(tree initialTree, double value) {

    tree_kd *aux = initialTree;
    aux->biggestY = value;

}

double getBiggestX(tree initialTree) {

    tree_kd *aux = initialTree;
    return aux->biggestX;

}

double getBiggestY(tree initialTree) {

    tree_kd *aux = initialTree;
    return aux->biggestY;

}