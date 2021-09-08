#include "libs.h"

#ifndef LOCATION_H
#define LOCATION_H

void* create_location();
void set_location_properties(void* location_to_set, char* id, char* cep, char face, int num, char* compl, double ar, double v);
int compare_id(void* current, void* match);
void location_info(void* location_data, FILE* txt_results);
char* location_get_cep(void* location_data);
char location_get_face(void* location_data);
int location_get_num(void* location_data);
char* location_get_complement(void* location_data);
void location_set_available(void* location_data, bool state);

#endif