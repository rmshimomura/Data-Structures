#include "libs.h"

#ifndef CHECKS_H
#define CHECKS_H

void* create_checkers();
bool get_qry_inserted(void* current_flags);
bool get_pm_inserted(void* current_flags);
bool get_via_inserted(void* current_flags);
void set_via_inserted(void* current_flags, bool new_value);

#endif