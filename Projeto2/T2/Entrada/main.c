#include "bibliotecas.h"
#include "circle.h"
#include "kdTree.h"
#include "paths.h"
#include "rectangle.h"
#include "svg.h"
#include "system.h"
#include "segments.h"
#include "dynamicList.h"
#include "normalTree.h"
#include "polygon.h"

int main(int argc, char** argv) {
    path paths = createPathsGerais();
    tree rectangles = KDcreateTree();
    tree circles = KDcreateTree();
    // tree shadows = NTcreateTree();
    dynamicList listOfTreesShadows = createList();
    int consulta = getArguments(argc, argv, paths);
    getData(rectangles, circles, paths);
    // dynamicList segments = createList();
    // buildSegments(rectangles, segments, KDgetRootNode(rectangles));
    // addWrapAroundRectangle(rectangles, circles, segments);
    FILE* svg_source = fopen(getPathDoSvgDoGeoSemMudanca(paths), "w+");
    setvbuf(svg_source, 0, _IONBF, 0);
    writeOnSvg(svg_source, rectangles, circles, paths);
    if (consulta) {
        FILE* txt_results = fopen(getPathDoTXTComOQryExecutado(paths), "w+");
        fprintf(txt_results, "Rodrigo Mimura Shimomura\n");
        setvbuf(txt_results, 0, _IONBF, 0);
        getFunctions(rectangles, circles, listOfTreesShadows, paths);
        fclose(txt_results);
    }
    KDdestroyRectTree(rectangles, KDgetRootNode(rectangles));
    KDdestroyCircTree(circles, KDgetRootNode(circles));
    // freeNTTree(shadows, NTgetRootNode(shadows));
    freePaths(paths);
    free(rectangles);
    free(circles);
    // free(shadows);
    // freeListOfSegments(segments);
    freeListOfTreesShadows(listOfTreesShadows);
    fclose(svg_source);
}