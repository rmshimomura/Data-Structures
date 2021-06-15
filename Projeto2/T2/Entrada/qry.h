#include "bibliotecas.h"

#ifndef QRY_H
#define QRY_H

void dr(tree rectangleTree, char* id, path paths);
void dpi(tree rectangleTree, double x, double y, path paths);
int inside(double x1, double y1, double p1Width, double p1Height, double x2, double y2, double p2Width, double p2Height);
void dpiInOrder(tree rectangleTree, node currentNode, double x, double y, char** names, int* index);
void fgInOrderRectangle(tree rectangleTree, FILE* results, void* current_rect, void* current_circ);
void fgInOrderCircle(tree rectangleTree, tree circleTree, FILE* results, void* current_rect, void* current_circ, double x, double y, double radius);
void fg(tree rectangleTree, tree circleTree, double x, double y, double radius, path paths);
void stopEveryone(tree circleTree, void* current_circle);
void writeFgresults(tree rectangleTree, FILE* results, void* current_rect, double x, double y, double radius);
void im(tree rectangleTree, tree circleTree, dynamicList listOfTreesShadows, double xMeteor, double yMeteor, double radiation, path paths);
void imInOrderShadows(tree shadows, node currentShadowPolygon, node currentCircle, double xMeteor, double yMeteor);
void t30InOrderT30(tree circleTree, node currentCircle, FILE* results);
void t30(tree circleTree, path paths);
void nveInOrder(tree shadowTree, node currentListPosition, node currentPolygon, int* insideNPolygons, double x, double y, double xMeteor, double yMeteor);
void nve(dynamicList listOfTreesShadows, path paths, double x, double y);
void nveUpdateRadiation(void* currentPolygon, double x, double y, int* inside_polygons, double xMeteor, double yMeteor);
#endif
