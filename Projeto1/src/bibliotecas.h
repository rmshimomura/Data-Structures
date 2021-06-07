#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef BIBLIOTECAS_H_INCLUDED
#define BIBLIOTECAS_H_INCLUDED

typedef void* lista; //Acessar o endereco da lista atraves de um ponteiro para void, fora do .c que existe a struct correspondente
typedef void* celula; //Acessar o endereco de um no da lista atraves de um ponteiro para void, fora do .c que existe a struct correspondente
typedef void* item; //Acessar o endereco o com todas as informacoes atraves de um ponteiro para void, fora do .c que existe a struct correspondente
typedef void* info; //Acessar as informacoes individualmente atraves de um ponteiro para void, fora do .c que existe a struct correspondente
typedef void* path; //Acessar os paths que foram passados no get arguments atraves de um ponteiro para void, fora do .c que existe a struct correspondente
typedef void* flag; //Acessar as flags que foram passados no get arguments atraves de um ponteiro para void, fora do .c que existe a struct correspondente

#endif