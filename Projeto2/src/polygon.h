#include "bibliotecas.h"

#ifndef POLYGON_H
#define POLYGON_H

double get_minimum_x(dynamicList listOfSegmentsShadowPolygon);
void store_shadow_polygons(tree shadowPolygons, void* vertexArray, dynamicList segmentsList, double xMeteor, double yMeteor);
void get_shadows(tree shadows, node current, FILE* aux);
void print_svg_shadows(tree shadows, double biggestX, double biggestY);

#endif