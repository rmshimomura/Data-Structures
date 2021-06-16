#include "qry.h"

#include "bibliotecas.h"
#include "circle.h"
#include "dynamicList.h"
#include "kdTree.h"
#include "normalTree.h"
#include "polygon.h"
#include "rectangle.h"
#include "segments.h"
#include "system.h"

typedef struct data {
    char rectName[100];
    void** peopleInside;
    void* originalRect;
    int numberOfPeopleInside;
} data_s;

typedef struct sorting {
    data_s* data;
    int size;
} sorting_t;

typedef struct circleData{
    char circleName[100];
    double radiation;
}circle_data_t;

typedef struct imSorting{
    circle_data_t* data;
    int pos;
}imSorting_t;

int sortingNamesRectangle(const void* pos1, const void* pos2) {
    const data_s* aux1 = pos1;
    const data_s* aux2 = pos2;
    return strcmp(aux1->rectName, aux2->rectName);
}

int sortingNamesCircle(const void* pos1, const void* pos2) {
    const circle_data_t* aux1 = pos1;
    const circle_data_t* aux2 = pos2;
    return strcmp(aux1->circleName, aux2->circleName);
}


int sortNames(const void* name1, const void* name2) {
    return strcmp(*(const char**)name1, *(const char**)name2);
}

int inside(double x1, double y1, double p1Width, double p1Height, double x2, double y2, double p2Width, double p2Height) {
    if ((x1 >= x2 && x1 <= x2 + p2Width && y1 >= y2 && y1 <= y2 + p2Height && x1 + p1Width <= x2 + p2Width && y1 + p1Height <= y2 + p2Height)) return 1;

    return 0;
}

int get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y, float p2_x, float p2_y, float p3_x, float p3_y) {
    float s1_x, s1_y, s2_x, s2_y;
    s1_x = p1_x - p0_x;
    s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;
    s2_y = p3_y - p2_y;

    float s, t;
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
        return 1;
    }

    return 0;
}

void dpiInOrder(tree rectangleTree, node currentNode, double x, double y, char** names, int* index) {
    
    if (currentNode) {
        
        dpiInOrder(rectangleTree, KDgetLeftNode(currentNode), x, y, names, index);

        if (inside(x, y, 0, 0, getRectangleX(KDgetData(currentNode)), getRectangleY(KDgetData(currentNode)), getRectangleWidth(KDgetData(currentNode)), getRectangleHeight(KDgetData(currentNode))) && KDgetState(currentNode)) {
            names[*index] = calloc(strlen(getRectangleId(KDgetData(currentNode))) + 1, sizeof(char));
            strcpy(names[*index], getRectangleId(KDgetData(currentNode))); 
            KDsetState(currentNode, 0);
            KDsetSize(rectangleTree, KDgetSize(rectangleTree) - 1);
            *index = *index + 1;
        }

        dpiInOrder(rectangleTree, KDgetRightNode(currentNode), x, y, names, index);
    }
}



void dpi(tree rectangleTree, double x, double y, path paths) {
    FILE* results = fopen(getPathDoTXTComOQryExecutado(paths), "a+");
    setvbuf(results, 0, _IONBF, 0);
    int size = KDgetSize(rectangleTree);

    int pos = 0;
    char** names = calloc(KDgetSize(rectangleTree), sizeof(char*));

    if (!size) {
        fprintf(results, "dpi\nTree size = 0 :( \n");
        fprintf(results, "========================================================");
        fclose(results);
        return;
    }

    void* root = KDgetRootNode(rectangleTree);
    fprintf(results, "\ndpi:\n\n");
    dpiInOrder(rectangleTree, root, x, y, names, &pos);
    qsort(names, pos , sizeof(char*), sortNames);
    for(int i = 0; i < pos; i++){
        fprintf(results, "%s\n", names[i]);
    }
    for(int i = 0; i < size; i++){
        free(names[i]);
    }
    free(names);
    fprintf(results, "\n========================================================\n");
    fclose(results);
}

