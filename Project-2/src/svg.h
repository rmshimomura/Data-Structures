#include "bibliotecas.h"
#ifndef SVG_H
#define SVG_H

void write_on_svg(FILE* svg_source, tree rectTree, tree circleTree, path paths);
void new_write_on_svg(FILE* svg_source, tree rectTree, tree circleTree, path paths, dynamicList fgData, dynamicList imData, dynamicList nveData);
void print_rectangle_in_order(FILE* svg_source, tree initialTree, node current);
void print_circle_in_order(FILE* svg_source, tree initialTree, node current);
double max(double x1, double x2);

#endif