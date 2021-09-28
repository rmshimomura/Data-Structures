#include "libs.h"

#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED

void print_on_SVG(tree blocks, path paths);
void recursive_print_svg(void* root, FILE* original_svg);
void position_cases_text(hash blocks_hash, void* location_data, void* list_of_modifications, char character_to_print);
void position_cases_line(void* old_square, void* new_square, char face, int num, void* person_info, void* list_of_modifications);
void insert_modifications(void* person_data, void* square, char* cpf, void* list_of_modifications);

#endif