#include "checks.h"

typedef struct flags {

    bool qry_inserted;
	bool via_inserted;

} flags;

void* create_checkers(){
    flags* new_checkers = calloc(1, sizeof(flags));
    set_via_inserted(new_checkers, false);
    set_qry_inserted(new_checkers, false);
	return new_checkers;
}

bool get_qry_inserted(void* current_flags){
	flags* aux = current_flags;
	return aux->qry_inserted; 
}

void set_qry_inserted(void* current_flags, bool new_value){
	flags* aux = current_flags;
	aux->qry_inserted = new_value;
}

bool get_via_inserted(void* current_flags){
	flags* aux = current_flags;
	return aux->via_inserted; 
}

void set_via_inserted(void* current_flags, bool new_value){
	flags* aux = current_flags;
	aux->via_inserted = new_value;
}