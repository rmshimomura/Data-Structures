#include "block.h"
#include "DynamicList/dynamicList.h"

typedef struct block {

    double x;
    double y;
    double w;
    double h;
    double sw;
    char cfill[30];
	char cep[20];
    char cstroke[30];
	void* persons_living;

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
	new_block->persons_living = create_list();
	return new_block;
}

void add_resident(void* block_data, void* person){
	
	block* new_block = block_data;
	insert_list(new_block->persons_living, person);
	
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

int compare_x(void* node, void* element)	{
	
	block* aux1 = node;
	block* aux2 = element;

	if(aux2->x > aux1->x) return 1;

	else if(aux2->x < aux1->x) return -1;

	else return 0;

}

int compare_cep(void* node, void* element){
	
	block* aux1 = node;
	block* aux2 = element;

	if(!strcmp(aux1->cep, aux2->cep)) return 1;

	return 0;
	

}