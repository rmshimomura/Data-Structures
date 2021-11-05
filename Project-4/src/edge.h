#include "libs.h"

char* edge_get_name(void* data);
char* edge_get_left_side_square(void* data);
char* edge_get_right_side_square(void* data);
double edge_get_length(void* data);
double edge_get_average_speed(void* data);
void edge_set_name(void* data, char* name);
void edge_set_left_side_square(void* data, char* left_side_square);
void edge_set_right_side_square(void* data, char* right_side_square);
void edge_set_length(void* data, double length);
void edge_set_average_speed(void* data, double length);