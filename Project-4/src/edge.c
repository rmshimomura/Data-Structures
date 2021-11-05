#include "edge.h"

typedef struct edge_data {

    char* name;
    char* left_side_square;
    char* right_side_square;
    double length;
    double average_speed;

} edge_data;

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