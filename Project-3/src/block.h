#include "libs.h"

#ifndef BLOCK_H
#define BLOCK_H

void* create_block();
void set_block_properties(void* block_to_set, char* cep, double x, double y, double w, double h, char* sw, char* cfill, char* cstroke);
int compare_cep(void* node, void* element);
void add_resident(void* block_data, void* person);
void add_location(void* block_data, void* new_location);
double get_x(void* current_block);
double get_y(void* current_block);
double get_w(void* current_block);
double get_h(void* current_block);
char* get_sw(void* current_block);
char* get_cfill(void* current_block);
char* get_cstroke(void* current_block);
void** get_residents(void* block_data);
void** get_locations(void* block_data);
char* get_cep(void* current_block);
void free_single_block(void* block_data);
int get_number_of_persons_living(void* block_data);
int get_number_of_locations_available(void* block_data);
void set_x(void* current_block, double newValue);
void set_y(void* current_block, double newValue);
void set_w(void* current_block, double newValue);
void set_h(void* current_block, double newValue);
void set_sw(void* current_block, char* newValue);
void set_cfill(void* current_block, char* newValue);
void set_cstroke(void* current_block, char* newValue);
void set_cep(void* current_block, char* newValue);

#endif