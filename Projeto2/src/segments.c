#include "segments.h"

#include "circle.h"
#include "dynamicList.h"
#include "kdTree.h"
#include "normalTree.h"
#include "rectangle.h"
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

void* getP1(void* segment) {
    segment_t* aux = segment;
    return aux->point1;
}

void* getP2(void* segment) {
    segment_t* aux = segment;
    return aux->point2;
}

void* createSegment() {
    segment_t* aux = calloc(1, sizeof(segment_t));
    return aux;
}

void* createPoint() {
    point_t* aux = calloc(1, sizeof(point_t));
    aux->angle = 0;
    aux->linkedTo = NULL;
    aux->analyzed = false;
    return aux;
}

void* getLinkedTo(void* point) {
    point_t* aux = point;
    return aux->linkedTo;
}

int compareForQSort(const void* a, const void* b) {
    const point_t* tempA = (point_t*)a;
    const point_t* tempB = (point_t*)b;

    if (tempA->angle > tempB->angle) return 1;
    else if (tempA->angle < tempB->angle) return -1;
    else if (tempA->distance > tempB->distance) return -1;
    else if (tempA->distance < tempB->distance) return 1;
    else if (tempA->type == 's' && tempB->type == 'e') return -1;
    else if (tempA->type == 'e' && tempB->type == 's') return 1;
    
    return 0;
}

void buildSegments(tree rectangleTree, dynamicList segmentsList, void* current_rect) {
    if (current_rect) {
        buildSegments(rectangleTree, segmentsList, KDgetLeftNode(current_rect));

        if (KDgetState(current_rect)) {

            segment_t* segment1 = calloc(1, sizeof(segment_t));
            segment1->point1 = calloc(1, sizeof(point_t));
            segment1->point2 = calloc(1, sizeof(point_t));

            segment_t* segment2 = calloc(1, sizeof(segment_t));
            segment2->point1 = calloc(1, sizeof(point_t));
            segment2->point2 = calloc(1, sizeof(point_t));

            segment_t* segment3 = calloc(1, sizeof(segment_t));
            segment3->point1 = calloc(1, sizeof(point_t));
            segment3->point2 = calloc(1, sizeof(point_t));

            segment_t* segment4 = calloc(1, sizeof(segment_t));
            segment4->point1 = calloc(1, sizeof(point_t));
            segment4->point2 = calloc(1, sizeof(point_t));

            segment1->point1->x = getRectangleX(KDgetData(current_rect));
            segment1->point1->y = getRectangleY(KDgetData(current_rect));
            segment1->point2->x = getRectangleX(KDgetData(current_rect)) + getRectangleWidth(KDgetData(current_rect));
            segment1->point2->y = getRectangleY(KDgetData(current_rect));
            segment1->point1->linkedTo = segment1;
            segment1->point2->linkedTo = segment1;
            segment1->point1->pair = segment1->point2;
            segment1->point2->pair = segment1->point1;
            strcpy(segment1->point1->code, "ORIG");
            strcpy(segment1->point2->code, "ORIG");

            segment2->point1->x = getRectangleX(KDgetData(current_rect)) + getRectangleWidth(KDgetData(current_rect));
            segment2->point1->y = getRectangleY(KDgetData(current_rect));
            segment2->point2->x = getRectangleX(KDgetData(current_rect)) + getRectangleWidth(KDgetData(current_rect));
            segment2->point2->y = getRectangleY(KDgetData(current_rect)) + getRectangleHeight(KDgetData(current_rect));
            segment2->point1->linkedTo = segment2;
            segment2->point2->linkedTo = segment2;
            segment2->point1->pair = segment2->point2;
            segment2->point2->pair = segment2->point1;
            strcpy(segment2->point1->code, "ORIG");
            strcpy(segment2->point2->code, "ORIG");

            segment3->point1->x = getRectangleX(KDgetData(current_rect)) + getRectangleWidth(KDgetData(current_rect));
            segment3->point1->y = getRectangleY(KDgetData(current_rect)) + getRectangleHeight(KDgetData(current_rect));
            segment3->point2->x = getRectangleX(KDgetData(current_rect));
            segment3->point2->y = getRectangleY(KDgetData(current_rect)) + getRectangleHeight(KDgetData(current_rect));
            segment3->point1->linkedTo = segment3;
            segment3->point2->linkedTo = segment3;
            segment3->point1->pair = segment3->point2;
            segment3->point2->pair = segment3->point1;
            strcpy(segment3->point1->code, "ORIG");
            strcpy(segment3->point2->code, "ORIG");

            segment4->point1->x = getRectangleX(KDgetData(current_rect));
            segment4->point1->y = getRectangleY(KDgetData(current_rect)) + getRectangleHeight(KDgetData(current_rect));
            segment4->point2->x = getRectangleX(KDgetData(current_rect));
            segment4->point2->y = getRectangleY(KDgetData(current_rect));
            segment4->point1->linkedTo = segment4;
            segment4->point2->linkedTo = segment4;
            segment4->point1->pair = segment4->point2;
            segment4->point2->pair = segment4->point1;
            strcpy(segment4->point1->code, "ORIG");
            strcpy(segment4->point2->code, "ORIG");

            insert(segmentsList, segment1);
            insert(segmentsList, segment2);
            insert(segmentsList, segment3);
            insert(segmentsList, segment4);
        }
        buildSegments(rectangleTree, segmentsList, KDgetRightNode(current_rect));
    }
}

