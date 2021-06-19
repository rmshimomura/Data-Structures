#include "bibliotecas.h"
#ifndef SVG_H
#define SVG_H   

void writeOnSvg(FILE* svg_source, tree rectTree, tree circleTree, path paths);
void new_writeOnSvg(FILE* svg_source, tree rectTree, tree circleTree, path paths, dynamicList fgData, dynamicList imData, dynamicList nveData);
void printRectangleInOrder(FILE* svg_source, tree initialTree, node current);
void printCircleInOrder(FILE* svg_source, tree initialTree, node current);
double max(double x1, double x2);


#endif