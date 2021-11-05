#include "dynamicList.h"

typedef struct node {

    struct node* next;
    struct node* prev;
    void* element;

} node;

typedef struct list {

    node* head;
    node* end;
    int size;

} list;

void* create_list() {

    list* newList = malloc(sizeof(list));
    newList->head = NULL;
    newList->end = NULL;
    newList->size = 0;
    return newList;

}

void insert_list(void* sequence, void* element) {

    list* list_aux = sequence;
    node* pontAux = calloc(1, sizeof(node));
    pontAux->element = element;

    if (list_aux->size == 0) {

        pontAux->next = NULL;
        pontAux->prev = NULL;
        list_aux->head = pontAux;
        list_aux->end = pontAux;

    } else {

        pontAux->next = NULL;
        list_aux->end->next = pontAux;
        pontAux->prev = list_aux->end;
        list_aux->end = pontAux;
    }

    list_aux->size++;

}

int get_size(void* sequence) {
    
    list* list_aux = sequence;
    return list_aux->size;

}

void* get_head(void* sequence) {

    list* list_aux = sequence;
    return list_aux->head;

}

void* get_next(void* current) {
    
    node* aux = current;

    if (aux) return aux->next;

    return NULL;
}

void* get_previous(void* current) {
    
    node* aux = current;

    if (aux->prev) return aux->prev;

    return NULL;
}

void* get_list_element(void* current) {

    node* aux = current;
    return aux->element;

}

void free_list(void* sequence, bool remove_elements, void (*free_node)(void*)) {
    
    if(!sequence) return;

    list* list_aux = sequence;

    
    if (list_aux->size == 0) {

        free(sequence);
        return;

    }

    node* auxNode = list_aux->head;
    node* auxElement = list_aux->head->element;

    while (list_aux->head != NULL) {

        auxNode = list_aux->head;
        auxElement = list_aux->head->element;
        list_aux->head = list_aux->head->next;

        if(remove_elements == true) free_node(auxElement);

        free(auxNode);
    }

    free(sequence);
}

void* at_pos(void* sequence, int index) {

    list* list_aux = sequence;
    node* aux = list_aux->head;

    for (int i = 0; i < index; i++) {
        aux = get_next(aux);
    }

    return aux;

}

void remove_node(void* sequence, void* node_to_remove, void (*free_node)(void*), bool remove_elements) {
    
    list* list_aux = sequence;
    node* aux1;
    node* aux2;
    
    node* posToRemove = list_aux->head;
    int pos = 0;

    while (posToRemove->element != node_to_remove) {

        posToRemove = posToRemove->next;
        pos++;

        if (pos > list_aux->size) {

            puts("Not found.");
            return;

        }

    }

    if (pos < 0)
        return;

    else if (pos > list_aux->size)
        return;

    else if (pos == list_aux->size - 1 && list_aux->size > 1) {
        
        // If it's the last position from the list

        aux1 = list_aux->end;
        aux2 = aux1->prev;

        if(remove_elements == true) free_node(aux1->element);
        free(aux1);

        aux2->next = NULL;
        list_aux->end = aux2;
        list_aux->size--;

    } else if (pos == 0 && list_aux->size > 1) {
        
        // Remove first element from list

        aux1 = list_aux->head->next;

        if(remove_elements == true) free_node(list_aux->head->element);

        free(list_aux->head);

        list_aux->head = aux1;
        list_aux->size--;

    } else if (pos == 0 && list_aux->size == 1) {

        // Remove the only element of the list

        if(remove_elements == true) free_node(list_aux->head->element);

        free(list_aux->head);

        list_aux->head = NULL;
        list_aux->end = NULL;

        list_aux->size--;

    } else {

        aux1 = at_pos(list_aux, pos - 1);
        aux2 = at_pos(list_aux, pos);

        aux1->next = aux2->next;
        aux2->next->prev = aux1;

        if(remove_elements == true) free_node(aux2->element);
        free(aux2);

        list_aux->size--;
    }
}

void* find_element(void* sequence, void* match, int (*compare_info)(void*, void*)) {
    
    if(!sequence) return NULL;
    
    list* list_aux = sequence;
    node* node_aux = list_aux->head;
    

    for(int i = 0; i < list_aux->size; i++) {

        if(compare_info(node_aux->element, match)) return node_aux->element;
    
        node_aux = node_aux->next;

    }
    return NULL;
}