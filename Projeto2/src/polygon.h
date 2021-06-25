#include "bibliotecas.h"

#ifndef POLYGON_H
#define POLYGON_H
    
    double getMinimumX(dynamicList listOfSegmentsShadowPolygon);
    void storeShadowPolygons(tree shadowPolygons, void* vertexArray, dynamicList segmentsList, double xMeteor, double yMeteor);
    void getShadows(tree shadows, node current, FILE* aux);
    void printSvgShadows(tree shadows, double biggestX, double biggestY);

#endif