void addWrapAroundRectangle(tree rectangleTree, tree circleTree, dynamicList segmentsList) {
    segment_t* aux1 = calloc(1, sizeof(segment_t));
    aux1->point1 = calloc(1, sizeof(point_t));
    aux1->point2 = calloc(1, sizeof(point_t));

    segment_t* aux2 = calloc(1, sizeof(segment_t));
    aux2->point1 = calloc(1, sizeof(point_t));
    aux2->point2 = calloc(1, sizeof(point_t));

    segment_t* aux3 = calloc(1, sizeof(segment_t));
    aux3->point1 = calloc(1, sizeof(point_t));
    aux3->point2 = calloc(1, sizeof(point_t));

    segment_t* aux4 = calloc(1, sizeof(segment_t));
    aux4->point1 = calloc(1, sizeof(point_t));
    aux4->point2 = calloc(1, sizeof(point_t));

    aux1->point1->x = -100;
    aux1->point1->y = -100;
    aux1->point2->x = max(getBiggestX(rectangleTree), getBiggestX(circleTree)) + 100;
    aux1->point2->y = -100;
    aux1->point1->linkedTo = aux1;
    aux1->point2->linkedTo = aux1;
    aux1->point1->pair = aux1->point2;
    aux1->point2->pair = aux1->point1;
    strcpy(aux1->point1->code, "RE");
    strcpy(aux1->point2->code, "RE");

    aux2->point1->x = max(getBiggestX(rectangleTree), getBiggestX(circleTree)) + 100;
    aux2->point1->y = -100;
    aux2->point2->x = max(getBiggestX(rectangleTree), getBiggestX(circleTree)) + 100;
    aux2->point2->y = max(getBiggestY(rectangleTree), getBiggestY(circleTree)) + 100;
    aux2->point1->linkedTo = aux2;
    aux2->point2->linkedTo = aux2;
    aux2->point1->pair = aux2->point2;
    aux2->point2->pair = aux2->point1;
    strcpy(aux2->point1->code, "RE");
    strcpy(aux2->point2->code, "RE");

    aux3->point1->x = max(getBiggestX(rectangleTree), getBiggestX(circleTree)) + 100;
    aux3->point1->y = max(getBiggestY(rectangleTree), getBiggestY(circleTree)) + 100;
    aux3->point2->x = -100;
    aux3->point2->y = max(getBiggestY(rectangleTree), getBiggestY(circleTree)) + 100;
    aux3->point1->linkedTo = aux3;
    aux3->point2->linkedTo = aux3;
    aux3->point1->pair = aux3->point2;
    aux3->point2->pair = aux3->point1;
    strcpy(aux3->point1->code, "RE");
    strcpy(aux3->point2->code, "RE");

    aux4->point1->x = -100;
    aux4->point1->y = max(getBiggestY(rectangleTree), getBiggestY(circleTree)) + 100;
    aux4->point2->x = -100;
    aux4->point2->y = -100;
    aux4->point1->linkedTo = aux4;
    aux4->point2->linkedTo = aux4;
    aux4->point1->pair = aux4->point2;
    aux4->point2->pair = aux4->point1;
    strcpy(aux4->point1->code, "RE");
    strcpy(aux4->point2->code, "RE");

    insert(segmentsList, aux1);
    insert(segmentsList, aux2);
    insert(segmentsList, aux3);
    insert(segmentsList, aux4);

}

