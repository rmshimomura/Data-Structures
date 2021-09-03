#include "dynamicList.h"

/*===============================*/

/*Double linked list*/

typedef struct data {

    struct data* next;
    struct data* prev;
    void* element;


} data_t;

typedef struct list {
    data_t* head;
    data_t* end;
    int size;

} list_t;

/*===============================*/

void* create_list() {
    list_t* newList = malloc(sizeof(list_t));
    newList->head = NULL;
    newList->end = NULL;
    newList->size = 0;
    return newList;
}

void* insert_list(void* sequence, void* element) {
    list_t* listAux = sequence;
    data_t* pontAux = calloc(1, sizeof(data_t));
    pontAux->element = element;


    if (listAux->size == 0) {
        pontAux->next = NULL;
        pontAux->prev = NULL;
        listAux->head = pontAux;
        listAux->end = pontAux;

    } else {
        pontAux->next = NULL;
        listAux->end->next = pontAux;
        pontAux->prev = listAux->end;
        listAux->end = pontAux;
    }

    listAux->size++;

    return pontAux;
}

int get_size(void* sequence) {
    list_t* listAux = sequence;
    return listAux->size;
}

void* get_head(void* sequence) {
    list_t* listAux = sequence;
    return listAux->head;
}

void* get_next(void* current) {
    
    data_t* aux = current;

    if (aux) return aux->next;

    return NULL;
}

void* get_previous(void* current) {
    data_t* aux = current;

    if (aux->prev) return aux->prev;

    return NULL;
}

void* get_list_element(void* current) {
    data_t* aux = current;
    return aux->element;
}

// void free_list(void* sequence) {
//     list_t* listAux = sequence;

//     if (listAux->size == 0) {
//         free(sequence);
//         return;
//     }

//     data_t* auxNode = listAux->head;
//     data_t* auxElement = listAux->head->element;

//     while (listAux->head != NULL) {
//         auxNode = listAux->head;
//         auxElement = listAux->head->element;
//         listAux->head = listAux->head->next;

//         free(auxElement);
//         free(auxNode);
//     }

//     free(sequence);
// }

void free_list(void* sequence, void (*free_data)(void*)){
    
    if(!sequence){
        return;
    }

    list_t* list_aux = sequence;

    if(!list_aux->size){
        free(list_aux);
        return;
    }

    data_t* auxNode = list_aux->head;
    data_t* auxElement = list_aux->head->element;

    while(list_aux->head != NULL) {
        
        auxNode = list_aux->head;
        auxElement = list_aux->head->element;
        list_aux->head = list_aux->head->next;
        free_data(auxElement);
        free(auxNode);
    }

    free(sequence);


}

void* at_pos(void* sequence, int index) {
    list_t* listAux = sequence;
    data_t* aux = listAux->head;

    for (int i = 0; i < index; i++) aux = get_next(aux);

    return aux;
}

// void remove_node(void* sequence, void* current) {
//     list_t* listAux = sequence;
//     data_t* aux1;
//     data_t* aux2;
//     void* get_item_aux1;
//     void* get_item_aux2;
//     data_t* posToRemove = listAux->head;
//     int pos = 0;

//     while (posToRemove != current) {
//         posToRemove = posToRemove->next;
//         pos++;

//         if (pos > listAux->size) {
//             puts("Nao encontrado.");
//             return;
//         }
//     }

//     if (pos < 0)
//         return;

//     else if (pos > listAux->size)
//         return;

//     else if (pos == listAux->size - 1 && listAux->size > 1) {
//         // If its the last position from the list

//         aux1 = at_pos(listAux, pos - 1);
//         aux2 = at_pos(listAux, pos);
//         get_item_aux2 = get_item(current);
//         destory_segment(get_item_aux2);
//         free(aux2);
//         aux1->next = NULL;
//         listAux->end = aux1;
//         listAux->size--;

//     } else if (pos == 0 && listAux->size > 1) {
//         // Remove first element from list

//         aux1 = at_pos(listAux, 0);
//         get_item_aux1 = get_item(get_head(sequence));
//         listAux->head = listAux->head->next;
//         destory_segment(get_item_aux1);
//         free(aux1);
//         listAux->size--;

//     } else if (pos == 0 && listAux->size == 1) {
//         // Remove the only element of the list

//         aux1 = at_pos(listAux, 0);
//         get_item_aux1 = get_item(get_head(sequence));
//         listAux->head = NULL;
//         listAux->end = NULL;
//         destory_segment(get_item_aux1);
//         free(aux1);
//         listAux->size--;

//     } else {
//         aux1 = at_pos(listAux, pos - 1);
//         aux2 = at_pos(listAux, pos);
//         get_item_aux2 = get_item(current);
//         aux1->next = aux2->next;
//         aux2->next->prev = aux1;
//         destory_segment(get_item_aux2);
//         free(aux2);
//         listAux->size--;
//     }
// }

void remove_node(void* sequence, void* current, void (free_data)(void*)) {
    list_t* listAux = sequence;
    data_t* aux1;
    data_t* aux2;

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

    if (pos < 0)
        return;

    else if (pos > listAux->size)
        return;

    else if (pos == listAux->size - 1 && listAux->size > 1) {
        // If it is the last position from the list

        aux1 = at_pos(listAux, pos - 1);
        aux2 = at_pos(listAux, pos);
        free_data(aux2->element);
        free(aux2);
        aux1->next = NULL;
        listAux->end = aux1;
        listAux->size--;

    } else if (pos == 0 && listAux->size > 1) {
        // Remove first element from list

        aux1 = at_pos(listAux, 0);
        free_data(aux1->element);
        listAux->head = listAux->head->next;
        free(aux1);
        listAux->size--;

    } else if (pos == 0 && listAux->size == 1) {
        // Remove the only element of the list

        aux1 = at_pos(listAux, 0);
        
        listAux->head = NULL;
        listAux->end = NULL;
        
        free_data(aux1->element);
        free(aux1);
        listAux->size--;

    } else {
        aux1 = at_pos(listAux, pos - 1);
        aux2 = at_pos(listAux, pos);
        free_data(aux2->element);
        aux1->next = aux2->next;
        aux2->next->prev = aux1;
        free(aux2);
        listAux->size--;
    }
}

void* findItem(void* sequence, void* match, int (*compare_info)(void*, void*)){
    
    list_t* list_aux = sequence;
    data_t* node_aux = list_aux->head;

    for(int i = 0; i < list_aux->size; i++){

        if(compare_info(node_aux->element, match)) return match;
    
        node_aux = node_aux->next;

    }
    return NULL;
}