void drInOrder(tree rectangleTree, node current, node analize, char** names, int* index) {
    void* aux = current;

    if (aux) {

        drInOrder(rectangleTree, KDgetLeftNode(aux), analize, names, index);

        if (inside(getRectangleX(KDgetData(aux)), getRectangleY(KDgetData(aux)), getRectangleWidth(KDgetData(aux)), getRectangleHeight(KDgetData(aux)), getRectangleX(KDgetData(analize)), getRectangleY(KDgetData(analize)), getRectangleWidth(KDgetData(analize)), getRectangleHeight(KDgetData(analize))) && getRectangleId(KDgetData(aux)) != getRectangleId(KDgetData(analize))) {
            
            names[*index] = calloc(strlen(getRectangleId(KDgetData(aux))) + 1, sizeof(char));
            strcpy(names[*index], getRectangleId(KDgetData(aux)));

            KDsetState(current, 0);
            KDsetSize(rectangleTree, KDgetSize(rectangleTree) - 1);
            *index = *index + 1;
        }

        drInOrder(rectangleTree, KDgetRightNode(aux), analize, names, index);
    }
}

void dr(tree rectangleTree, char* id, path paths) {
    FILE* results = fopen(getPathDoTXTComOQryExecutado(paths), "a+");
    setvbuf(results, 0, _IONBF, 0);
    char** names = calloc(KDgetSize(rectangleTree), sizeof(char*));
    int size = KDgetSize(rectangleTree);
    if (!KDgetSize(rectangleTree)) {
        fprintf(results, "dr\nTree size = 0 :( \n");
        fclose(results);
        return;
    }
    int pos = 0;
    fprintf(results, "\ndr:\n\n");

    if (!KDsearchID(KDgetRootNode(rectangleTree), id)) {
        fprintf(results, "id does not match any nodes in the tree :( \n");
        fprintf(results, "========================================================\n");
        fclose(results);
        return;
    }

    drInOrder(rectangleTree, KDgetRootNode(rectangleTree), KDsearchID(KDgetRootNode(rectangleTree), id), names, &pos);
    qsort(names, pos, sizeof(char*), sortNames);
    for(int i = 0; i < pos; i++){
        fprintf(results, "%s\n", names[i]);
    }
    for(int i = 0; i < size; i++){
        free(names[i]);
    }
    free(names);
    fprintf(results, "\n========================================================\n");
    fclose(results);
}

void fgInOrderRectangle(tree rectangleTree, FILE* results, void* current_rect, void* current_circ) {
    if (current_rect) {
        fgInOrderRectangle(rectangleTree, results, KDgetLeftNode(current_rect), current_circ);

        if (sqrt(pow((getCircleX(KDgetData(current_circ)) - getRectangleCenterX(KDgetData(current_rect))), 2) + (pow((getCircleY(KDgetData(current_circ)) - getRectangleCenterY(KDgetData(current_rect))), 2))) < getNearestDistance(KDgetData(current_circ)) && KDgetState(current_rect)) {
            setNearestDistance(KDgetData(current_circ), sqrt(pow(getCircleX(KDgetData(current_circ)) - getRectangleCenterX(KDgetData(current_rect)), 2) + pow((getCircleY(KDgetData(current_circ)) - getRectangleCenterY(KDgetData(current_rect))), 2)));
            setRunTo(KDgetData(current_circ), current_rect);
            setFg(KDgetData(current_circ), true);
        }

        fgInOrderRectangle(rectangleTree, results, KDgetRightNode(current_rect), current_circ);
    }
}

