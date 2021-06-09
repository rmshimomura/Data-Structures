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

int inside(double x1, double y1, double p1Width, double p1Height, double x2, double y2, double p2Width, double p2Height) {
    if ((x1 >= x2 && x1 <= x2 + p2Width && y1 >= y2 && y1 <= y2 + p2Height && x1 + p1Width <= x2 + p2Width && y1 + p1Height <= y2 + p2Height)) {
        return 1;
    } else {
        return 0;
    }
}

int get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y, float p2_x, float p2_y, float p3_x, float p3_y){
    float s1_x, s1_y, s2_x, s2_y;
    s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

    float s, t;
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        // Collision detected
        return 1;
    }

    return 0; // No collision
}

void dpiInOrder(tree rectangleTree, FILE* svg_source, node currentNode, double x, double y) {
    if (currentNode != NULL) {
        dpiInOrder(rectangleTree, svg_source, KDgetLeftNode(currentNode), x, y);
        if (inside(x, y, 0, 0, getRectangleX(KDgetData(currentNode)), getRectangleY(KDgetData(currentNode)), getRectangleWidth(KDgetData(currentNode)), getRectangleHeight(KDgetData(currentNode))) && KDgetState(currentNode)) {
            fprintf(svg_source, "%s\n", getRectangleId(KDgetData(currentNode)));
            KDsetState(currentNode, 0);
            KDsetSize(rectangleTree, KDgetSize(rectangleTree) - 1);
        }
        dpiInOrder(rectangleTree, svg_source, KDgetRightNode(currentNode), x, y);
    }
}

void dpi(tree rectangleTree, double x, double y, path paths) {
    FILE* results = fopen(getPathDoTXTComOQryExecutado(paths), "a+");
    setvbuf(results, 0, _IONBF, 0);
    int size = KDgetSize(rectangleTree);
    if (!size) {
        fprintf(results, "dpi\nTree size = 0 :( \n");
        fprintf(results, "========================================================");
        fclose(results);
        return;
    }
    void* root = KDgetRootNode(rectangleTree);
    fprintf(results, "\ndpi:\n");
    dpiInOrder(rectangleTree, results, root, x, y);
    fprintf(results, "\n========================================================\n");
    fclose(results);
}

void drInOrder(tree rectangleTree, FILE* results, node current, node analize) {
    void* aux = current;
    if (aux) {
        drInOrder(rectangleTree, results, KDgetLeftNode(aux), analize);
        if (inside(getRectangleX(KDgetData(aux)), getRectangleY(KDgetData(aux)), getRectangleWidth(KDgetData(aux)), getRectangleHeight(KDgetData(aux)), getRectangleX(KDgetData(analize)), getRectangleY(KDgetData(analize)), getRectangleWidth(KDgetData(analize)), getRectangleHeight(KDgetData(analize))) && getRectangleId(KDgetData(aux)) != getRectangleId(KDgetData(analize))) {
            fprintf(results, "%s\n", getRectangleId(KDgetData(aux)));
            KDsetState(current, 0);
            KDsetSize(rectangleTree, KDgetSize(rectangleTree) - 1);
        }
        drInOrder(rectangleTree, results, KDgetRightNode(aux), analize);
    }
}

void dr(tree rectangleTree, char* id, path paths) {
    FILE* results = fopen(getPathDoTXTComOQryExecutado(paths), "a+");
    setvbuf(results, 0, _IONBF, 0);
    if (!KDgetSize(rectangleTree)) {
        fprintf(results, "dr\nTree size = 0 :( \n");
        fclose(results);
        return;
    }
    fprintf(results, "\ndr:\n");
    if (!KDsearchID(KDgetRootNode(rectangleTree), id)) {
        fprintf(results, "id does not match any nodes in the tree :( \n");
        fprintf(results, "========================================================\n");
        fclose(results);
        return;
    }
    drInOrder(rectangleTree, results, KDgetRootNode(rectangleTree), KDsearchID(KDgetRootNode(rectangleTree), id));
    fprintf(results, "\n========================================================\n");
    fclose(results);
}

void stopEveryone(tree circleTree, void* current_circle) {
    if (current_circle) {
        stopEveryone(circleTree, KDgetLeftNode(current_circle));
        setNearestDistance(KDgetData(current_circle), __DBL_MAX__);
        setRunTo(KDgetData(current_circle), NULL);
        setFg(KDgetData(current_circle), 0);
        stopEveryone(circleTree, KDgetRightNode(current_circle));
    }
}

