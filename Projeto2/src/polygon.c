#include "polygon.h"

#include "circle.h"
#include "dynamicList.h"
#include "kdTree.h"
#include "normalTree.h"
#include "rectangle.h"
#include "segments.h"
#include "svg.h"
#include "system.h"

typedef struct point {
    
    double x, y, angle;
    void* linkedTo;
    void* pair;
    char type;
    int quadrant;
    double distance;
    char code[5];
    bool analyzed;

} point_t;

typedef struct segment {
    
    point_t* point1;
    point_t* point2;

} segment_t;

int collinear(double x1, double y1, double x2, double y2, double x3, double y3) {
    

    double a = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);

    if (a == 0.0) return 1;
    else return 0;

}


void storeShadowPolygons(tree shadowPolygons, void* vertexArray, dynamicList segmentsList, double xMeteor, double yMeteor) {
    
    point_t* auxVertex = vertexArray;
    point_t* extremes = calloc(4, sizeof(point_t));
    void* root = NTgetRootNode(shadowPolygons);
    int count = 0;
    double biggestX = 0;
    double biggestY = 0;

    for (int i = 0; i < getSize(segmentsList) * 2; i += 2) {
        
        if (!strcmp(auxVertex[i].code, "RE")) {
            
            extremes[count] = auxVertex[i];
            if (extremes[count].x > biggestX) {
                
                biggestX = extremes[count].x;
            }
            if (extremes[count].y > biggestY) {
                
                biggestY = extremes[count].y;
            }
            count++;
        }
    }

    for (int i = 0; i < getSize(segmentsList) * 2; i++) {
        
        if (!strcmp(auxVertex[i].code, "ORIG") && !strcmp(getCode(auxVertex[i].pair), "ORIG") && auxVertex[i].analyzed == false && getAnalyzed(auxVertex[i].pair) == false) {
            
            segment_t* segment = calloc(1, sizeof(segment_t));
            segment_t* sidesOfShadowPolygon = calloc(3, sizeof(segment_t));

            int horizontal = 0;
            int vertical = 0;

            if (auxVertex[i].y == getPointY(auxVertex[i].pair)) {
                  // the 2 points are horizontal

                horizontal = 1;

            } else if (auxVertex[i].x == getPointX(auxVertex[i].pair)) {
                  // the 2 points vertical

                vertical = 1;
            }

            if (vertical) {
                
                if (auxVertex[i].y < getPointY(auxVertex[i].pair)) {
                    
                    segment->point1 = calloc(1, sizeof(point_t));
                    *(segment->point1) = auxVertex[i];
                    
                    segment->point2 = calloc(1, sizeof(point_t));
                    segment->point2->x = getPointX(auxVertex[i].pair);
                    segment->point2->y = getPointY(auxVertex[i].pair);
                    strcpy(segment->point2->code, getCode(auxVertex[i].pair));
                    segment->point2->type = getPointType(auxVertex[i].pair);
                    segment->point2->angle = getAngle(auxVertex[i].pair);

                } else {
                    
                    segment->point2 = calloc(1, sizeof(point_t));
                    *(segment->point2) = auxVertex[i];
                    
                    segment->point1 = calloc(1, sizeof(point_t));
                    segment->point1->x = getPointX(auxVertex[i].pair);
                    segment->point1->y = getPointY(auxVertex[i].pair);
                    strcpy(segment->point1->code, getCode(auxVertex[i].pair));
                    segment->point1->type = getPointType(auxVertex[i].pair);
                    segment->point1->angle = getAngle(auxVertex[i].pair);
                }
            } else if (horizontal) {
                
                if (auxVertex[i].x < getPointX(auxVertex[i].pair)) {
                    
                    segment->point1 = calloc(1, sizeof(point_t));
                    *(segment->point1) = auxVertex[i];
                    
                    segment->point2 = calloc(1, sizeof(point_t));
                    segment->point2->x = getPointX(auxVertex[i].pair);
                    segment->point2->y = getPointY(auxVertex[i].pair);
                    strcpy(segment->point2->code, getCode(auxVertex[i].pair));
                    segment->point2->type = getPointType(auxVertex[i].pair);
                    segment->point2->angle = getAngle(auxVertex[i].pair);
                } else {
                    
                    segment->point2 = calloc(1, sizeof(point_t));
                    *(segment->point2) = auxVertex[i];
                    
                    segment->point1 = calloc(1, sizeof(point_t));
                    segment->point1->x = getPointX(auxVertex[i].pair);
                    segment->point1->y = getPointY(auxVertex[i].pair);
                    strcpy(segment->point1->code, getCode(auxVertex[i].pair));
                    segment->point1->type = getPointType(auxVertex[i].pair);
                    segment->point1->angle = getAngle(auxVertex[i].pair);
                }
            }

            int ok = 0;
            int ok1 = 0;
            int ok2 = 0;
            
            segment_t* wallPointSegPoint1 = calloc(1, sizeof(segment_t));

            if (strcmp(segment->point1->code, "RE") && strcmp(segment->point1->code, "DIV")) {
                
            
                if ((segment->point1->angle >= 0 && segment->point1->angle < extremes[0].angle) || (segment->point1->angle >= extremes[3].angle && segment->point1->angle <= 360)) {
                    
            
                    double dist = (((segment->point1->y - yMeteor) / (segment->point1->x - xMeteor)) * (biggestX - segment->point1->x)) + segment->point1->y;
            
                    wallPointSegPoint1->point1 = calloc(1, sizeof(point_t));
                    wallPointSegPoint1->point1->x = segment->point1->x;
                    wallPointSegPoint1->point1->y = segment->point1->y;
                    strcpy(wallPointSegPoint1->point1->code, segment->point1->code);
                    wallPointSegPoint1->point1->type = segment->point1->type;
                    wallPointSegPoint1->point1->angle = segment->point1->angle;
                    wallPointSegPoint1->point2 = calloc(1, sizeof(point_t));
                    wallPointSegPoint1->point2->x = biggestX;
                    wallPointSegPoint1->point2->y = dist;
                    ok1 = 1;

                } else if (segment->point1->angle >= extremes[0].angle && segment->point1->angle < extremes[1].angle) {
                    
                   
                    double dist = ((biggestY - segment->point1->y) / ((segment->point1->y - yMeteor) / (segment->point1->x - xMeteor))) + segment->point1->x;
                   
                    wallPointSegPoint1->point1 = calloc(1, sizeof(point_t));
                    wallPointSegPoint1->point1->x = segment->point1->x;
                    wallPointSegPoint1->point1->y = segment->point1->y;
                    strcpy(wallPointSegPoint1->point1->code, segment->point1->code);
                    wallPointSegPoint1->point1->type = segment->point1->type;
                    wallPointSegPoint1->point1->angle = segment->point1->angle;
                    wallPointSegPoint1->point2 = calloc(1, sizeof(point_t));
                    wallPointSegPoint1->point2->x = dist;
                    wallPointSegPoint1->point2->y = biggestY;
                    ok1 = 1;

                } else if (segment->point1->angle >= extremes[1].angle && segment->point1->angle < extremes[2].angle) {
                    
                   
                    double dist = (((segment->point1->y - yMeteor) / (segment->point1->x - xMeteor)) * (-100 - segment->point1->x)) + segment->point1->y;
                   
                    wallPointSegPoint1->point1 = calloc(1, sizeof(point_t));
                    wallPointSegPoint1->point1->x = segment->point1->x;
                    wallPointSegPoint1->point1->y = segment->point1->y;
                    strcpy(wallPointSegPoint1->point1->code, segment->point1->code);
                    wallPointSegPoint1->point1->type = segment->point1->type;
                    wallPointSegPoint1->point1->angle = segment->point1->angle;
                    wallPointSegPoint1->point2 = calloc(1, sizeof(point_t));
                    wallPointSegPoint1->point2->x = -100.0;
                    wallPointSegPoint1->point2->y = dist;
                    ok1 = 1;

                } else if (segment->point1->angle >= extremes[2].angle && segment->point1->angle < extremes[3].angle) {
                    
                   
                    double dist = ((- 100 - segment->point1->y) / ((segment->point1->y - yMeteor) / (segment->point1->x - xMeteor))) + segment->point1->x;
                   
                    wallPointSegPoint1->point1 = calloc(1, sizeof(point_t));
                    wallPointSegPoint1->point1->x = segment->point1->x;
                    wallPointSegPoint1->point1->y = segment->point1->y;
                    strcpy(wallPointSegPoint1->point1->code, segment->point1->code);
                    wallPointSegPoint1->point1->type = segment->point1->type;
                    wallPointSegPoint1->point1->angle = segment->point1->angle;

                    wallPointSegPoint1->point2 = calloc(1, sizeof(point_t));
                    wallPointSegPoint1->point2->x = dist;
                    wallPointSegPoint1->point2->y = -100.0;
                    ok1 = 1;
                }
            }

            segment_t* wallPointSegPoint2 = calloc(1, sizeof(segment_t));

            if (strcmp(segment->point2->code, "RE") && strcmp(segment->point2->code, "DIV")) {
                

                if ((segment->point2->angle >= 0 && segment->point2->angle < extremes[0].angle) || (segment->point2->angle >= extremes[3].angle && segment->point2->angle <= 360)) {
                    

                    double dist = (((segment->point2->y - yMeteor) / (segment->point2->x - xMeteor)) * (biggestX - segment->point2->x)) + segment->point2->y;

                    wallPointSegPoint2->point1 = calloc(1, sizeof(point_t));
                    wallPointSegPoint2->point1->x = segment->point2->x;
                    wallPointSegPoint2->point1->y = segment->point2->y;
                    strcpy(wallPointSegPoint2->point1->code, segment->point2->code);
                    wallPointSegPoint2->point1->type = segment->point2->type;
                    wallPointSegPoint2->point1->angle = segment->point2->angle;

                    wallPointSegPoint2->point2 = calloc(1, sizeof(point_t));
                    wallPointSegPoint2->point2->x = biggestX;
                    wallPointSegPoint2->point2->y = dist;
                    ok2 = 1;

                } else if (segment->point2->angle >= extremes[0].angle && segment->point2->angle < extremes[1].angle) {
                    

                    double dist = ((biggestY - segment->point2->y) / ((segment->point2->y - yMeteor) / (segment->point2->x - xMeteor))) + segment->point2->x;


                    wallPointSegPoint2->point1 = calloc(1, sizeof(point_t));
                    wallPointSegPoint2->point1->x = segment->point2->x;
                    wallPointSegPoint2->point1->y = segment->point2->y;
                    strcpy(wallPointSegPoint2->point1->code, segment->point2->code);
                    wallPointSegPoint2->point1->type = segment->point2->type;
                    wallPointSegPoint2->point1->angle = segment->point2->angle;

                    wallPointSegPoint2->point2 = calloc(1, sizeof(point_t));
                    wallPointSegPoint2->point2->x = dist;
                    wallPointSegPoint2->point2->y = biggestY;
                    ok2 = 1;

                } else if (segment->point2->angle >= extremes[1].angle && segment->point2->angle < extremes[2].angle) {
                    

                    double dist = (((segment->point2->y - yMeteor) / (segment->point2->x - xMeteor)) * (-100 - segment->point2->x)) + segment->point2->y;


                    wallPointSegPoint2->point1 = calloc(1, sizeof(point_t));
                    wallPointSegPoint2->point1->x = segment->point2->x;
                    wallPointSegPoint2->point1->y = segment->point2->y;
                    strcpy(wallPointSegPoint2->point1->code, segment->point2->code);
                    wallPointSegPoint2->point1->type = segment->point2->type;
                    wallPointSegPoint2->point1->angle = segment->point2->angle;

                    wallPointSegPoint2->point2 = calloc(1, sizeof(point_t));
                    wallPointSegPoint2->point2->x = -100.0;
                    wallPointSegPoint2->point2->y = dist;
                    ok2 = 1;

                } else if (segment->point2->angle >= extremes[2].angle && segment->point2->angle < extremes[3].angle) {
                    

                    double dist = ((-100 - segment->point2->y) / ((segment->point2->y - yMeteor) / (segment->point2->x - xMeteor))) + segment->point2->x;


                    wallPointSegPoint2->point1 = calloc(1, sizeof(point_t));
                    wallPointSegPoint2->point1->x = segment->point2->x;
                    wallPointSegPoint2->point1->y = segment->point2->y;
                    strcpy(wallPointSegPoint2->point1->code, segment->point2->code);
                    wallPointSegPoint2->point1->type = segment->point2->type;
                    wallPointSegPoint2->point1->angle = segment->point2->angle;

                    wallPointSegPoint2->point2 = calloc(1, sizeof(point_t));
                    wallPointSegPoint2->point2->x = dist;
                    wallPointSegPoint2->point2->y = -100.0;
                    ok2 = 1;
                }
            }

            if (!ok1) puts("OK1 fail");
            if (!ok2) puts("OK2 fail");

            if(!collinear(segment->point1->x, segment->point1->y, wallPointSegPoint1->point2->x, wallPointSegPoint1->point2->y, wallPointSegPoint2->point2->x, wallPointSegPoint2->point2->y)){
                
                sidesOfShadowPolygon[0] = *(segment);
                sidesOfShadowPolygon[1] = *(wallPointSegPoint1);
                sidesOfShadowPolygon[2] = *(wallPointSegPoint2);


                (!root) ? root = NTinsertShadow(shadowPolygons, root, root, sidesOfShadowPolygon) : NTinsertShadow(shadowPolygons, root, root, sidesOfShadowPolygon);
                
            }
            
            free(segment);

            free(wallPointSegPoint1);

            free(wallPointSegPoint2);

            setAnalyzed(auxVertex[i].pair, true);
            setAnalyzed(getPair(auxVertex[i].pair), true);

        }
    }

    NTsetRootNode(shadowPolygons, root);
    free(extremes);
}

