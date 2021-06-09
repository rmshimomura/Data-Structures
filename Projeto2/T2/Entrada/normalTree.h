#include "bibliotecas.h"

#ifndef NORMAL_TREE_H 
#define NORMAL_TREE_H

    tree NTcreateTree();
    node NTcreateNewNode(item element);
    node NTgetRootNode(tree current);
    node NTgetLeftNode(node current);
    node NTgetRightNode(node current);
    int NTgetSize(tree current);
    void freeNTTree(tree initialTree, node initialRoot);
    void* NTgetData(node current);
    node NTinsertShadow(tree initialTree, node initialNode, node generator, item element);
    void NTsetRootNode(tree initialTree, node root);
    void* NTdeleteNode(void* root, void* toRemove, int(*compare_function)(void*, void*));
    void* NTinsertSegment(tree activeSegmentsTree, node initialNode, void* active_segment, int(*compare_function)(void*, void*));

#endif