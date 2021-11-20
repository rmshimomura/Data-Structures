#include "libs.h"

#ifndef QRY_H
#define QRY_H

void catac(void* connections, void* blocks, double x, double y, double w, double h, void* point_location, FILE* txt_results, void* list_of_modifications); // catac
void* find_position(void* connections, void* blocks_hash, char* cep, char face, int num, FILE* txt_results, void* list_of_modifications); // @o?
void free_point(void* data);

#endif