double getMinimumX(void* listOfSegmentsShadowPolygon) {
    

    segment_t* polygon = listOfSegmentsShadowPolygon;

    double min = DBL_MAX;

    for (int i = 0; i < 3; i++) {
        

        double smaller;
        
        if(polygon[i].point1->x < polygon[i].point2->x){
            smaller = polygon[i].point1->x;
        }else{
            smaller = polygon[i].point2->x;
        }
        if (smaller < min) {
            
            min = smaller;
        }
    }
    
    if(min < polygon[0].point1->x){
        min = -100;
    }

    return min;
}

void getShadows(tree shadows, node current, FILE* aux) {
    
    if (current) {
        
        getShadows(shadows, NTgetLeftNode(current), aux);
        segment_t* wow = NTgetData(current);
        for (int i = 0; i < 3; i++) {
            
            fprintf(aux, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" stroke=\"red\" stroke-width=\".3\"/>\n", wow[i].point1->x, wow[i].point1->y, wow[i].point2->x, wow[i].point2->y);
            
        }
        getShadows(shadows, NTgetRightNode(current), aux);
    }
}

void printSvgShadows(tree shadows, double biggestX, double biggestY) {
    
    FILE* aux = fopen("Testesombras.svg", "w+");
    setvbuf(aux, 0, _IONBF, 0);
    fprintf(aux, "<svg viewbox=\"0 0 %.2lf %.2lf\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" width=\"100%%\" height=\"100%%\">\n", biggestX, biggestY);
    getShadows(shadows, NTgetRootNode(shadows), aux);
    fprintf(aux, "</svg>");

    fclose(aux);
}