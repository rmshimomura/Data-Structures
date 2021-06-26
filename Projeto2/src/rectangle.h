#include "bibliotecas.h"
#ifndef RECTANGLE_H
#define RECTANGLE_H

item create_rectangle();
void set_rectangle_x(node current, double x);
void set_rectangle_y(node current, double y);
void set_rectangle_width(node current, double width);
void set_rectangle_height(node current, double height);
void set_rectangle_id(node current, char* idValue);
void set_rectangle_fill(node current, char* fillValue);
void set_rectangle_stroke(node current, char* strokeValue);
void set_rectangle_center_x(node current, double centerX);
void set_rectangle_center_y(node current, double centerY);
double get_rectangle_x(node current);
double get_rectangle_y(node current);
double get_rectangle_width(node current);
double get_rectangle_height(node current);
char* get_rectangle_id(node current);
char* get_rectangle_fill(node current);
char* get_rectangle_stroke(node current);
double get_rectangle_center_x(node current);
double get_rectangle_center_y(node current);
void set_vector_of_people_started(node current, bool state);
bool get_vector_of_people_started(node current);
void set_number_of_people_inside(node current, int people);
int get_number_of_people_inside(node current);
void allocate_vector_of_people(node current);
void free_vector_of_people(node current);
void** get_vector_of_people(node current);
void set_addresses(node current, void* address, int line);

#endif