void fgInOrderCircle(tree rectangleTree, tree circleTree, FILE* results, void* current_rect, void* current_circ, double x, double y, double radius) {
    if (current_circ) {
        fgInOrderCircle(rectangleTree, circleTree, results, current_rect, KDgetLeftNode(current_circ), x, y, radius);

        if ((pow(abs(x - getCircleX(KDgetData(current_circ))), 2) + pow(abs(y - getCircleY(KDgetData(current_circ))), 2) <= pow(radius, 2))) {
            fgInOrderRectangle(rectangleTree, results, KDgetRootNode(rectangleTree), current_circ);  //Find closest rectangle

            if (!getVectorOfPeopleStarted(KDgetData(getRunTo(KDgetData(current_circ))))) {
                setVectorOfPeopleStarted(KDgetData(getRunTo(KDgetData(current_circ))), 1);
            }

            allocateVectorOfPeople(KDgetData(getRunTo(KDgetData(current_circ))));

            int exist = 0;

            for (int i = 0; i < getNumberOfPeopleInside(KDgetData(getRunTo(KDgetData(current_circ)))); i++) {  //Compare if someone that is already inside is trying to enter again

                if (!strcmp(getCircleId(KDgetData(getVectorOfPeople(KDgetData(getRunTo(KDgetData(current_circ))))[i])), getCircleId(KDgetData(current_circ)))) {
                    exist = 1;
                }
            }

            if (!exist) {
                setAddresses(KDgetData(getRunTo(KDgetData(current_circ))), current_circ, getNumberOfPeopleInside(KDgetData(getRunTo(KDgetData(current_circ)))));
                setNumberOfPeopleInside(KDgetData(getRunTo(KDgetData(current_circ))), getNumberOfPeopleInside(KDgetData(getRunTo(KDgetData(current_circ)))) + 1);
            }
        }

        fgInOrderCircle(rectangleTree, circleTree, results, current_rect, KDgetRightNode(current_circ), x, y, radius);
    }
}

void loop_rectangle_tree(sorting_t rectangles_to_sort, void* current_rect, int* size) {
    if (current_rect) {

        loop_rectangle_tree(rectangles_to_sort, KDgetLeftNode(current_rect), size);

        if(getVectorOfPeopleStarted(KDgetData(current_rect))){
            
            strcpy(rectangles_to_sort.data[*size].rectName, getRectangleId(KDgetData(current_rect)));
            rectangles_to_sort.data[*size].peopleInside = getVectorOfPeople(KDgetData(current_rect));
            rectangles_to_sort.data[*size].numberOfPeopleInside = getNumberOfPeopleInside(KDgetData(current_rect));
            rectangles_to_sort.data[*size].originalRect = current_rect;
            *size = *size + 1;

        }

        loop_rectangle_tree(rectangles_to_sort, KDgetRightNode(current_rect), size);
    }
}

void storeRectanglesToSort(tree rectangleTree, FILE* results) {
    
    sorting_t rectangles_to_sort;
    rectangles_to_sort.data = calloc(KDgetSize(rectangleTree), sizeof(data_s));
    rectangles_to_sort.size = 0;
    int size = 0;
    FILE* howManyRun = fopen("fgTemp.txt", "a+");
    setvbuf(howManyRun, 0, _IONBF, 0);

    loop_rectangle_tree(rectangles_to_sort, KDgetRootNode(rectangleTree), &size);

    qsort(rectangles_to_sort.data, size, sizeof(data_s), sortingNamesRectangle);

    for (int i = 0; i < size; i++) {
        
        void** arrayOfPeople = rectangles_to_sort.data[i].peopleInside;
        char** temp = calloc(rectangles_to_sort.data[i].numberOfPeopleInside, sizeof(char*));

        for (int j = 0; j < rectangles_to_sort.data[i].numberOfPeopleInside; j++) {
            temp[j] = calloc(strlen(getCircleId(KDgetData(rectangles_to_sort.data[i].peopleInside[j]))) + 1, sizeof(char));
            strcpy(temp[j], getCircleId(KDgetData(rectangles_to_sort.data[i].peopleInside[j])));
        }

        qsort(temp, rectangles_to_sort.data[i].numberOfPeopleInside, sizeof(char*), sortNames);

        
        fprintf(results, "✷ %s:\n", rectangles_to_sort.data[i].rectName);
        

        for (int j = 0; j < rectangles_to_sort.data[i].numberOfPeopleInside; j++) {
            fprintf(results, "-> %s\n", temp[j]);
        }

        if (rectangles_to_sort.data[i].numberOfPeopleInside) {
            fprintf(results, "\n");
        }

        for (int j = 0; j < rectangles_to_sort.data[i].numberOfPeopleInside; j++) {
            free(temp[j]);
        }
        free(temp);

        fprintf(howManyRun, "%.2lf %.2lf %d\n", getRectangleX(KDgetData(rectangles_to_sort.data[i].originalRect)) + 2 , getRectangleY(KDgetData(rectangles_to_sort.data[i].originalRect)) + 5, rectangles_to_sort.data[i].numberOfPeopleInside);

        freeVectorOfPeople(KDgetData(rectangles_to_sort.data[i].originalRect));
        setNumberOfPeopleInside(KDgetData(rectangles_to_sort.data[i].originalRect), 0);
        setVectorOfPeopleStarted(KDgetData(rectangles_to_sort.data[i].originalRect), 0);

    }
    free(rectangles_to_sort.data);
    fclose(howManyRun);
}


