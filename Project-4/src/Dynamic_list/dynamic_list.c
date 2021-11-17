#include "dynamic_list.h"
#include "../vertex.h"
#include "../block.h"

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

void* insert_list(void* sequence, void* element) {

    if(!element) return NULL;

    list* list_aux = sequence;
    node* node_aux = calloc(1, sizeof(node));
    node_aux->element = element;

    if (list_aux->size == 0) {

        node_aux->next = NULL;
        node_aux->prev = NULL;
        list_aux->head = node_aux;
        list_aux->end = node_aux;

    } else {

        node_aux->next = NULL;
        list_aux->end->next = node_aux;
        node_aux->prev = list_aux->end;
        list_aux->end = node_aux;
    }

    list_aux->size++;
    return node_aux;

}

void* insert_first(void* sequence, void* element) {

    if(!element) return NULL;

    list* list_aux = sequence;
    node* node_aux = calloc(1, sizeof(node));
    node_aux->element = element;

    if (list_aux->size == 0) {

        node_aux->next = NULL;
        node_aux->prev = NULL;
        list_aux->head = node_aux;
        list_aux->end = node_aux;

    } else {

        list_aux->head->prev = node_aux;
        node_aux->next = list_aux->head;
        node_aux->prev = NULL;
        list_aux->head = node_aux;
    }

    list_aux->size++;
    return node_aux;

}

int get_size(void* sequence) {
    
    if(!sequence) return -1;

    list* list_aux = sequence;
    return list_aux->size;

}

void* get_head(void* sequence) {

    if(!sequence) return NULL;
    
    list* list_aux = sequence;
    return list_aux->head;

}

void* get_end(void* sequence) {

    list* list_aux = sequence;
    return list_aux->end;

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

    node* aux_node = list_aux->head;
    node* aux_element = list_aux->head->element;

    while (list_aux->head != NULL) {

        aux_node = list_aux->head;
        aux_element = list_aux->head->element;
        list_aux->head = list_aux->head->next;

        if(remove_elements == true){
             free_node(aux_element);
        }

        free(aux_node);
        list_aux->size--;
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

void* remove_node(void* sequence, void* node_to_remove, void (*free_node)(void*), bool remove_elements) {
    
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
            return NULL;

        }

    }

    if (pos < 0)
        return NULL;

    else if (pos > list_aux->size)
        return NULL;

    else if (pos == list_aux->size - 1 && list_aux->size > 1) {
        
        // If it's the last position from the list

        aux1 = list_aux->end;
        aux2 = aux1->prev;
        void* temp = aux1->element;

        if(remove_elements) free_node(aux1->element);
        
        free(aux1);

        aux2->next = NULL;
        list_aux->end = aux2;
        list_aux->size--;

        if(!remove_elements) return temp;

    } else if (pos == 0 && list_aux->size > 1) {
        
        // Remove first element from list

        aux1 = list_aux->head->next;

        void* temp = list_aux->head->element;

        if(remove_elements) free_node(list_aux->head->element);

        free(list_aux->head);

        list_aux->head = aux1;
        list_aux->size--;

        if(!remove_elements) return temp;

    } else if (pos == 0 && list_aux->size == 1) {

        // Remove the only element of the list

        void* temp = list_aux->head->element;

        if(remove_elements) free_node(list_aux->head->element);

        free(list_aux->head);

        list_aux->head = NULL;
        list_aux->end = NULL;

        list_aux->size--;

        if(!remove_elements) return temp;

    } else {

        aux1 = at_pos(list_aux, pos - 1);
        aux2 = at_pos(list_aux, pos);

        aux1->next = aux2->next;
        aux2->next->prev = aux1;

        void* temp = aux2->element;

        if(remove_elements) free_node(aux2->element);

        free(aux2);

        list_aux->size--;

        if(!remove_elements) return temp;

    }

    return NULL;

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

void* find_element_by_vertex_name(void* sequence, void* match) {
    
    if(!sequence) return NULL;
    
    list* list_aux = sequence;
    node* node_aux = list_aux->head;
    

    for(int i = 0; i < list_aux->size; i++) {

        if(!strcmp(vertex_data_get_id(node_aux->element), match)) return node_aux->element;
    
        node_aux = node_aux->next;

    }
    return NULL;
}

void list_swap (void* a, void* b){
    node *node_a = a, *node_b = b;
    void* t = node_b->element;
    node_b->element = node_a->element;
    node_a->element = t;
}

node* list_partition(node *l, node *h, int (*cmp)(void*, void*)){

    void *x = h->element;
 
    node *i = l->prev;
 
    for (node *j = l; j != h; j = j->next){

        if (cmp(j->element, x) < 0){
            i = (i == NULL) ? l : i->next;
 
            list_swap(i, j);
        }
    }
    i = (i == NULL) ? l : i->next;
    list_swap(i, h);
    return i;
}
 
void list_quick_sort_(node* l, node *h, int (*cmp)(void*, void*)){
    
    if (h != NULL && l != h && l != h->next) {

        node* p = list_partition(l, h, cmp);
        list_quick_sort_(l, p->prev, cmp);
        list_quick_sort_(p->next, h, cmp);

    }

}
 
void list_sort(void* list_, int (*cmp)(void*, void*)) {

    list* sequence = list_;
    node* head = sequence->head;
    node* h = sequence->end;
 
    list_quick_sort_(head, h, cmp);
}

void free_block_list(void* sequence){

    if(!sequence){
        return;
    }

    list* list_aux = sequence;

    if(!list_aux->size){
        free(list_aux);
        return;
    }

    node* aux_node = list_aux->head;
    node* aux_element = list_aux->head->element;

    while(list_aux->head != NULL) {
        
        aux_node = list_aux->head;
        aux_element = list_aux->head->element;
        list_aux->head = list_aux->head->next;
        free_single_block(aux_element);
        free(aux_node);
    }

    free(sequence);


}