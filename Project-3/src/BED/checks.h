#include "libs.h"

void* create_checkers();
bool get_qry_inserted(void* current_flags);
bool get_pm_inserted(void* current_flags);
void set_qry_inserted(void* current_flags, bool newValue);
void set_pm_inserted(void* current_flags, bool newValue);