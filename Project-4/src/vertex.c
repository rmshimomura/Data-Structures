#include "vertex.h"

typedef struct vertex_data {

    char* id;
    double x;
    double y;

} vertex_data;

void* new_vertex_data(char* id, double x, double y) {

    vertex_data* aux = calloc(1, sizeof(vertex_data));
    strcpy(aux->id, id);
    aux->x = x;
    aux->y = y;

    return aux;

}

char* vertex_get_id(void* data) {
    vertex_data* aux = data;
    return aux->id;
}

double vertex_get_x(void* data) {
    vertex_data* aux = data;
    return aux->x;
}

double vertex_get_y(void* data) {
    vertex_data* aux = data;
    return aux->y;
}

void vertex_set_id(void* data, char* id) {
    vertex_data* aux = data;
    strcpy(aux->id, id);
}

void vertex_set_x(void* data, double x) {
    vertex_data* aux = data;
    aux->x = x;
}

void vertex_set_y(void* data, double y) {
    vertex_data* aux = data;
    aux->y = y;
}