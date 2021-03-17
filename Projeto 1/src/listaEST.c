#include "bibliotecas.h"
#include "lista.h"

//--------------------------ESTATICA--------------------------//

typedef struct S_cell {
    void* data;
    int next;
    bool isFree;
} S_cell;

typedef struct S_list {
    S_cell* vetor;
    int head;
    int tail;
    int size;
    int allocedSize;
    long int originalSize;
    long int visitas;
} S_list;

lista createList(int tamanho){
    S_list *listAux = calloc(1, sizeof(S_list));
    listAux->head = -1;
    listAux->tail = -1;
    listAux->size = 0;
    listAux->vetor = calloc(tamanho, sizeof(S_cell));
    for(int i = 0; i < tamanho; i++){
        listAux->vetor[i].next = i+1;
        listAux->vetor[i].isFree = true;
    }
    listAux->allocedSize = tamanho;
    listAux->vetor[tamanho - 1].next = -1; //Setar o ultimo no para -1 que representa o NULL da dinamica
    return listAux;
}

long int getVisitas(lista sequence){
    S_list* aux = sequence;
    return aux->visitas;
}

void raiseVisitas(lista sequence){
    S_list* aux = sequence;
    aux->visitas++;
}

long int getOriginalSize(lista sequence){
    S_list* aux = sequence;
    return aux->originalSize;
}

celula insert(lista sequence, item elemento){
    
    S_list* listAux = sequence;
    item aux = elemento;

    for(int i = 0; i < listAux->allocedSize; i++){
        if(listAux->vetor[i].isFree && listAux->size == 0){
            listAux->head = i;
            listAux->tail = i;
            listAux->vetor[i].data = aux;
            listAux->vetor[i].isFree = false; 
            listAux->vetor[i].next = -1;
            listAux->size++;
            break;
        }else if(listAux->vetor[i].isFree){
            listAux->vetor[listAux->tail].next = i;
            listAux->tail = i;
            listAux->vetor[i].data = aux;
            listAux->vetor[i].isFree = false; 
            listAux->vetor[i].next = -1;
            listAux->size++;
            break;
        }
    }
    listAux->originalSize++;
}

int returnIndexByAddress(lista sequence, celula current){
    S_list *listaAux = sequence;
    for(int i = 0; i < listaAux->size; i++){
        if(&listaAux->vetor[i] == current) return i;
        listaAux->visitas++;
    }
    return -1;
}

int getSize(lista sequence){
    S_list *listAux = sequence;
    return listAux->size;
}

celula getHead(lista sequence){
    S_list *listAux = sequence;
    return &listAux->vetor[listAux->head];
}

celula getNext(lista sequence, celula current){
    S_list *listAux = sequence;
    S_cell *aux = current;
    listAux->visitas++;
    if(aux->next == -1){
        return NULL;
    }
    return &listAux->vetor[aux->next];
}

celula getPrevious(lista sequence, celula current){
    S_list* listAux = sequence;
    int pos = listAux->head;
    for(int i = 0; i < listAux->size; i++){
        if(&listAux->vetor[listAux->vetor[pos].next] == current){
            return &listAux->vetor[pos];
        }
        pos = listAux->vetor[pos].next;
        listAux->visitas++;
    }
    return NULL;
}

item getItem(lista sequence, celula current){
    S_cell* aux = current;
    return aux->data;
}

void freeList(lista sequence, int tamanho){
    S_list *listAux = sequence;
    S_cell *aux;
    item dataAux;
    for(int i = 0; i < listAux->originalSize; i++){
        dataAux = listAux->vetor[i].data;
        free(dataAux);
    }
    free(listAux->vetor);
    free(listAux);
}

celula atPos(lista sequence, int index){ 
    S_list* listAux = sequence;
    S_cell* aux = getHead(sequence);
    for(int i = 0; i < index; i++){
        aux = getNext(sequence, aux);
        listAux->visitas++;
    }
    return aux;
}

void removeNode(lista sequence, celula current){ 
    S_list* listAux = sequence;
    int posBefore, posAfter, pos;
    posBefore = returnIndexByAddress(sequence, getPrevious(sequence, current));
    pos = returnIndexByAddress(sequence, current);
    posAfter = returnIndexByAddress(sequence, getNext(sequence, current));
    if(posBefore == -1){ //primeiro elemento da lista
        listAux->head = listAux->vetor[listAux->head].next;
        listAux->size--;
        
    }else if(posAfter == -1){ //ultimo elemento da lista
        listAux->tail = posBefore;
        listAux->size--;
        
    }else{ //meio da lista
        listAux->vetor[posBefore].next = posAfter;
        listAux->size--;
    }
    
}

celula getLast(lista sequence){
    S_list* listAux = sequence;
    if(listAux->size == 0){
        return NULL;
    }else{
        return &listAux->vetor[listAux->tail];
    }
}

celula insertBefore(lista sequence, celula current, item elemento){
    S_list* listAux = sequence;
    S_cell* aux1 = getPrevious(sequence, current);
    if(listAux->vetor[returnIndexByAddress(sequence, aux1)].isFree){
        listAux->vetor[returnIndexByAddress(sequence, aux1)].data = elemento;
    }else{
        puts("nao ha espaco antes da celula !");
        return NULL;
    }
}

celula insertAfter(lista sequence, celula current, item elemento){
    S_list* listAux = sequence;
    S_cell* aux1 = getNext(sequence, current);
    if(listAux->vetor[returnIndexByAddress(sequence, aux1)].isFree){
        listAux->vetor[returnIndexByAddress(sequence, aux1)].data = elemento;
    }else{
        puts("nao ha espaco depois da celula !");
        return NULL;
    }
}