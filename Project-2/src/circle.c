#include "circle.h"

typedef struct data_c {
    double x, y, radius, radiation, nearest_distance, original_x, original_y;
    int inside_n_shadows;
    char id[100], fill[100], stroke[100];
    void* run_to;
    bool fg;
    bool alive;
    bool marked_for_death;

} data_c;

void* create_circle() {
    data_c* aux = calloc(1, sizeof(data_c));
    return aux;
}

void set_circle_x(node current, double x) {
    data_c* aux = current;
    aux->x = x;
}

void set_circle_y(node current, double y) {
    data_c* aux = current;
    aux->y = y;
}

void set_circle_id(node current, char* idValue) {
    data_c* aux = current;
    strcpy(aux->id, idValue);
}

void set_circle_fill(node current, char* fillValue) {
    data_c* aux = current;
    strcpy(aux->fill, fillValue);
}

void set_circle_stroke(node current, char* strokeValue) {
    data_c* aux = current;
    strcpy(aux->stroke, strokeValue);
}

void set_circle_radius(node current, double radius) {
    data_c* aux = current;
    aux->radius = radius;
}

double get_radiation(node current) {
    data_c* aux = current;
    return aux->radiation;
}

void set_radiation(node current, double newRadiation) {
    data_c* aux = current;
    aux->radiation = newRadiation;
}

void set_inside_n_shadows(node current, int numberOfShadows) {
    data_c* aux = current;
    aux->inside_n_shadows = numberOfShadows;
}

int get_inside_n_shadows(node current) {
    data_c* aux = current;
    return aux->inside_n_shadows;
}

double get_circle_x(node current) {
    data_c* aux = current;
    return aux->x;
}

double get_circle_y(node current) {
    data_c* aux = current;
    return aux->y;
}

char* get_circle_id(node current) {
    data_c* aux = current;
    return aux->id;
}

char* get_circle_fill(node current) {
    data_c* aux = current;
    return aux->fill;
}

char* get_circle_stroke(node current) {
    data_c* aux = current;
    return aux->stroke;
}

double get_circle_radius(node current) {
    data_c* aux = current;
    return aux->radius;
}

void* get_run_to(node current) {
    data_c* aux = current;
    return aux->run_to;
}

void set_run_to(node current, void* building) {
    data_c* aux = current;
    aux->run_to = building;
}

void set_nearest_distance(node current, double distance) {
    data_c* aux = current;
    aux->nearest_distance = distance;
}

double get_nearest_distance(node current) {
    data_c* aux = current;
    return aux->nearest_distance;
}

void set_fg(node current, bool state) {
    data_c* aux = current;
    aux->fg = state;
}

bool get_fg(node current) {
    data_c* aux = current;
    return aux->fg;
}

void set_circle_original_x(node current, double x) {
    data_c* aux = current;
    aux->original_x = x;
}

double get_circle_original_x(node current) {
    data_c* aux = current;
    return aux->original_x;
}

void set_circle_original_y(node current, double y) {
    data_c* aux = current;
    aux->original_y = y;
}

double get_circle_original_y(node current) {
    data_c* aux = current;
    return aux->original_y;
}

void set_circle_alive(node current, bool isAlive) {
    data_c* aux = current;
    aux->alive = isAlive;
}

bool get_circle_alive(node current) {
    data_c* aux = current;
    return aux->alive;
}

void set_circle_marked_for_death(node current, bool goingToDie) {
    data_c* aux = current;
    aux->marked_for_death = goingToDie;
}

bool get_circle_marked_for_death(node current) {
    data_c* aux = current;
    return aux->marked_for_death;
}