void updateCirclesNewPositions(tree circleTree, void* current_circ) {
    if (current_circ) {
        updateCirclesNewPositions(circleTree, KDgetLeftNode(current_circ));

        if (getRunTo(KDgetData(current_circ))) {
            setCircleX(KDgetData(current_circ), getRectangleCenterX(KDgetData(getRunTo(KDgetData(current_circ)))));
            setCircleY(KDgetData(current_circ), getRectangleCenterY(KDgetData(getRunTo(KDgetData(current_circ)))));
        }

        updateCirclesNewPositions(circleTree, KDgetRightNode(current_circ));
    }
}

void fg(tree rectangleTree, tree circleTree, double x, double y, double radius, path paths) {
    FILE* results = fopen(getPathDoTXTComOQryExecutado(paths), "a+");
    setvbuf(results, 0, _IONBF, 0);

    fgInOrderCircle(rectangleTree, circleTree, results, KDgetRootNode(rectangleTree), KDgetRootNode(circleTree), x, y, radius);
    fprintf(results, "FG: \n\n");
    updateCirclesNewPositions(circleTree, KDgetRootNode(circleTree));
    storeRectanglesToSort(rectangleTree, results);
    fprintf(results, "========================================================\n");
    fclose(results);
}

char* colorPicker(double radiation) {
    
    if (radiation < 25) return "#00ffff";
    else if (radiation >= 25 && radiation < 50) return "#00ff00";
    else if (radiation >= 50 && radiation < 100) return "#ff00ff";
    else if (radiation >= 100 && radiation < 250) return "#0000ff";
    else if (radiation >= 250 && radiation < 600) return "#800080";
    else if (radiation >= 600 && radiation < 1000) return "#000080";
    else if (radiation >= 1000 && radiation < 8000) return "#ff0000";
    else if (radiation >= 8000) return "#000000";

}

void imInOrderShadows(tree shadows, node currentShadowPolygon, node currentCircle, double xMeteor, double yMeteor) {
    
    if (currentShadowPolygon) {
        
        imInOrderShadows(shadows, NTgetLeftNode(currentShadowPolygon), currentCircle, xMeteor, yMeteor);
        void* line = NTgetData(currentShadowPolygon);  //Now has the array of segments
        int intersections = 0;

        for (int i = 0; i < 7; i++) {
            void* info = atPosArray(line, i);
            void* point1 = getP1(info);
            void* point2 = getP2(info);

            if (!point1 || !point2) {
                break;
            }

            if (get_line_intersection(getPointX(point1), getPointY(point1), getPointX(point2), getPointY(point2), getCircleX(KDgetData(currentCircle)), getCircleY(KDgetData(currentCircle)), xMeteor, yMeteor)) {
                if (getCircleX(KDgetData(currentCircle)) != getPointX(point1) && getCircleX(KDgetData(currentCircle)) != getPointX(point2) && getCircleY(KDgetData(currentCircle)) != getPointY(point1) && getCircleY(KDgetData(currentCircle)) != getPointY(point2))

                    intersections++;
            }
        }

        if (intersections % 2 == 1) {
            setInsideNShadows(KDgetData(currentCircle), getInsideNShadows(KDgetData(currentCircle)) + 1);
        }

        imInOrderShadows(shadows, NTgetRightNode(currentShadowPolygon), currentCircle, xMeteor, yMeteor);
    }
}

