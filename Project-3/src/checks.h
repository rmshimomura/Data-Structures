#include "libs.h"

#ifndef CHECKS_H
#define CHECKS_H

void* create_checkers();
bool get_qry_inserted(void* current_flags);
bool get_pm_inserted(void* current_flags);
void set_qry_inserted(void* current_flags, bool newValue);
void set_pm_inserted(void* current_flags, bool newValue);

#endif