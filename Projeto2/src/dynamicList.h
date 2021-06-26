#include "bibliotecas.h"
#ifndef DYNAMICLIST_H_INCLUDED
#define DYNAMICLIST_H_INCLUDED

void* createList();
int getSize(void* sequence);
void* insert(void* sequence, void* element);
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
double getDataxMeteor(void* node);
void setDataxMeteor(void* node, double xMeteor);
double getDatayMeteor(void* node);
void setDatayMeteor(void* node, double yMeteor);


#endif