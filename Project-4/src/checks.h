#include "libs.h"

#ifndef CHECKS_H
#define CHECKS_H

void* create_checkers();
bool get_qry_inserted(void* current_flags);
void set_qry_inserted(void* current_flags, bool new_value);
bool get_roads_inserted(void* current_flags);
void set_roads_inserted(void* current_flags, bool new_value);

#endif