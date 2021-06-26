#include "bibliotecas.h"

#ifndef QRY_H
#define QRY_H

void dr(tree rectangleTree, char* id, path paths);
void dpi(tree rectangleTree, double x, double y, path paths);
int inside(double x1, double y1, double p1Width, double p1Height, double x2, double y2, double p2Width, double p2Height);
void fg(tree rectangleTree, tree circleTree, double x, double y, double radius, path paths, dynamicList tempInfo);
void im(tree rectangleTree, tree circleTree, dynamicList listOfTreesShadows, double xMeteor, double yMeteor, double radiation, path paths, dynamicList tempInfo);
void t30(tree circleTree, path paths);
void nve(dynamicList listOfTreesShadows, path paths, double x, double y, dynamicList tempInfo);

#endif
