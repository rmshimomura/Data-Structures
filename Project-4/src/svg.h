#include "libs.h"

#ifndef SVG_H
#define SVG_H

void print_on_SVG(void* connections, void* blocks, void* view_box, path paths);
void recursive_print_svg(void* root, FILE* original_svg);
void print_graph(void* connections, FILE* original_svg);

#endif