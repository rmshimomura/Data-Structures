#include "bibliotecas.h"
#ifndef CIRCLE_H
#define CIRCLE_H

item create_circle();
void set_circle_x(node current, double x);
void set_circle_y(node current, double y);
void set_circle_id(node current, char* idValue);
void set_circle_fill(node current, char* fillValue);
void set_circle_stroke(node current, char* strokeValue);
void set_circle_radius(node current, double radius);
double get_circle_x(node current);
double get_circle_y(node current);
char* get_circle_id(node current);
char* get_circle_fill(node current);
char* get_circle_stroke(node current);
double get_circle_radius(node current);
void* get_run_to(node current);
void set_run_to(node current, void* building);
void set_nearest_distance(node current, double distance);
double get_nearest_distance(node current);
void set_fg(node current, bool state);
bool get_fg(node current);
void set_circle_original_x(node current, double x);
double get_circle_original_x(node current);
void set_circle_original_y(node current, double y);
double get_circle_original_y(node current);
double get_radiation(node current);
void set_radiation(node current, double newRadiation);
void set_inside_n_shadows(node current, int numberOfShadows);
int get_inside_n_shadows(node current);
void set_circle_alive(node current, bool isAlive);
bool get_circle_alive(node current);
void set_circle_marked_for_death(node current, bool goingToDie);
bool get_circle_marked_for_death(node current);


#endif