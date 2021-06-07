#include "bibliotecas.h"
#include "lista.h"

/*===============================*/

/*LISTA DUPLAMENTE ENCADEADA*/

typedef struct dados {
    struct dados* next;
    struct dados* prev;
    void* elemento;
} dados;

typedef struct list {
    dados* head;
    dados* end;
    int size;
    long int visitas;
    long int originalSize;
} list;

/*===============================*/

lista createList(int tamanho) {
    list* newList = malloc(sizeof(list));
    newList->head = NULL;
    newList->end = NULL;
    newList->size = 0;
    newList->visitas = 0;
    return newList;
}

long int getVisitas(lista sequence){
    list* listAux = sequence;
    return listAux->visitas;
}

void raiseVisitas(lista sequence){
    list* listAux = sequence;
    listAux->visitas++;
}

long int getOriginalSize(lista sequence){
    list* listAux = sequence;
    return listAux->originalSize;
}

celula insert(lista sequence, item elemento){
    list* listaAux = sequence;
    dados* pontAux = malloc(sizeof(dados));
    pontAux->elemento = elemento;
    if(listaAux->size == 0){
        pontAux->next = NULL;
        pontAux->prev = NULL;
        listaAux->head = pontAux;
        listaAux->end = pontAux;
        
    }else{
        pontAux->next = NULL;
        listaAux->end->next = pontAux;
        pontAux->prev= listaAux->end;
        listaAux->end = pontAux;
    }
    listaAux->size++;
    listaAux->originalSize = listaAux->size;
    return elemento;
}

int getSize(lista sequence){
    list* listAux = sequence;
    return listAux->size;
}

celula getHead(lista sequence){
    list* listAux = sequence;
    return listAux->head;
}

celula getNext(lista sequence, celula current){
    list* listAux = sequence;
    dados* aux = current; 
    listAux->visitas++;
    if(aux == NULL){
        return NULL;
    }else{
        return aux->next;
    }

}

celula getPrevious(lista sequence, celula current){
    list* listAux = sequence;
    listAux->visitas++;
    dados* aux = current;
    if(aux->prev){
        return aux->prev;
    }else{
        return NULL;
    }
}

item getItem(lista sequence, celula current){
    dados* aux = current;
    return aux->elemento;
}

void freeList(lista sequence, int tamanho){
    list* listAux = sequence;
    if(listAux->size == 0){
        free(sequence);
        return;
    }
    dados* auxCelula = listAux->head;
    dados* auxElemento = listAux->head->elemento;
    while(listAux->head != NULL){
        auxCelula = listAux->head;
        auxElemento = listAux->head->elemento;
        listAux->head = listAux->head->next;
        free(auxElemento);
        free(auxCelula);
    }
    free(sequence);
}

celula atPos(lista sequence, int index){
    list* listAux = sequence;
    dados* aux = listAux->head;
    for(int i = 0; i < index; i++){
        aux = getNext(sequence, aux);
        listAux->visitas++;
    }
    return aux;
}

void removeNode(lista sequence, celula current){
    list* listAux = sequence;
    dados* aux1;
    dados* aux2;
    void* dadosdoAux1;
    void* dadosdoAux2;
    dados* posToRemove = listAux->head;
    int pos = 0;
    while(posToRemove != current){
        posToRemove = posToRemove->next;
        pos++;
        if(pos > listAux->size){
            puts("Nao encontrado.");
            return;
        }
        listAux->visitas++;
    }
    if(pos < 0){
        puts("RIP!");
        return;
    }else if(pos > listAux->size){
        puts("pos maior do que a lista!");
        return;
    }else if(pos == listAux->size - 1 && listAux->size > 1){ //Se for o ultimo da lista
        aux1 = atPos(listAux, pos - 1);
        aux2 = atPos(listAux, pos);
        dadosdoAux2 = getItem(sequence, current);
        free(dadosdoAux2);
        free(aux2);
        aux1->next = NULL;
        listAux->end = aux1;
        listAux->size--;
    }else if(pos == 0 && listAux->size > 1){ //Se for remover o primeiro, mas ha mais de 1 elemento na lista
        aux1 = atPos(listAux, 0);
        dadosdoAux1 = getItem(sequence, getHead(sequence));
        listAux->head = listAux->head->next;
        free(dadosdoAux1);
        free(aux1);
        listAux->size--;
    }else if(pos == 0 && listAux->size == 1){ //Se for o UNICO na lista
        aux1 = atPos(listAux, 0);
        dadosdoAux1 = getItem(sequence, getHead(sequence));
        listAux->head = NULL;
        listAux->end = NULL;
        free(dadosdoAux1);
        free(aux1);
        listAux->size--;
    }else{
        aux1 = atPos(listAux, pos - 1);
        aux2 = atPos(listAux, pos);
        dadosdoAux2 = getItem(sequence, current);
        aux1->next = aux2->next;
        aux2->next->prev = aux1;
        free(dadosdoAux2);
        free(aux2);
        listAux->size--;
    }
}

celula insertBefore(lista sequence, celula current, item elemento){
    list* listAux = sequence;
    dados* aux1 = getPrevious(sequence, current);
    dados* aux2 = malloc(sizeof(dados));
    aux2->elemento = elemento;
    if(listAux->size == 0){ //Nao existir elementos na lista //Provavel de nao acontecer
        aux2->next = NULL;
        aux2->prev = NULL;
        listAux->head = aux2;
        listAux->end = aux2;
    }else if(aux1 == NULL && listAux->size > 0){ //Existem elementos na lista, mas eh para ser inserido no comeco
        listAux->head->prev = aux2;
        aux2->next = listAux->head;
        aux2->prev = NULL;
        listAux->head = aux2;
    }else{ //Meio da lista
        aux2->prev = aux1;
        aux2->next = aux1->next;
        aux1->next->prev = aux2;
        aux1->next = aux2;
    }
    listAux->size++;
    return aux2;
}

celula insertAfter(lista sequence, celula current, item elemento){
    list* listAux = sequence;
    dados* aux1 = getNext(sequence, current);
    dados* aux2 = aux1->prev;
    dados* aux3 = malloc(sizeof(dados));
    aux3->elemento = elemento;
    if(aux1 == NULL){ //Se for o ultimo 
        aux3->prev = aux2;
        aux3->next = NULL;
        aux2->next = aux3;
        listAux->end = aux3;
    }else{
        aux3->prev = aux2;
        aux3->next = aux1;
        aux2->next = aux3;
        aux1->prev = aux3;
    }
    listAux->size++;
    return aux2;
}

celula getLast(lista sequence){
    list* listAux = sequence;
    if(listAux->size == 0){
        return NULL;
    }else{
        return listAux->end;
    }
}