void* buildVertexArray(dynamicList segmentsList, double xMeteor, double yMeteor) {
    point_t* aux = calloc(2 * getSize(segmentsList), sizeof(point_t));
    void* pos = getHead(segmentsList);
    for (int i = 0; i < getSize(segmentsList) * 2; i += 2) {
        segment_t* dataAux = getItem(segmentsList, pos);
        pos = getNext(segmentsList, pos);

        if (fabs(xMeteor - dataAux->point1->x) == 0) {
            dataAux->point1->angle = 0;
        } else {
            dataAux->point1->angle = (atan(fabs(yMeteor - dataAux->point1->y) / fabs(xMeteor - dataAux->point1->x))) * (180 / PI);
        }

        dataAux->point1->distance = sqrt(pow(dataAux->point1->x - xMeteor, 2) + pow(dataAux->point1->y - yMeteor, 2));

        if (fabs(xMeteor - dataAux->point2->x) == 0) {
            dataAux->point2->angle = 0;
        } else {
            dataAux->point2->angle = (atan(fabs(yMeteor - dataAux->point2->y) / fabs(xMeteor - dataAux->point2->x))) * (180 / PI);
        }

        dataAux->point2->distance = sqrt(pow(dataAux->point2->x - xMeteor, 2) + pow(dataAux->point2->y - yMeteor, 2));

        if (dataAux->point1->x < xMeteor) {
            if (dataAux->point1->y < yMeteor) {  //Third quadrant

                dataAux->point1->angle += 180;
                dataAux->point1->quadrant = 3;

            } else if (dataAux->point1->y > yMeteor) {  //Second quadrant

                dataAux->point1->angle = 180 - dataAux->point1->angle;
                dataAux->point1->quadrant = 2;
            }

        } else if (dataAux->point1->x >= xMeteor) {
            if (dataAux->point1->y < yMeteor) {  //Fourth quadrant

                dataAux->point1->angle = 360 - dataAux->point1->angle;
                dataAux->point1->quadrant = 4;

            } else if (dataAux->point1->y >= yMeteor) {  //First quadrant

                dataAux->point1->quadrant = 1;
            }
        }

        if (dataAux->point2->x < xMeteor) {
            if (dataAux->point2->y < yMeteor) {  //Third quadrant

                dataAux->point2->angle += 180;
                dataAux->point2->quadrant = 3;

            } else if (dataAux->point2->y > yMeteor) {  //Second quadrant

                dataAux->point2->angle = 180 - dataAux->point2->angle;
                dataAux->point2->quadrant = 2;
            }

        } else if (dataAux->point2->x >= xMeteor) {
            if (dataAux->point2->y < yMeteor) {  //Fourth quadrant

                dataAux->point2->angle = 360 - dataAux->point2->angle;
                dataAux->point2->quadrant = 4;

            } else if (dataAux->point2->y >= yMeteor) {  //First quadrant

                dataAux->point2->quadrant = 1;
            }
        }
       
        switch (dataAux->point1->quadrant) {
            case 1:

                switch (dataAux->point2->quadrant) {
                    case 1:

                        if (dataAux->point1->angle > dataAux->point2->angle) {
                            dataAux->point1->type = 'e';
                            dataAux->point2->type = 's';
                        } else if (dataAux->point1->angle < dataAux->point2->angle) {
                            dataAux->point1->type = 's';
                            dataAux->point2->type = 'e';
                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';
                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;

                    case 2:
                        if (dataAux->point1->angle < dataAux->point2->angle) {
                            dataAux->point1->type = 's';
                            dataAux->point2->type = 'e';
                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';
                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;

                    case 3:
                        //Impossible !
                        break;

                    case 4:
                        if (dataAux->point1->angle < dataAux->point2->angle) {
                            dataAux->point1->type = 'e';
                            dataAux->point2->type = 's';
                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';
                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;
                }

                break;

            case 2:

                switch (dataAux->point2->quadrant) {
                    case 1:
                        if (dataAux->point1->angle > dataAux->point2->angle) {
                            dataAux->point1->type = 'e';
                            dataAux->point2->type = 's';
                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';
                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;

                    case 2:
                        if (dataAux->point1->angle > dataAux->point2->angle) {
                            dataAux->point1->type = 'e';
                            dataAux->point2->type = 's';
                        } else if (dataAux->point1->angle < dataAux->point2->angle) {
                            dataAux->point1->type = 's';
                            dataAux->point2->type = 'e';
                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';
                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;

                    case 3:
                        if (dataAux->point1->angle < dataAux->point2->angle) {
                            dataAux->point1->type = 's';
                            dataAux->point2->type = 'e';
                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';
                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;

                    case 4:
                        //Impossible !
                        break;
                }

                break;

            case 3:

                switch (dataAux->point2->quadrant) {
                    case 1:
                        //Impossible !
                        break;

                    case 2:
                        if (dataAux->point1->angle > dataAux->point2->angle) {
                            dataAux->point1->type = 'e';
                            dataAux->point2->type = 's';
                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';
                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;

                    case 3:
                        if (dataAux->point1->angle > dataAux->point2->angle) {
                            dataAux->point1->type = 'e';
                            dataAux->point2->type = 's';
                        } else if (dataAux->point1->angle < dataAux->point2->angle) {
                            dataAux->point1->type = 's';
                            dataAux->point2->type = 'e';
                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';
                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;

                    case 4:
                        if (dataAux->point1->angle < dataAux->point2->angle) {
                            dataAux->point1->type = 's';
                            dataAux->point2->type = 'e';
                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';
                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;
                }

                break;

            case 4:

                switch (dataAux->point2->quadrant) {
                    case 1:
                        if (dataAux->point1->angle > dataAux->point2->angle) {
                            dataAux->point1->type = 's';
                            dataAux->point2->type = 'e';
                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';
                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;

                    case 2:
                        //Impossible !
                        break;

                    case 3:
                        if (dataAux->point1->angle > dataAux->point2->angle) {
                            dataAux->point1->type = 'e';
                            dataAux->point2->type = 's';
                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';
                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;

                    case 4:
                        if (dataAux->point1->angle > dataAux->point2->angle) {
                            dataAux->point1->type = 'e';
                            dataAux->point2->type = 's';
                        } else if (dataAux->point1->angle < dataAux->point2->angle) {
                            dataAux->point1->type = 's';
                            dataAux->point2->type = 'e';
                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';
                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;
                }

                break;
        }
        //============================================================================
        
        aux[i] = *(dataAux->point1);
        aux[i + 1] = *(dataAux->point2);
        
    }
    
    qsort(aux, 2 * getSize(segmentsList), sizeof(point_t), compareForQSort);
    
    return aux;
}

double getPointX(void* point) {
    point_t* aux = point;
    return aux->x;
}

double getPointY(void* point) {
    point_t* aux = point;
    return aux->y;
}

char* getCode(void* point) {
    point_t* aux = point;
    return aux->code;
}

char getPointType(void* point) {
    point_t* aux = point;
    return aux->type;
}

double getAngle(void* point) {
    point_t* aux = point;
    return aux->angle;
}

int getQuadrant(void* point) {
    point_t* aux = point;
    return aux->quadrant;
}

void* getOrigin(void* point) {
    point_t* aux = point;
    return aux->linkedTo;
}

bool getAnalyzed(void* point) {
    point_t* aux = point;
    return aux->analyzed;
}

void* atPosArray(void* array, int pos) {
    segment_t* aux = array;
    return &aux[pos];
}

void* getPair(void* point) {
    point_t* aux = point;
    return aux->pair;
}

void setAnalyzed(void* point, bool state) {
    point_t* aux = point;
    aux->analyzed = state;
}

void freePointsInfo(void* segment) {
    if (segment != NULL) {
        segment_t* aux = segment;
        if (aux->point1) {
            free(aux->point1);
        }
        if (aux->point2) {
            free(aux->point2);
        }
    }
}

void destorySegment(void* segment) {
    segment_t* aux = segment;
    free(aux->point1);
    free(aux->point2);
    free(aux);
}

void setAngle(void* point, double angle) {
    point_t* aux = point;
    aux->angle = angle;
}

void freeShadowPolygonsArray(void* array) {
    segment_t* aux = array;
    for (int i = 0; i < 3; i++) {
        
        free(aux[i].point1);
        free(aux[i].point2);
        
    }
}