void fgCheckShelteredRectangle(tree rectangleTree, tree circleTree, void* current_rectangle, void* current_circle) {
    if (current_rectangle) {
        fgCheckShelteredRectangle(rectangleTree, circleTree, KDgetLeftNode(current_rectangle), current_circle);

        if (inside(getCircleX(KDgetData(current_circle)), getCircleY(KDgetData(current_circle)), 0, 0, getRectangleX(KDgetData(current_rectangle)), getRectangleY(KDgetData(current_rectangle)), getRectangleWidth(KDgetData(current_rectangle)), getRectangleHeight(KDgetData(current_rectangle))) && KDgetState(current_rectangle)) {
            if (!getVectorOfPeopleStarted(KDgetData(current_rectangle))) {
                setVectorOfPeopleStarted(KDgetData(current_rectangle), 1);
            }
            // setNearestDistance(KDgetData(current_circle), sqrt(pow(getCircleX(KDgetData(current_circle)) - getRectangleCenterX(KDgetData(current_rectangle)), 2) + pow((getCircleY(KDgetData(current_circle)) - getRectangleCenterY(KDgetData(current_rectangle))), 2)));
            // setRunTo(KDgetData(current_circle), current_rectangle);
            setFg(KDgetData(current_circle), false);
            allocateVectorOfPeople(KDgetData(current_rectangle));
            int exist = 0;
            for (int i = 0; i < getNumberOfPeopleInside(KDgetData(current_rectangle)); i++) {  //Compare if someone that is already inside is trying to enter again
                if (!strcmp(getCircleId(KDgetData(getVectorOfPeople(KDgetData(current_rectangle))[i])), getCircleId(KDgetData(current_circle)))) {
                    exist = 1;
                }
            }
            if (!exist) {
                setAddresses(KDgetData(current_rectangle), current_circle, getNumberOfPeopleInside(KDgetData(current_rectangle)));
                setNumberOfPeopleInside(KDgetData(current_rectangle), getNumberOfPeopleInside(KDgetData(current_rectangle)) + 1);
            }
        }
        fgCheckShelteredRectangle(rectangleTree, circleTree, KDgetRightNode(current_rectangle), current_circle);
    }
}

void fgCheckShelteredCircle(tree rectangleTree, tree circleTree, void* current_circle) {
    if (current_circle) {
        fgCheckShelteredCircle(rectangleTree, circleTree, KDgetLeftNode(current_circle));
        fgCheckShelteredRectangle(rectangleTree, circleTree, KDgetRootNode(rectangleTree), current_circle);
        fgCheckShelteredCircle(rectangleTree, circleTree, KDgetRightNode(current_circle));
    }
}

void fgInOrderRectangle(tree rectangleTree, FILE* results, void* current_rect, void* current_circ) {
    if (current_rect) {
        fgInOrderRectangle(rectangleTree, results, KDgetLeftNode(current_rect), current_circ);

        if (sqrt(pow((getCircleX(KDgetData(current_circ)) - getRectangleCenterX(KDgetData(current_rect))), 2) + (pow((getCircleY(KDgetData(current_circ)) - getRectangleCenterY(KDgetData(current_rect))), 2))) < getNearestDistance(KDgetData(current_circ)) && KDgetState(current_rect)) {
            if (getRunTo(KDgetData(current_circ)) != current_rect && getRunTo(KDgetData(current_circ)) != NULL) {  //Someone leave the current rect, and has to run to a new one
                // printf("UPDATE ! %s has now to run to %s\n",  getCircleId(KDgetData(current_circ)), getRectangleId(KDgetData(current_rect)));

                setNumberOfPeopleInside(KDgetData(getRunTo(KDgetData(current_circ))), getNumberOfPeopleInside(KDgetData(getRunTo(KDgetData(current_circ)))) - 1);
            }
            // printf("I'm setting %s to run to %s.\n", getCircleId(KDgetData(current_circ)), getRectangleId(KDgetData(current_rect)));
            // puts("SET!");
            setNearestDistance(KDgetData(current_circ), sqrt(pow(getCircleX(KDgetData(current_circ)) - getRectangleCenterX(KDgetData(current_rect)), 2) + pow((getCircleY(KDgetData(current_circ)) - getRectangleCenterY(KDgetData(current_rect))), 2)));
            setRunTo(KDgetData(current_circ), current_rect);
            setFg(KDgetData(current_circ), true);
            if (!getVectorOfPeopleStarted(KDgetData(current_rect))) {
                setVectorOfPeopleStarted(KDgetData(current_rect), 1);
            }
            allocateVectorOfPeople(KDgetData(current_rect));
            int exist = 0;
            for (int i = 0; i < getNumberOfPeopleInside(KDgetData(current_rect)); i++) {  //Compare if someone that is already inside is trying to enter again
                if (!strcmp(getCircleId(KDgetData(getVectorOfPeople(KDgetData(current_rect))[i])), getCircleId(KDgetData(current_circ)))) {
                    exist = 1;
                }
            }
            if (!exist) {
                setAddresses(KDgetData(current_rect), current_circ, getNumberOfPeopleInside(KDgetData(current_rect)));
                setNumberOfPeopleInside(KDgetData(current_rect), getNumberOfPeopleInside(KDgetData(current_rect)) + 1);
            }
            // printf("There are %d inside %s\n", getNumberOfPeopleInside(KDgetData(current_rect)), getRectangleId(KDgetData(current_rect)));
        }
        fgInOrderRectangle(rectangleTree, results, KDgetRightNode(current_rect), current_circ);
    }
}

