#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PI 3.14159265
#ifndef BIBLIOTECAS_H
#define BIBLIOTECAS_H

typedef void* tree;  //Acessar o endereco da lista atraves de um ponteiro para void, fora do .c que existe a struct correspondente
typedef void* node;  //Acessar o endereco de um no da lista atraves de um ponteiro para void, fora do .c que existe a struct correspondente
typedef void* item;  //Acessar o endereco o com todas as informacoes atraves de um ponteiro para void, fora do .c que existe a struct correspondente
typedef void* data;  //Acessar as informacoes individualmente atraves de um ponteiro para void, fora do .c que existe a struct correspondente
typedef void* path;  //Acessar os paths que foram passados no get arguments atraves de um ponteiro para void, fora do .c que existe a struct correspondente
typedef void* segment;
typedef void* dynamicList;

#endif