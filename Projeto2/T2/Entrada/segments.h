#include "bibliotecas.h"
#ifndef SEGMENTS_H
#define SEGMENTS_H

void* createSegment();
void constructPoints(tree rectangleTree, node current_rect, dynamicList vertexList);
void calculateAngles(tree rectangleTree, dynamicList vertexList, double xMeteor, double yMeteor);
void* buildVertexArray(dynamicList segmentsList, double xMeteor, double yMeteor);
void buildSegments(tree rectangleTree, dynamicList segmentsList, void* current_rect);
void checkNewDivisions(dynamicList segmentsList, double xMeteor, double yMeteor);
void* buildArrayOfPoints(tree rectangleTree, dynamicList vertexList);
void resetAngles(dynamicList vertexList);
void freePointsInfo(void* segment);
void* getOrigin(void* point);
void* getLinkedTo(void* point);
double getPointX(void* point);
double getPointY(void* point);
double getAngle(void* point);
void* getP1(void* segment);
void* getP2(void* segment);
void* atPosArray(void* array, int pos);
void setAngle(void* point, double angle);
int getQuadrant(void* point);
char* getCode(void* point);
char getPointType(void* point);
bool getAnalyzed(void* point);
void setAnalyzed(void* point, bool state);
void freeShadowPolygonsArray(void* array);
void* getPair(void* point);
void constructTempSVG(void* vertexArray, dynamicList segmentsList);  //Debug
void buildLines(void* vertexArray, dynamicList segmentsList, double xMeteor, double yMeteor, double biggestX, double biggestY);
void addWrapAroundRectangle(tree rectangleTree, tree circleTree, dynamicList segmentsList);
void destorySegment(void* segment);

#endif