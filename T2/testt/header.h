#include <stdio.h>
#include <stdlib.h>


int (*compare2Numbers)(void* elemento1, void* elemento2);
void printAlgumacoisa(int (*compare2Numbers)(void* elemento1, void* elemento2));
void* createPonto();
int max(void* elemento1, void* elemento2);
void setX(void* ponto, int x);
int getX(void* ponto);
