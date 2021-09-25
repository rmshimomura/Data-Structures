#include "block.h"
#include "DynamicList/dynamicList.h"

typedef struct block {

    double x;
    double y;
    double w;
    double h;
    double sw;
    char cfill[30];
	char cep[50];
    char cstroke[30];
	void** persons_living;
	void** locations_available;
	int number_of_persons_living;
	int number_of_locations_available;

} block;

void set_block_properties(void* block_to_set, char* cep, double x, double y, double w, double h, double sw, char* cfill, char* cstroke){
	block* aux = block_to_set;
	aux->x = x;
	aux->y = y;
	aux->w = w;
	aux->h = h;
	aux->sw = sw;
	strcpy(aux->cep, cep);
	strcpy(aux->cfill, cfill);
	strcpy(aux->cstroke, cstroke);
}

void* create_block(){
	block* new_block = calloc(1, sizeof(block));
	new_block->number_of_persons_living = 0;
	new_block->number_of_locations_available = 0;
	return new_block;
}

void free_single_block(void* block_data){
	
	block* block_to_remove = block_data;

	free(block_to_remove->locations_available);
	free(block_to_remove->persons_living);

	free(block_to_remove);

}

void add_resident(void* block_data, void* person){
	
	block* new_block = block_data;
	
	if(!new_block->persons_living) {

		new_block->persons_living = calloc(1, sizeof(void*));
		new_block->persons_living[0] = person;
		new_block->number_of_persons_living++;

	}else{
		
		new_block->persons_living = realloc(new_block->persons_living, (new_block->number_of_persons_living + 1) * sizeof(void*));
		new_block->persons_living[new_block->number_of_persons_living] = person;
		new_block->number_of_persons_living++;

	}
	
}

void** get_residents(void* block_data){

	block* aux = block_data;

	return aux->persons_living ? aux->persons_living : NULL;

}

void add_location(void* block_data, void* new_location){
	
	block* new_block = block_data;
	
	if(!new_block->locations_available) {

		new_block->locations_available = calloc(1, sizeof(void*));
		new_block->locations_available[0] = new_location;
		new_block->number_of_locations_available++;

	}else{
		
		new_block->locations_available = realloc(new_block->locations_available, (new_block->number_of_locations_available + 1) * sizeof(void*));
		new_block->locations_available[new_block->number_of_locations_available] = new_location;
		new_block->number_of_locations_available++;

	}
	
}

void** get_locations(void* block_data){

	block* aux = block_data;

	return aux->locations_available ? aux->locations_available : NULL;

}

int get_number_of_persons_living(void* block_data){
	
	block* aux = block_data;
	return aux->number_of_persons_living;

}

int get_number_of_locations_available(void* block_data){
	
	block* aux = block_data;
	return aux->number_of_locations_available;

}

double get_x(void* current_block){
	block* aux = current_block;
	return aux->x; 
}

void set_x(void* current_block, double newValue){
	block* aux = current_block;
	aux->x = newValue;
}

double get_y(void* current_block){
	block* aux = current_block;
	return aux->y; 
}

void set_y(void* current_block, double newValue){
	block* aux = current_block;
	aux->y = newValue;
}

double get_w(void* current_block){
	block* aux = current_block;
	return aux->w; 
}

void set_w(void* current_block, double newValue){
	block* aux = current_block;
	aux->w = newValue;
}

double get_h(void* current_block){
	block* aux = current_block;
	return aux->h; 
}

void set_h(void* current_block, double newValue){
	block* aux = current_block;
	aux->h = newValue;
}

double get_sw(void* current_block){
	block* aux = current_block;
	return aux->sw; 
}

void set_sw(void* current_block, double newValue){
	block* aux = current_block;
	aux->sw = newValue;
}

char* get_cfill(void* current_block){
	block* aux = current_block;
	return aux->cfill; 
}

void set_cfill(void* current_block, char* newValue){
	block* aux = current_block;
	strcpy(aux->cfill, newValue);
}

char* get_cstroke(void* current_block){
	block* aux = current_block;
	return aux->cstroke; 
}

void set_cstroke(void* current_block, char* newValue){
	block* aux = current_block;
	strcpy(aux->cstroke, newValue);
}

char* get_cep(void* current_block){
	block* aux = current_block;
	return aux->cep; 
}

void set_cep(void* current_block, char* newValue){
	block* aux = current_block;
	strcpy(aux->cep, newValue);
}

int compare_cep(void* node, void* element){
	
	block* aux1 = node;

	if(!strcmp(aux1->cep, element)) return 1;

	return 0;	

}