void imInOrderCircles(tree shadows, node currentCircle, double radiation, double xMeteor, double yMeteor, imSorting_t circlesToSort, int *index) {
    
    if (currentCircle) {
        imInOrderCircles(shadows, KDgetLeftNode(currentCircle), radiation, xMeteor, yMeteor, circlesToSort, index);
        setInsideNShadows(KDgetData(currentCircle), 0);
        imInOrderShadows(shadows, NTgetRootNode(shadows), currentCircle, xMeteor, yMeteor);

        if (!getInsideNShadows(KDgetData(currentCircle))) {
            setRadiation(KDgetData(currentCircle), getRadiation(KDgetData(currentCircle)) + radiation);

        } else {
            setRadiation(KDgetData(currentCircle), getRadiation(KDgetData(currentCircle)) + (pow(0.8, getInsideNShadows(KDgetData(currentCircle))) * radiation));
        }

        setCircleFill(KDgetData(currentCircle), colorPicker(getRadiation(KDgetData(currentCircle))));
        setCircleStroke(KDgetData(currentCircle), colorPicker(getRadiation(KDgetData(currentCircle))));

        if (getRadiation(KDgetData(currentCircle)) >= 1000 && getRadiation(KDgetData(currentCircle)) < 8000) {
            
            strcpy(circlesToSort.data[*(index)].circleName, getCircleId(KDgetData(currentCircle)));
            circlesToSort.data[*(index)].radiation = getRadiation(KDgetData(currentCircle));
            *index = *index + 1;

            
            setCircleMarkedForDeath(KDgetData(currentCircle), true);

        } else if (getRadiation(KDgetData(currentCircle)) >= 8000) {
            if (getCircleAlive(KDgetData(currentCircle))) {
                
                strcpy(circlesToSort.data[*(index)].circleName, getCircleId(KDgetData(currentCircle)));
                circlesToSort.data[*(index)].radiation = getRadiation(KDgetData(currentCircle));
                *index = *index + 1;
                
                setCircleAlive(KDgetData(currentCircle), false);
            }
        }


        imInOrderCircles(shadows, KDgetRightNode(currentCircle), radiation, xMeteor, yMeteor, circlesToSort, index);

    }
}

void im(tree rectangleTree, tree circleTree, dynamicList listOfTreesShadows, double xMeteor, double yMeteor, double radiation, path paths) {
    FILE* results = fopen(getPathDoTXTComOQryExecutado(paths), "a+");
    setvbuf(results, 0, _IONBF, 0);
    tree shadows = NTcreateTree();
    dynamicList segments = createList();
    buildSegments(rectangleTree, segments, KDgetRootNode(rectangleTree));
    addWrapAroundRectangle(rectangleTree, circleTree, segments);
    void* vertexArray = buildVertexArray(segments, xMeteor, yMeteor);
    storeShadowPolygons(shadows, vertexArray, segments, xMeteor, yMeteor);
    fprintf(results, "IM: \n\n");


    imSorting_t toSortCircles;
    toSortCircles.data = calloc(KDgetSize(circleTree), sizeof(circle_data_t));
    int pos = 0;
    imInOrderCircles(shadows, KDgetRootNode(circleTree), radiation, xMeteor, yMeteor, toSortCircles, &pos);
    qsort(toSortCircles.data, pos, sizeof(circle_data_t), sortingNamesCircle);
    
    for(int i = 0; i < pos; i++){
        if(toSortCircles.data[i].radiation >= 1000 && toSortCircles.data[i].radiation < 8000){
            fprintf(results, "%s - Morte Iminente\n", toSortCircles.data[i].circleName);
        }else if(toSortCircles.data[i].radiation >= 8000){
            fprintf(results, "%s - Morte Instantanea\n", toSortCircles.data[i].circleName);
        }
    }


    fprintf(results, "\n========================================================\n");
    free(toSortCircles.data);
    FILE* tempIm = fopen("imTemp.txt", "a+");
    setvbuf(tempIm, 0, _IONBF, 0);
    fprintf(tempIm, "%.6lf %.6lf %.6lf\n", xMeteor, yMeteor, radiation / 3);
    // printSvgShadows(shadows, getBiggestX(rectangleTree) > getBiggestX(circleTree) ? getBiggestX(rectangleTree) + 100 : getBiggestX(circleTree) + 100, getBiggestY(rectangleTree) > getBiggestY(circleTree) ? getBiggestY(rectangleTree) + 100 : getBiggestY(circleTree) + 100);
    void* auxNode = insert(listOfTreesShadows, shadows);
    setDataRadiation(auxNode, radiation);
    setDataxMeteor(auxNode, xMeteor);
    setDatayMeteor(auxNode, yMeteor);
    free(vertexArray);
    freeListOfSegments(segments);
    fclose(results);
    fclose(tempIm);
}

