#include "header.h"

typedef struct ponto{
    int x;
}ponto_t;

void* createPonto(){
    ponto_t *aux = calloc(1, sizeof(ponto_t));
    return aux;
}

void setX(void* ponto, int x){
    ponto_t *aux = ponto;
    aux->x = x;
}

int getX(void* ponto){
    ponto_t *aux = ponto;
    return aux->x;
}

int max(void* elemento1, void* elemento2){
    ponto_t *aux1 = elemento1;
    ponto_t *aux2 = elemento2;
    return aux1->x > aux2->x ? aux1->x : aux2->x;
}

void printAlgumacoisa(int (*compare2Numbers)(void* elemento1, void* elemento2)){
    void* a = createPonto();
    setX(a, 2);
    void* b = createPonto();
    setX(b, 5);
    printf("%d maior\n", compare2Numbers(a, b));
    free(a);
    free(b);
}