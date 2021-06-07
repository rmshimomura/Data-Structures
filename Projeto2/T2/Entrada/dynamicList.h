#include "bibliotecas.h"
#ifndef DYNAMICLIST_H_INCLUDED
#define DYNAMICLIST_H_INCLUDED

void* createList();
int getSize(void* sequence);
void* insert(void* sequence, void* elemento);
void removeNode(void* sequence, void* current);
void* getItem(void* sequence, void* current);
void* getHead(void* sequence);
void* getNext(void* sequence, void* current);
void* getLast(void* sequence);
void* getPrevious(void* sequence, void* current);
void freeList(void* sequence);
void* atPos(void* sequence, int index);
void freeListOfSegments(void* sequence);
void freeListOfTreesShadows(void* sequence);
double getDataRadiation(void* node);
void setDataRadiation(void* node, double radiation);

#endif