void fgInOrderCircle(tree rectangleTree, tree circleTree, FILE* results, void* current_rect, void* current_circ, double x, double y, double radius) {
    if (current_circ) {
        fgInOrderCircle(rectangleTree, circleTree, results, current_rect, KDgetLeftNode(current_circ), x, y, radius);
        if ((pow(abs(x - getCircleX(KDgetData(current_circ))), 2) + pow(abs(y - getCircleY(KDgetData(current_circ))), 2) <= pow(radius, 2))) {
            fgInOrderRectangle(rectangleTree, results, KDgetRootNode(rectangleTree), current_circ);
        }
        fgInOrderCircle(rectangleTree, circleTree, results, current_rect, KDgetRightNode(current_circ), x, y, radius);
    }
}

void writeFgresults(tree rectangleTree, FILE* results, void* current_rect, double x, double y, double radius) {
    if (current_rect) {
        writeFgresults(rectangleTree, results, KDgetLeftNode(current_rect), x, y, radius);
        if (getVectorOfPeopleStarted(KDgetData(current_rect))) {
            if (getNumberOfPeopleInside(KDgetData(current_rect))) {
                fprintf(results, "✷ %s:\n", getRectangleId(KDgetData(current_rect)));
            }
            for (int i = 0; i < getNumberOfPeopleInside(KDgetData(current_rect)); i++) {
                fprintf(results, "-> %s\n", getCircleId(KDgetData(getVectorOfPeople(KDgetData(current_rect))[i])));
                // fprintf(results, "-> %p\n", KDgetData(getVectorOfPeople(KDgetData(current_rect))[i]));
            }
            if (getNumberOfPeopleInside(KDgetData(current_rect))) {
                fprintf(results, "\n");
            }
        }
        writeFgresults(rectangleTree, results, KDgetRightNode(current_rect), x, y, radius);
    }
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
    if (!KDgetSize(rectangleTree)) {
        fprintf(results, "There are no more buildings to run to :( .\n");
        stopEveryone(circleTree, KDgetRootNode(circleTree));
        fclose(results);
        return;
    }
    if (!KDgetSize(circleTree)) {
        fprintf(results, "Everyone is dead :( .\n");
        fclose(results);
        return;
    }
    fgCheckShelteredCircle(rectangleTree, circleTree, KDgetRootNode(circleTree));
    fgInOrderCircle(rectangleTree, circleTree, results, KDgetRootNode(rectangleTree), KDgetRootNode(circleTree), x, y, radius);
    fprintf(results, "FG: \n\n");
    updateCirclesNewPositions(circleTree, KDgetRootNode(circleTree));
    writeFgresults(rectangleTree, results, KDgetRootNode(rectangleTree), x, y, radius);
    fprintf(results, "========================================================\n");
    fclose(results);
}

