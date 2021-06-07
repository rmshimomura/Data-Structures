#include "bibliotecas.h"

#ifndef KD_TREE_H
#define KD_TREE_H
tree KDcreateTree();
node KDgetRootNode(tree current);
node KDcreateNewNode(item element);
node KDinsertRect(tree initialTree, node initialNode, node generator, item element, int level);
node KDinsertCirc(tree initialTree, node initialNode, node generator, item element, int level);
void inorder(node initialRoot);
void KDsetRootNode(node primeRoot, node modifyRoot);
node KDgetLeftNode(node current);
node KDgetRightNode(node current);
void KDdestroyRectTree(tree initialTree, node initialRoot);
void KDdestroyCircTree(tree initialTree, node initialRoot);
bool KDgetState(node current);
int KDgetSize(tree initialTree);
void setType(tree initialTree, char type);
char getType(tree initialTree);
int KDgetSize(tree initialTree);
void* KDgetData(node current);
void KDsetState(node current, bool state);
node KDsearchID(node current, char *id);
void KDsetSize(tree initialTree, int size);
void rectangleinorder(node initialNode);
void circleinorder(node initialNode);
void KDsetRootNode(tree current, node modifyRoot);
void setBiggestX(tree initialTree, double value);
void setBiggestY(tree initialTree, double value);
double getBiggestX(tree initialTree);
double getBiggestY(tree initialTree);

#endif