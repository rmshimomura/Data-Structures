#include "elemento.h"

typedef struct elemento{
    double x, y, largura, altura;
    char id[100], contorno[100], preenchimento[100];
    bool marcadoTP, marcadoTPR;
}elemento;

info createElemento(){
    elemento *aux = calloc(1, sizeof(elemento));
    return aux;
}

/*==============================================*/

double getX(celula current){
    elemento* aux = current;
    return aux->x;
}

void setX(celula current, double xValue){
    elemento* aux = current;
    aux->x = xValue;
}

/*==============================================*/

double getY(celula current){
    elemento* aux = current;
    return aux->y;
}

void setY(celula current, double yValue){
    elemento* aux = current;
    aux->y = yValue;
}

/*==============================================*/

double getLargura(celula current){
    elemento* aux = current;
    return aux->largura;
}

void setLargura(celula current, double larguraValue){
    elemento* aux = current;
    aux->largura = larguraValue;
}

/*==============================================*/

double getAltura(celula current){
    elemento* aux = current;
    return aux->altura;
}

void setAltura(celula current, double alturaValue){
    elemento* aux = current;
    aux->altura = alturaValue;
}

/*==============================================*/

char* getId(celula current){
    elemento* aux = current;
    return aux->id;
}

void setId(celula current, char* idValue){
    elemento* aux = current;
    strcpy(aux->id, idValue);
}

/*==============================================*/

char* getPreenchimento(celula current){
    elemento* aux = current;
    return aux->preenchimento;
}

void setPreenchimento(celula current, char* preenchimentoValue){
    elemento* aux = current;
    strcpy(aux->preenchimento, preenchimentoValue);
}

/*==============================================*/

char* getContorno(celula current){
    elemento* aux = current;
    return aux->contorno;
}

void setContorno(celula current, char* contornoValue){
    elemento* aux = current;
    strcpy(aux->contorno, contornoValue);
}

/*==============================================*/

bool getMarcadoTP(celula current){
    elemento* aux = current;
    return aux->marcadoTP;
}

void setMarcadoTP(celula current, bool marcadoTPValue){
    elemento* aux = current;
    aux->marcadoTP = marcadoTPValue;
}

/*==============================================*/

bool getMarcadoTPR(celula current){
    elemento* aux = current;
    return aux->marcadoTPR;
}

void setMarcadoTPR(celula current, bool marcadoTPRValue){
    elemento* aux = current;
    aux->marcadoTPR = marcadoTPRValue;
}