char* colorPicker(double radiation) {
    if (radiation < 25) {
        return "#00ffff";
    } else if (radiation >= 25 && radiation < 50) {
        return "#00ff00";
    } else if (radiation >= 50 && radiation < 100) {
        return "#ff00ff";
    } else if (radiation >= 100 && radiation < 250) {
        return "#0000ff";
    } else if (radiation >= 250 && radiation < 600) {
        return "#800080";
    } else if (radiation >= 600 && radiation < 1000) {
        return "#000080";
    } else if (radiation >= 1000 && radiation < 8000) {
        return "#ff0000";
    } else if (radiation >= 8000) {
        return "#000000";
    }
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
                if(getCircleX(KDgetData(currentCircle)) != getPointX(point1) && getCircleX(KDgetData(currentCircle)) != getPointX(point2) && getCircleY(KDgetData(currentCircle)) != getPointY(point1) && getCircleY(KDgetData(currentCircle)) != getPointY(point2))
                    intersections++;
            }
        }
        if (intersections % 2 == 1) {
            setInsideNShadows(KDgetData(currentCircle), getInsideNShadows(KDgetData(currentCircle)) + 1);
        }
        imInOrderShadows(shadows, NTgetRightNode(currentShadowPolygon), currentCircle, xMeteor, yMeteor);
    }
}

void imInOrderCircles(tree shadows, tree circleTree, node currentCircle, FILE* results, double radiation, double xMeteor, double yMeteor) {
    if (currentCircle) {
        imInOrderCircles(shadows, circleTree, KDgetLeftNode(currentCircle), results, radiation, xMeteor, yMeteor);
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
            fprintf(results, "%s morte iminente\n", getCircleId(KDgetData(currentCircle)));
            setCircleMarkedForDeath(KDgetData(currentCircle), true);
        } else if (getRadiation(KDgetData(currentCircle)) >= 8000) {
            if (getCircleAlive(KDgetData(currentCircle))) {
                fprintf(results, "%s morte instantanea\n", getCircleId(KDgetData(currentCircle)));
                setCircleAlive(KDgetData(currentCircle), false);
            }
        }
        // fprintf(results, "DEBUG - %s has %.6lf mSv\n",  getCircleId(KDgetData(currentCircle)), getRadiation(KDgetData(currentCircle)));
        imInOrderCircles(shadows, circleTree, KDgetRightNode(currentCircle), results, radiation, xMeteor, yMeteor);
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
    imInOrderCircles(shadows, circleTree, KDgetRootNode(circleTree), results, radiation, xMeteor, yMeteor);
    fprintf(results, "\n========================================================\n");
    FILE* tempIm = fopen("imTemp.txt", "a+");
    setvbuf(tempIm, 0, _IONBF, 0);
    fprintf(tempIm, "%.6lf %.6lf %.6lf\n", xMeteor, yMeteor, radiation / 3);
    // printSvgShadows(shadows, getBiggestX(rectangleTree) > getBiggestX(circleTree) ? getBiggestX(rectangleTree) + 100 : getBiggestX(circleTree) + 100, getBiggestY(rectangleTree) > getBiggestY(circleTree) ? getBiggestY(rectangleTree) + 100 : getBiggestY(circleTree) + 100);
    // checkNewDivisions(segments, xMeteor, yMeteor);
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
            if(xNve != getPointX(point1) && xNve != getPointX(point2) && yNve != getPointY(point1) && yNve != getPointY(point2))
                intersections++;
            // printf("Intercept with (%.2lf, %.2lf) - (%.2lf, %.2lf)\n", getPointX(point1), getPointY(point1), getPointX(point2), getPointY(point2));
        }
    }
    if (intersections % 2 == 1) {
        insideNPolygons++;
        // puts("UP!");
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
        // printf("xmeteor = %.2lf ymeteor = %.2lf\n", getDataxMeteor(posAuxList), getDatayMeteor(posAuxList));
        nveInOrder(treeAux, posAuxList, treeNodeAux, &inside_n_polygons, x, y, getDataxMeteor(posAuxList), getDatayMeteor(posAuxList));
        // printf("%d inside polygons\n", inside_n_polygons);
        if (!inside_n_polygons) {
            // puts("aqui");
            radiationAtThePoint += (getDataRadiation(posAuxList));
        } else {
            // puts("la");
            // printf("Inside %d polygons\n", inside_n_polygons);
            radiationAtThePoint += (pow(0.8, inside_n_polygons) * getDataRadiation(posAuxList));
        }

        posAuxList = getNext(listOfTreesShadows, posAuxList);
    }
    fprintf(results, "NVE: \n\n(%.6lf, %.6lf) has %.6lf mSv\n", x, y, radiationAtThePoint);
    fprintf(tempFileOfNve, "%.6lf %.6lf %.6lf\n", x, y, radiationAtThePoint);
    fprintf(results, "\n========================================================\n");
    fclose(tempFileOfNve);
    fclose(results);
}