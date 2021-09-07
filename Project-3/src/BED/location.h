#include "libs.h"

#ifndef LOCATION_H
#define LOCATION_H

void* create_location();
void set_location_properties(void* location_to_set, char* id, char* cep, char face, int num, char* compl, double ar, double v);


#endif