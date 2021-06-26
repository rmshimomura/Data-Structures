#include "bibliotecas.h"
#include "circle.h"
#include "dynamicList.h"
#include "kdTree.h"
#include "normalTree.h"
#include "paths.h"
#include "polygon.h"
#include "rectangle.h"
#include "segments.h"
#include "svg.h"
#include "system.h"

int main(int argc, char** argv) {

    path paths = create_general_paths();
    tree rectangles = KDcreateTree();
    tree circles = KDcreateTree();
    dynamicList listOfTreesShadows = createList();
    int qryExecuted = get_arguments(argc, argv, paths);
    get_data(rectangles, circles, paths);
    FILE* svg_source = fopen(get_path_original_SVG(paths), "w+");
    setvbuf(svg_source, 0, _IONBF, 0);
    write_on_svg(svg_source, rectangles, circles, paths);

    if (qryExecuted) {

        FILE* txt_results = fopen(get_path_TXT_with_qry(paths), "w+");
        setvbuf(txt_results, 0, _IONBF, 0);
        fprintf(txt_results, "Rodrigo Mimura Shimomura\n");
        get_functions(rectangles, circles, listOfTreesShadows, paths);
        fclose(txt_results);

    }

    KDdestroyRectTree(rectangles, KDgetRootNode(rectangles));
    KDdestroyCircTree(circles, KDgetRootNode(circles));
    freePaths(paths);
    free(rectangles);
    free(circles);
    freeListOfTreesShadows(listOfTreesShadows);
    fclose(svg_source);
    
}