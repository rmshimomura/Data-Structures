#include "libs.h"

#ifndef VIEWBOX_H
#define VIEWBOX_H

void* create_view_box();
double get_smallest_x(void* data);
double get_smallest_y(void* data);
double get_biggest_x(void* data);
double get_biggest_y(void* data);
void set_smallest_x(void* data, double value);
void set_smallest_y(void* data, double value);
void set_biggest_x(void* data, double value);
void set_biggest_y(void* data, double value);

#endif 