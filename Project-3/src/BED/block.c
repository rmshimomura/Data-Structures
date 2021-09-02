#include "block.h"

typedef struct block {

    double x;
    double y;
    double w;
    double h;
    double sw;
    char* cfill;
    char* cstroke;

} block;

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
	aux->cfill = newValue;
}

char* get_cstroke(void* current_block){
	block* aux = current_block;
	return aux->cstroke; 
}

void set_cstroke(void* current_block, char* newValue){
	block* aux = current_block;
	aux->cstroke = newValue;
}

