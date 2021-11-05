#include "edge.h"
#include "vertex.h"

typedef struct edge_data {

    char* name;
    char* left_side_square;
    char* right_side_square;
    double length;
    double average_speed;
    char direction[2];

} edge_data;

void* new_edge_data(char* name, char* left_side_square, char* right_side_square, double length, double average_speed, void* vertex_1_data, void* vertex_2_data) {

    edge_data* aux = calloc(1, sizeof(edge_data));
    strcpy(aux->name, name);
    strcpy(aux->left_side_square, left_side_square);
    strcpy(aux->right_side_square, right_side_square);
    aux->length = length;
    aux->average_speed = average_speed;

    if(vertex_get_x(vertex_1_data) == vertex_get_x(vertex_2_data)) {

        vertex_get_y(vertex_1_data) > vertex_get_y(vertex_2_data) ? strcpy(aux->direction, "S") : strcpy(aux->direction, "N");
        
    } else if (vertex_get_y(vertex_1_data) == vertex_get_y(vertex_2_data)){

        vertex_get_x(vertex_1_data) > vertex_get_x(vertex_2_data) ? strcpy(aux->direction, "W") : strcpy(aux->direction, "E");

    }

    //TODO NW, NE, SW, SE

}

char* edge_get_name(void* data) {
    edge_data* aux = data;
    return aux->name;
}

char* edge_get_left_side_square(void* data) {
    edge_data* aux = data;
    return aux->left_side_square;
}

char* edge_get_right_side_square(void* data) {
    edge_data* aux = data;
    return aux->right_side_square;
}

double edge_get_length(void* data) {
    edge_data* aux = data;
    return aux->length;
}

double edge_get_average_speed(void* data) {
    edge_data* aux = data;
    return aux->average_speed;
}

char* edge_get_direction(void* data) {
    edge_data* aux = data;
    return aux->direction;
}

void edge_set_name(void* data, char* name) {
    edge_data* aux = data;
    strcpy(aux->name, name);
}

void edge_set_left_side_square(void* data, char* left_side_square) {
    edge_data* aux = data;
    strcpy(aux->left_side_square, left_side_square);
}

void edge_set_right_side_square(void* data, char* right_side_square) {
    edge_data* aux = data;
    strcpy(aux->right_side_square, right_side_square);
}

void edge_set_length(void* data, double length) {
    edge_data* aux = data;
    aux->length = length;
}

void edge_set_average_speed(void* data, double length) {
    edge_data* aux = data;
    aux->length = length;
}

void edge_set_direction(void* data, char* direction) {
    edge_data* aux = data;
    strcpy(aux->direction, direction);
}