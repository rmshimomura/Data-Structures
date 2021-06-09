#include "normalTree.h"

#include "dynamicList.h"
#include "polygon.h"
#include "segments.h"

typedef struct node_t {
    struct node_t* left;
    struct node_t* right;
    struct node_t* father;
    void* data;
    int height;
    int depth;
    bool activated;

} node_t;

typedef struct tree_t {
    int size;
    node_t* root;

} tree_t;

tree NTcreateTree() {
    tree_t* aux = calloc(1, sizeof(tree_t));
    aux->size = 0;
    aux->root = NULL;
    return aux;
}

node NTcreateNewNode(item element) {
    node_t* aux = calloc(1, sizeof(node_t));
    aux->data = element;
    aux->left = aux->right = NULL;
    aux->depth = aux->height = 0;
    aux->activated = false;
    return aux;
}

int NTgetSize(tree current) {
    tree_t* aux = current;
    return aux->size;
}

node NTgetRootNode(tree current) {
    tree_t* aux = current;
    return aux->root;
}

node NTgetLeftNode(node current) {
    node_t* aux = current;
    return aux->left;
}

node NTgetRightNode(node current) {
    node_t* aux = current;
    return aux->right;
}

bool NTgetState(node current) {
    node_t* aux = current;
    return aux->activated;
}

void NTsetState(node current, bool state) {
    node_t* aux = current;
    aux->activated = state;
}

node NTinsertShadow(tree initialTree, node initialNode, node generator, item element) {
    tree_t* treeAux = initialTree;
    node_t* nodeAux = initialNode;

    if (!nodeAux) {
        nodeAux = NTcreateNewNode(element);
        treeAux->size++;
        nodeAux->father = generator;

    } else if (getMinimumX(element) >= getMinimumX(nodeAux->data)) {
        nodeAux->right = NTinsertShadow(initialTree, nodeAux->right, nodeAux, element);

    } else if (getMinimumX(element) < getMinimumX(nodeAux->data)) {
        nodeAux->left = NTinsertShadow(initialTree, nodeAux->left, nodeAux, element);
    }

    return nodeAux;
}

void freeNTTree(tree initialTree, node initialRoot) {
    tree_t* auxTree = initialTree;
    node_t* auxRoot = initialRoot;
    if (initialRoot) {
        if (auxRoot->left)
            freeNTTree(auxTree, auxRoot->left);
        if (auxRoot->data != NULL) {
            freeShadowPolygonsArray(auxRoot->data);
        }
        free(auxRoot->data);
        if (auxRoot->right)
            freeNTTree(auxTree, auxRoot->right);
        free(auxRoot);
    }
}

void* NTgetData(node current) {
    node_t* aux = current;
    return aux->data;
}

void NTsetRootNode(tree initialTree, node root) {
    tree_t* treeAux = initialTree;
    treeAux->root = root;
}

node_t* minValueNode(node_t* node){
    node_t* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
}
/*
void* NTdeleteNode(void* root, void* toRemove, int(*compare_function)(void*, void*)){
    
    node_t* auxRoot = root; 
    node_t* auxToRemove = toRemove;
    
    if (root == NULL)
        return root;

    if (compare_function(auxRoot->data, auxToRemove->data) == 1)
        auxRoot->left = NTdeleteNode(auxRoot->left, auxToRemove, compare_function);

    else if (compare_function(auxRoot->data, auxToRemove->data) == -1)
        auxRoot->right = NTdeleteNode(auxRoot->right, auxToRemove, compare_function);

    else {
        // node with only one child or no child
        if (auxRoot->left == NULL) {
            node_t* temp = auxRoot->right;
            freePointsInfo(auxRoot->data);
            free(auxRoot->data);
            return temp;
        }
        else if (auxRoot->right == NULL) {
            node_t* temp = auxRoot->left;
            freePointsInfo(auxRoot->data);
            free(auxRoot->data);
            return temp;
        }
 
        // node with two children:
        // Get the inorder successor
        // (smallest in the right subtree)
        node_t* temp = minValueNode(auxRoot->right);
 
        // Copy the inorder
        // successor's content to this node
        auxRoot->data = temp->data;
 
        // Delete the inorder successor
        auxRoot->right = NTdeleteNode(auxRoot->right, auxToRemove, compare_function);
    }

    return auxRoot;

}
*/