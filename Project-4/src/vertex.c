#include "vertex.h"

typedef struct vertex_data {

    char* id;
    double x;
    double y;

} vertex_data;

void* new_vertex_data(char* id, double x, double y) {

    vertex_data* aux = calloc(1, sizeof(vertex_data));
    aux->id = calloc(strlen(id) + 1, sizeof(char));
    strcpy(aux->id, id);
    aux->x = x;
    aux->y = y;

    return aux;

}

void free_vertex_data(void* data) {

    vertex_data* aux = data;
    free(aux->id);
    free(aux);

}

char* vertex_data_get_id(void* data) {
    vertex_data* aux = data;
    return data ? aux->id : "none";
}

double vertex_data_get_x(void* data) {
    vertex_data* aux = data;
    return aux->x;
}

double vertex_data_get_y(void* data) {
    vertex_data* aux = data;
    return aux->y;
}

void vertex_data_set_id(void* data, char* id) {
    vertex_data* aux = data;
    strcpy(aux->id, id);
}

void vertex_data_set_x(void* data, double x) {
    vertex_data* aux = data;
    aux->x = x;
}

void vertex_data_set_y(void* data, double y) {
    vertex_data* aux = data;
    aux->y = y;
}

char* direction(void* vertex_1, void* vertex_2, void* vertex_3) {

    double x1, y1, x2, y2, x3, y3;

    vertex_data* aux_1 = vertex_1;
    vertex_data* aux_2 = vertex_2;
    vertex_data* aux_3 = vertex_3;

    x1 = aux_1->x;
    y1 = aux_1->y;

    x2 = aux_2->x;
    y2 = aux_2->y;

    x3 = aux_3->x;
    y3 = aux_3->y;

    double coef_1 = (y2 - y1)/(x2 - x1);

    double coef_2 = (y3 - y2)/(x3 - x2);

    if(coef_1 == coef_2) {

        return "FOWARD";

    } else if (coef_1 > coef_2) {

        return "RIGHT";

    } else {

        return "LEFT";

    }
    
}