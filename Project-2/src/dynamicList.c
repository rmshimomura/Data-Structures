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

void* create_list() {
    list_t* newList = malloc(sizeof(list_t));
    newList->head = NULL;
    newList->end = NULL;
    newList->size = 0;
    return newList;
}

void* insert(void* sequence, void* element) {
    list_t* listAux = sequence;
    data_t* pontAux = calloc(1, sizeof(data_t));
    pontAux->element = element;
    pontAux->radiation = 0;
    pontAux->xMeteor = 0;
    pontAux->yMeteor = 0;

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

double get_data_radiation(void* node) {
    data_t* dataAux = node;
    return dataAux->radiation;
}

void set_data_radiation(void* node, double radiation) {
    data_t* dataAux = node;
    dataAux->radiation = radiation;
}

double get_data_x_meteor(void* node) {
    data_t* dataAux = node;
    return dataAux->xMeteor;
}

void set_data_x_meteor(void* node, double xMeteor) {
    data_t* dataAux = node;
    dataAux->xMeteor = xMeteor;
}

double get_data_y_meteor(void* node) {
    data_t* dataAux = node;
    return dataAux->yMeteor;
}

void set_data_y_meteor(void* node, double yMeteor) {
    data_t* dataAux = node;
    dataAux->yMeteor = yMeteor;
}

void* get_head(void* sequence) {
    list_t* listAux = sequence;
    return listAux->head;
}

void* get_next(void* sequence, void* current) {
    list_t* listAux = sequence;
    data_t* aux = current;

    if (aux) return aux->next;

    return NULL;
}

void* get_previous(void* sequence, void* current) {
    list_t* listAux = sequence;
    data_t* aux = current;

    if (aux->prev) return aux->prev;

    return NULL;
}

void* get_item(void* sequence, void* current) {
    data_t* aux = current;
    return aux->element;
}

void free_list(void* sequence) {
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

        free(auxElement);
        free(auxNode);
    }

    free(sequence);
}

void free_list_of_segments(void* sequence) {
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
            free_points_info(auxElement);
            free(auxElement);
        }

        free(auxNode);
    }

    free(sequence);
}

void* at_pos(void* sequence, int index) {
    list_t* listAux = sequence;
    data_t* aux = listAux->head;

    for (int i = 0; i < index; i++) {
        aux = get_next(sequence, aux);
    }
    return aux;
}

void remove_node(void* sequence, void* current) {
    list_t* listAux = sequence;
    data_t* aux1;
    data_t* aux2;
    void* get_item_aux1;
    void* get_item_aux2;
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
        // If its the last position from the list

        aux1 = at_pos(listAux, pos - 1);
        aux2 = at_pos(listAux, pos);
        get_item_aux2 = get_item(sequence, current);
        destory_segment(get_item_aux2);
        free(aux2);
        aux1->next = NULL;
        listAux->end = aux1;
        listAux->size--;

    } else if (pos == 0 && listAux->size > 1) {
        // Remove first element from list

        aux1 = at_pos(listAux, 0);
        get_item_aux1 = get_item(sequence, get_head(sequence));
        listAux->head = listAux->head->next;
        destory_segment(get_item_aux1);
        free(aux1);
        listAux->size--;

    } else if (pos == 0 && listAux->size == 1) {
        // Remove the only element of the list

        aux1 = at_pos(listAux, 0);
        get_item_aux1 = get_item(sequence, get_head(sequence));
        listAux->head = NULL;
        listAux->end = NULL;
        destory_segment(get_item_aux1);
        free(aux1);
        listAux->size--;

    } else {
        aux1 = at_pos(listAux, pos - 1);
        aux2 = at_pos(listAux, pos);
        get_item_aux2 = get_item(sequence, current);
        aux1->next = aux2->next;
        aux2->next->prev = aux1;
        destory_segment(get_item_aux2);
        free(aux2);
        listAux->size--;
    }
}

void free_list_of_trees_shadows(void* sequence) {
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
            free_NT_tree(auxElement, NT_get_root_node(auxElement));
            free(auxElement);
        }

        free(auxNode);
    }

    free(sequence);
}