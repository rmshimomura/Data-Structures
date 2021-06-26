#ifndef QRY_H
#define QRY_H
#include "bibliotecas.h"
#include "lista.h"

//Usada nas funcoes 
int intersec(double x1, double y1, double p1Largura, double p1Altura, double x2, double y2, double p2Largura, double p2Altura);

//Usada nas funcoes 
int inside(double x1, double y1, double p1Largura, double p1Altura, double x2, double y2, double p2Largura, double p2Altura);

//Fucoes pedidas no pdf
void tp(lista sequence, FILE* results, flag checkers);
void tpr(double x, double y, double largura, double altura, lista sequence, FILE* results, flag checkers);
void dpi(double x, double y, lista sequence, FILE* results, flag checkers);
void dr(char* id, lista sequence, FILE* results, flag checkers);
void bbi(double x, double y, lista sequence, FILE* results, flag checkers);
void bbid(char* id, lista sequence, FILE* results, flag checkers);
void iid(char* id, int k, lista sequence, FILE* results, flag checkers);
void diid(char* id, int k, lista sequence, FILE* results, flag checkers);

#endif