#include "libs.h"

#ifndef BLOCK_H
#define BLOCK_H

void* create_block();
void set_block_properties(void* block_to_set, char* cep, double x, double y, double w, double h, double sw, char* cfill, char* cstroke);
int compare_x(void* node, void* element);
double get_x(void* current_block);
double get_y(void* current_block);
double get_w(void* current_block);
double get_h(void* current_block);
double get_sw(void* current_block);
char* get_cfill(void* current_block);
char* get_cstroke(void* current_block);
void set_x(void* current_block, double newValue);
void set_y(void* current_block, double newValue);
void set_w(void* current_block, double newValue);
void set_h(void* current_block, double newValue);
void set_sw(void* current_block, double newValue);
void set_cfill(void* current_block, char* newValue);
void set_cstroke(void* current_block, char* newValue);

#endif