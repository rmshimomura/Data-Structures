#include "viewbox.h"

typedef struct view_box {

    double smallest_x, smallest_y, biggest_x, biggest_y;

} view_box;

void* create_view_box() {

    view_box* box = calloc(1, sizeof(view_box));
    box->smallest_x = __DBL_MAX__;
    box->smallest_y = __DBL_MAX__;
    box->biggest_x = 0;
    box->biggest_y = 0;

    return box;

}

double get_smallest_x(void* data) {

    view_box* aux = data;
    return aux->smallest_x;

}

double get_smallest_y(void* data) {

    view_box* aux = data;
    return aux->smallest_y;

}

double get_biggest_x(void* data) {

    view_box* aux = data;
    return aux->biggest_x;

}

double get_biggest_y(void* data) {

    view_box* aux = data;
    return aux->biggest_y;

}

void set_smallest_x(void* data, double value) {

    view_box* aux = data;
    aux->smallest_x = value;

}

void set_smallest_y(void* data, double value) {

    view_box* aux = data;
    aux->smallest_y = value;

}

void set_biggest_x(void* data, double value) {

    view_box* aux = data;
    aux->biggest_x = value;

}

void set_biggest_y(void* data, double value) {

    view_box* aux = data;
    aux->biggest_y = value;

}