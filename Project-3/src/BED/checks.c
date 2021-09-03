#include "checks.h"

typedef struct flags {

    bool qry_inserted;
    bool pm_inserted;

} flags;

void* create_checkers(){
    flags* new_checkers = calloc(1, sizeof(flags));
    set_pm_inserted(new_checkers, false);
    set_qry_inserted(new_checkers, false);
}

bool get_qry_inserted(void* current_flags){
	flags* aux = current_flags;
	return aux->qry_inserted; 
}

void set_qry_inserted(void* current_flags, bool newValue){
	flags* aux = current_flags;
	aux->qry_inserted = newValue;
}

bool get_pm_inserted(void* current_flags){
	flags* aux = current_flags;
	return aux->pm_inserted; 
}

void set_pm_inserted(void* current_flags, bool newValue){
	flags* aux = current_flags;
	aux->pm_inserted = newValue;
}




