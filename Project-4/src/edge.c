#include "edge.h"
#include "vertex.h"

typedef struct edge_data {

    char* name;
    char* left_side_square;
    char* right_side_square;
    double length;
    double average_speed;

} edge_data;

void* new_edge_data(char* name, char* left_side_square, char* right_side_square, double length, double average_speed, void* vertex_1_data, void* vertex_2_data) {

    edge_data* aux = calloc(1, sizeof(edge_data));
    aux->name = calloc(strlen(name) + 1, sizeof(char));
    strcpy(aux->name, name);
    aux->left_side_square = calloc(strlen(left_side_square) + 1, sizeof(char));
    strcpy(aux->left_side_square, left_side_square);
    aux->right_side_square = calloc(strlen(right_side_square) + 1, sizeof(char));
    strcpy(aux->right_side_square, right_side_square);
    aux->length = length;
    aux->average_speed = average_speed;

    return aux;

}

void free_edge_data (void* data) {

    edge_data* aux = data;
    free(aux->name);
    free(aux->left_side_square);
    free(aux->right_side_square);
    free(aux);

}

double shortest_path(void* data) {

    return ((edge_data*)data)->length;

}

double fastest_path(void* data) {

    return (((edge_data*)data)->length/((edge_data*)data)->average_speed);

}

char* edge_data_get_name(void* data) {
    edge_data* aux = data;
    return aux->name;
}

char* edge_data_get_left_side_square(void* data) {
    edge_data* aux = data;
    return aux->left_side_square;
}

char* edge_data_get_right_side_square(void* data) {
    edge_data* aux = data;
    return aux->right_side_square;
}

double edge_data_get_length(void* data) {
    edge_data* aux = data;
    return aux->length;
}

double edge_data_get_average_speed(void* data) {
    edge_data* aux = data;
    return aux->average_speed;
}

void edge_data_set_name(void* data, char* name) {
    edge_data* aux = data;
    strcpy(aux->name, name);
}

void edge_data_set_left_side_square(void* data, char* left_side_square) {
    edge_data* aux = data;
    strcpy(aux->left_side_square, left_side_square);
}

void edge_data_set_right_side_square(void* data, char* right_side_square) {
    edge_data* aux = data;
    strcpy(aux->right_side_square, right_side_square);
}

void edge_data_set_length(void* data, double length) {
    edge_data* aux = data;
    aux->length = length;
}

void edge_data_set_average_speed(void* data, double average_speed) {
    edge_data* aux = data;
    aux->average_speed = average_speed;
}