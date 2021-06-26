#include "rectangle.h"

typedef struct data {
    double x, y, width, height, centerX, centerY;
    char id[100], fill[100], stroke[100];
    void** people_inside;
    bool vector_of_addresses_started;
    int number_of_people_inside;

} data_t;

void* create_rectangle() {
    data_t* aux = (data_t*)calloc(1, sizeof(data_t));
    return aux;
}

void set_rectangle_x(node current, double x) {
    data_t* aux = current;
    aux->x = x;
}

void set_rectangle_y(node current, double y) {
    data_t* aux = current;
    aux->y = y;
}

void set_rectangle_width(node current, double width) {
    data_t* aux = current;
    aux->width = width;
}

void set_rectangle_height(node current, double height) {
    data_t* aux = current;
    aux->height = height;
}

void set_rectangle_id(node current, char* idValue) {
    data_t* aux = current;
    strcpy(aux->id, idValue);
}

void set_rectangle_fill(node current, char* fillValue) {
    data_t* aux = current;
    strcpy(aux->fill, fillValue);
}

void set_rectangle_stroke(node current, char* strokeValue) {
    data_t* aux = current;
    strcpy(aux->stroke, strokeValue);
}

void set_rectangle_center_x(node current, double centerX) {
    data_t* aux = current;
    aux->centerX = centerX;
}

void set_rectangle_center_y(node current, double centerY) {
    data_t* aux = current;
    aux->centerY = centerY;
}

//===============================================//

double get_rectangle_x(node current) {
    data_t* aux = current;
    return aux->x;
}

double get_rectangle_y(node current) {
    data_t* aux = current;
    return aux->y;
}

double get_rectangle_width(node current) {
    data_t* aux = current;
    return aux->width;
}

double get_rectangle_height(node current) {
    data_t* aux = current;
    return aux->height;
}

char* get_rectangle_id(node current) {
    data_t* aux = current;
    return aux->id;
}

char* get_rectangle_fill(node current) {
    data_t* aux = current;
    return aux->fill;
}

char* get_rectangle_stroke(node current) {
    data_t* aux = current;
    return aux->stroke;
}

double get_rectangle_center_x(node current) {
    data_t* aux = current;
    return aux->centerX;
}

double get_rectangle_center_y(node current) {
    data_t* aux = current;
    return aux->centerY;
}

void set_vector_of_people_started(node current, bool state) {
    data_t* aux = current;
    aux->vector_of_addresses_started = state;
}

bool get_vector_of_people_started(node current) {
    data_t* aux = current;
    return aux->vector_of_addresses_started;
}

void set_number_of_people_inside(node current, int people) {
    data_t* aux = current;
    aux->number_of_people_inside = people;
}

int get_number_of_people_inside(node current) {
    data_t* aux = current;
    return aux->number_of_people_inside;
}

void** get_vector_of_people(node current) {
    data_t* aux = current;
    return aux->people_inside;
}

void allocate_vector_of_people(node current) {
    data_t* aux = current;

    if (!get_vector_of_people(current) || !aux->number_of_people_inside) {
        aux->people_inside = calloc(1, sizeof(void*));

    } else {
        aux->people_inside = realloc(aux->people_inside, (aux->number_of_people_inside + 1) * sizeof(void*));
    }
}

void set_addresses(node current, void* address, int line) {
    data_t* aux = current;
    aux->people_inside[line] = address;
}

void free_vector_of_people(node current) {
    data_t* aux = current;

    for (int i = 0; i < get_number_of_people_inside(current); i++) {
        aux->people_inside[i] = NULL;
        free(aux->people_inside[i]);
    }
    free(aux->people_inside);
}