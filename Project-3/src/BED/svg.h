#include "libs.h"

#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED

void print_on_SVG(tree blocks, path paths);
void recursive_print_svg(void* root, FILE* original_svg);

#endif