void t30InOrderT30(tree circleTree, node currentCircle, FILE* results) {
    if (currentCircle) {

        t30InOrderT30(circleTree, KDgetLeftNode(currentCircle), results);

        if (getCircleMarkedForDeath(KDgetData(currentCircle))) {
            fprintf(results, "ID %s morto por tempo\n", getCircleId(KDgetData(currentCircle)));
            setCircleAlive(KDgetData(currentCircle), false);
        }

        t30InOrderT30(circleTree, KDgetRightNode(currentCircle), results);

    }
}

void t30(tree circleTree, path paths) {
    FILE* results = fopen(getPathDoTXTComOQryExecutado(paths), "a+");
    setvbuf(results, 0, _IONBF, 0);
    fprintf(results, "T30: \n\n");
    t30InOrderT30(circleTree, KDgetRootNode(circleTree), results);
    fprintf(results, "\n========================================================\n");
    fclose(results);
}

void nveUpdateRadiation(void* currentPolygon, double xNve, double yNve, int* inside_polygons, double xMeteor, double yMeteor) {
    int insideNPolygons = 0;
    void* line = NTgetData(currentPolygon);
    int intersections = 0;

    for (int i = 0; i < 7; i++) {
        void* info = atPosArray(line, i);
        void* point1 = getP1(info);
        void* point2 = getP2(info);

        if (!point1 || !point2) {
            break;
        }

        if (get_line_intersection(getPointX(point1), getPointY(point1), getPointX(point2), getPointY(point2), xNve, yNve, xMeteor, yMeteor)) {
            if (xNve != getPointX(point1) && xNve != getPointX(point2) && yNve != getPointY(point1) && yNve != getPointY(point2))

                intersections++;

            
        }
    }

    if (intersections % 2 == 1) {
        insideNPolygons++;
        
    }

    *inside_polygons += (insideNPolygons);
}

void nveInOrder(tree shadowTree, node currentListPosition, node currentPolygon, int* insideNPolygons, double x, double y, double xMeteor, double yMeteor) {
    if (currentPolygon) {

        nveInOrder(shadowTree, currentListPosition, NTgetLeftNode(currentPolygon), insideNPolygons, x, y, xMeteor, yMeteor);

        nveUpdateRadiation(currentPolygon, x, y, insideNPolygons, xMeteor, yMeteor);

        nveInOrder(shadowTree, currentListPosition, NTgetRightNode(currentPolygon), insideNPolygons, x, y, xMeteor, yMeteor);
    }
}

void nve(dynamicList listOfTreesShadows, path paths, double x, double y) {
    
    FILE* results = fopen(getPathDoTXTComOQryExecutado(paths), "a+");
    setvbuf(results, 0, _IONBF, 0);
    FILE* tempFileOfNve = fopen("nveTemp.txt", "a+");
    setvbuf(tempFileOfNve, 0, _IONBF, 0);
    double radiationAtThePoint = 0.0;
    void* posAuxList = getHead(listOfTreesShadows);  //Now I'm storing the head of the list

    for (int i = 0; i < getSize(listOfTreesShadows); i++) {
        int inside_n_polygons = 0;
        void* treeAux = getItem(listOfTreesShadows, posAuxList);  //Now I'm getting the address of the whole tree inside node
        void* treeNodeAux = NTgetRootNode(treeAux);               //I'm getting the root node from the tree that I'm analysing
        nveInOrder(treeAux, posAuxList, treeNodeAux, &inside_n_polygons, x, y, getDataxMeteor(posAuxList), getDatayMeteor(posAuxList));

        if (!inside_n_polygons) radiationAtThePoint += (getDataRadiation(posAuxList));
        else radiationAtThePoint += (pow(0.8, inside_n_polygons) * getDataRadiation(posAuxList));
        posAuxList = getNext(listOfTreesShadows, posAuxList);

    }

    fprintf(results, "NVE: \n\n(%.6lf, %.6lf) has %.6lf mSv\n", x, y, radiationAtThePoint);
    fprintf(tempFileOfNve, "%.6lf %.6lf %.6lf\n", x, y, radiationAtThePoint);
    fprintf(results, "\n========================================================\n");
    fclose(tempFileOfNve);
    fclose(results);
}