#include "dynamicList.h"

#include "bibliotecas.h"
#include "normalTree.h"
#include "segments.h"

/*===============================*/

/*Double linked list*/

typedef struct data {
    struct data* next;
    struct data* prev;
    void* element;
    double radiation;
    double xMeteor, yMeteor;
} data_t;

typedef struct list {
    data_t* head;
    data_t* end;
    int size;

} list_t;

/*===============================*/

void* createList() {
    list_t* newList = malloc(sizeof(list_t));
    newList->head = NULL;
    newList->end = NULL;
    newList->size = 0;
    return newList;
}

void* insert(void* sequence, void* elemento) {
    list_t* listaAux = sequence;
    data_t* pontAux = calloc(1, sizeof(data_t));
    pontAux->element = elemento;
    pontAux->radiation = 0;
    pontAux->xMeteor = 0;
    pontAux->yMeteor = 0;
    if (listaAux->size == 0) {
        pontAux->next = NULL;
        pontAux->prev = NULL;
        listaAux->head = pontAux;
        listaAux->end = pontAux;

    } else {
        pontAux->next = NULL;
        listaAux->end->next = pontAux;
        pontAux->prev = listaAux->end;
        listaAux->end = pontAux;
    }
    listaAux->size++;

    return pontAux;
}

int getSize(void* sequence) {
    list_t* listAux = sequence;
    return listAux->size;
}

double getDataRadiation(void* node) {
    data_t* dataAux = node;
    return dataAux->radiation;
}

void setDataRadiation(void* node, double radiation) {
    data_t* dataAux = node;
    dataAux->radiation = radiation;
}

double getDataxMeteor(void* node) {
    data_t* dataAux = node;
    return dataAux->xMeteor;
}

void setDataxMeteor(void* node, double xMeteor) {
    data_t* dataAux = node;
    dataAux->xMeteor = xMeteor;
}

double getDatayMeteor(void* node) {
    data_t* dataAux = node;
    return dataAux->yMeteor;
}

void setDatayMeteor(void* node, double yMeteor) {
    data_t* dataAux = node;
    dataAux->yMeteor = yMeteor;
}

void* getHead(void* sequence) {
    list_t* listAux = sequence;
    return listAux->head;
}

void* getNext(void* sequence, void* current) {
    list_t* listAux = sequence;
    data_t* aux = current;
    if (aux == NULL) {
        return NULL;
    } else {
        return aux->next;
    }
}

void* getPrevious(void* sequence, void* current) {
    list_t* listAux = sequence;
    data_t* aux = current;
    if (aux->prev) {
        return aux->prev;
    } else {
        return NULL;
    }
}

void* getItem(void* sequence, void* current) {
    data_t* aux = current;
    return aux->element;
}

void freeList(void* sequence) {
    list_t* listAux = sequence;
    if (listAux->size == 0) {
        free(sequence);
        return;
    }
    data_t* auxCelula = listAux->head;
    data_t* auxElemento = listAux->head->element;
    while (listAux->head != NULL) {
        auxCelula = listAux->head;
        auxElemento = listAux->head->element;
        listAux->head = listAux->head->next;

        free(auxElemento);
        free(auxCelula);
    }
    free(sequence);
}

void freeListOfSegments(void* sequence) {
    list_t* listAux = sequence;
    if (listAux->size == 0) {
        free(sequence);
        return;
    }
    data_t* auxCelula = listAux->head;
    data_t* auxElemento = listAux->head->element;
    while (listAux->head != NULL) {
        auxCelula = listAux->head;
        auxElemento = listAux->head->element;
        listAux->head = listAux->head->next;

        if (auxElemento) {
            freePointsInfo(auxElemento);
            free(auxElemento);
        }

        free(auxCelula);
    }

    free(sequence);
}

void* atPos(void* sequence, int index) {
    list_t* listAux = sequence;
    data_t* aux = listAux->head;
    for (int i = 0; i < index; i++) {
        aux = getNext(sequence, aux);
    }
    return aux;
}

void removeNode(void* sequence, void* current) {
    list_t* listAux = sequence;
    data_t* aux1;
    data_t* aux2;
    void* data_tdoAux1;
    void* data_tdoAux2;
    data_t* posToRemove = listAux->head;
    int pos = 0;
    while (posToRemove != current) {
        posToRemove = posToRemove->next;
        pos++;
        if (pos > listAux->size) {
            puts("Nao encontrado.");
            return;
        }
    }
    if (pos < 0) {
        puts("RIP!");
        return;
    } else if (pos > listAux->size) {
        puts("pos maior do que a lista!");
        return;
    } else if (pos == listAux->size - 1 && listAux->size > 1) {  //Se for o ultimo da lista
        aux1 = atPos(listAux, pos - 1);
        aux2 = atPos(listAux, pos);
        data_tdoAux2 = getItem(sequence, current);

        // free(data_tdoAux2);
        destorySegment(data_tdoAux2);
        free(aux2);
        aux1->next = NULL;
        listAux->end = aux1;
        listAux->size--;
    } else if (pos == 0 && listAux->size > 1) {  //Se for remover o primeiro, mas ha mais de 1 elemento na lista
        aux1 = atPos(listAux, 0);
        data_tdoAux1 = getItem(sequence, getHead(sequence));
        listAux->head = listAux->head->next;
        // free(data_tdoAux1);
        destorySegment(data_tdoAux1);
        free(aux1);
        listAux->size--;
    } else if (pos == 0 && listAux->size == 1) {  //Se for o UNICO na lista
        aux1 = atPos(listAux, 0);
        data_tdoAux1 = getItem(sequence, getHead(sequence));
        listAux->head = NULL;
        listAux->end = NULL;
        // free(data_tdoAux1);
        destorySegment(data_tdoAux1);
        free(aux1);
        listAux->size--;
    } else {
        aux1 = atPos(listAux, pos - 1);
        aux2 = atPos(listAux, pos);
        data_tdoAux2 = getItem(sequence, current);
        aux1->next = aux2->next;
        aux2->next->prev = aux1;
        // free(data_tdoAux2);
        destorySegment(data_tdoAux2);
        free(aux2);
        listAux->size--;
    }
}

void freeListOfTreesShadows(void* sequence) {
    list_t* listAux = sequence;
    if (listAux->size == 0) {
        free(sequence);
        return;
    }

    data_t* auxNode = listAux->head;
    data_t* auxElement = listAux->head->element;
    while (listAux->head != NULL) {
        auxNode = listAux->head;
        auxElement = listAux->head->element;
        listAux->head = listAux->head->next;

        if (auxElement) {
            freeNTTree(auxElement, NTgetRootNode(auxElement));
            // freePointsInfo(auxElement);
            free(auxElement);
        }

        free(auxNode);
    }

    free(sequence);
}