#include "libs.h"

#ifndef QRY_H
#define QRY_H

int inside(double x1, double y1, double p1_width, double p1_height, double x2, double y2, double p2_width, double p2_height);

void catac(void* connections, void* blocks, double x, double y, double w, double h, void* point_location, FILE* txt_results, void* list_of_modifications); // catac
void* find_position(void* connections, void* blocks_hash, char* cep, char face, int num, FILE* txt_results, void* list_of_modifications); // @o?
void rv(void* connections, double x, double y, double w, double h, double f, FILE* txt_results, void* list_of_modifications); // rv
void cx(void* connections, double threshold, FILE* txt_results, void* list_of_modifications); // cx
void route(void* connections, void* blocks_hash, char* cep, char face, int num, char* cmc, char* cmr, void* departure, FILE* txt_results, void* list_of_modifications); // p?
void free_point(void* data);

#endif