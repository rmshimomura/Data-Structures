#include "libs.h"

#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED

void print_on_SVG(tree blocks, path paths);
void recursive_print_svg(void* root, FILE* original_svg);
void position_cases_loc_who(hash blocks_hash, void* location_data, FILE* modified_SVG, char character_to_print);


#endif