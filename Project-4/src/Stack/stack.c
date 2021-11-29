#include "stack.h"

typedef struct node {
    
    struct node* down;
    void* element;

} node;

typedef struct stack {

    node* top;    
    int size;

} stack;

void* create_stack() {

    stack* new_stack = malloc(sizeof(stack));
    new_stack->size = 0;
    new_stack->top = NULL;
    
    return new_stack;

}

void stack_push(void* sequence, void* element) {

    stack* stack_aux = sequence;
    node* aux = calloc(1, sizeof(node));
    aux->element = element;
    aux->down = stack_aux->top;
    stack_aux->top = aux;
    stack_aux->size++;

}

int stack_get_size(void* sequence) {
    
    stack* stack_aux = sequence;
    return stack_aux->size;

}

void* stack_get_top(void* sequence) {

    stack* stack_aux = sequence;
    return stack_aux->top;

}

void* stack_get_down(void* current) {
    
    node* aux = current;

    if (aux) return aux->down;

    return NULL;
}

void* stack_get_element(void* current) {

    node* aux = current;
    return aux->element;

}

void* stack_pop(void* sequence, void (*free_node)(void*), bool remove_elements) {
    
    stack* stack_aux = sequence;

    if(!stack_aux->size){

        return NULL;

    }

    node* aux = stack_aux->top;
    stack_aux->top = aux->down;
    stack_aux->size--;

    if(remove_elements){
        free_node(aux->element);
        return NULL;
    } else {
        return aux->element;
    }

}

void stack_free(void* sequence, bool remove_elements) {
    
    if(!sequence) return;

    stack* stack_aux = sequence;

    
    if (stack_aux->size == 0) {

        free(sequence);
        return;

    }

    node* auxNode = stack_aux->top;
    node* auxElement = stack_aux->top->element;

    while (stack_aux->top != NULL) {

        auxNode = stack_aux->top;
        auxElement = stack_aux->top->element;
        stack_aux->top = stack_aux->top->down;

        if(remove_elements == true) free(auxElement);

        free(auxNode);
    }

    free(sequence);
}