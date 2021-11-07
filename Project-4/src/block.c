#include "block.h"
#include "Dynamic_list/dynamic_list.h"

typedef struct block {

    double x;
    double y;
    double w;
    double h;
    char sw[10];
    char cfill[30];
	char cep[50];
    char cstroke[30];

} block;

void set_block_properties(void* block_to_set, char* cep, double x, double y, double w, double h, char* sw, char* cfill, char* cstroke){
	
	block* aux = block_to_set;
	aux->x = x;
	aux->y = y;
	aux->w = w;
	aux->h = h;
	strcpy(aux->sw, sw);
	strcpy(aux->cep, cep);
	strcpy(aux->cfill, cfill);
	strcpy(aux->cstroke, cstroke);
	
}

void* create_block(){

	block* new_block = calloc(1, sizeof(block));
	return new_block;

}

void free_single_block(void* block_data){
	
	block* block_to_remove = block_data;
	free(block_to_remove);

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

char* get_sw(void* current_block){
	block* aux = current_block;
	return aux->sw; 
}

void set_sw(void* current_block, char* newValue){
	block* aux = current_block;
	strcpy(aux->sw, newValue);
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
	if(aux1 && element){
		if(aux1->cep){
			if(!strcmp(aux1->cep, element)) return 1;
		}
	}

	return 0;	

}