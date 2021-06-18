#include "svg.h"

#include "circle.h"
#include "kdTree.h"
#include "rectangle.h"
#include "system.h"

double max(double x1, double x2) {
    return x2 > x1 ? x2 : x1;
}

void printRectangleInOrder(FILE* svg_source, tree initialTree, node current) {
    if (current != NULL) {
        printRectangleInOrder(svg_source, initialTree, KDgetLeftNode(current));
        if (KDgetState(current)) {
            fprintf(svg_source, "\t<rect x=\"%.2lf\" y=\"%.2lf\" width=\"%.2lf\" height=\"%.2lf\" id=\"%s\"\n  style=\"fill:%s;stroke:%s;stroke-width:.5;fill-opacity:0.5;stroke-opacity:1\" />\n", getRectangleX(KDgetData(current)), getRectangleY(KDgetData(current)), getRectangleWidth(KDgetData(current)), getRectangleHeight(KDgetData(current)), getRectangleId(KDgetData(current)), getRectangleFill(KDgetData(current)), getRectangleStroke(KDgetData(current)));
        }
        printRectangleInOrder(svg_source, initialTree, KDgetRightNode(current));
    }
}

void printCircleInOrder(FILE* svg_source, tree initialTree, node current) {
    if (current != NULL) {
        printCircleInOrder(svg_source, initialTree, KDgetLeftNode(current));
        if (KDgetState(current) && getCircleAlive(KDgetData(current))) {
            if (getFg(KDgetData(current)) && getRunTo(KDgetData(current)) != NULL && KDgetState(getRunTo(KDgetData(current)))) {
                fprintf(svg_source, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"%.2lf\" id=\"%s\" stroke=\"grey\" stroke-width=\".5\" fill=\"lightgrey\" fill-opacity = \"0.3\" />\n", getCircleOriginalX(KDgetData(current)), getCircleOriginalY(KDgetData(current)), getCircleRadius(KDgetData(current)), getCircleId(KDgetData(current)));
                fprintf(svg_source, "\t<path fill=\"none\" stroke=\"red\" stroke-dasharray=\"2\" d=\"M%.2lf,%.2lf %.2lf,%.2lf z\"/>\n", getCircleOriginalX(KDgetData(current)), getCircleOriginalY(KDgetData(current)), getRectangleCenterX(KDgetData(getRunTo(KDgetData(current)))), getRectangleCenterY(KDgetData(getRunTo(KDgetData(current)))));
                fprintf(svg_source, "\t<circle r=\"%.2lf\" id=\"%s\" stroke=\"%s\" stroke-width=\".5\" fill=\"%s\" fill-opacity = \"0.5\" >\n", getCircleRadius(KDgetData(current)), getCircleId(KDgetData(current)), getCircleStroke(KDgetData(current)), getCircleFill(KDgetData(current)));
                fprintf(svg_source, "\t\t<animateMotion dur=\"10s\" repeatCount=\"indefinite\" path=\"M%.2lf,%.2lf %.2lf,%.2lf z\"/>\n", getCircleOriginalX(KDgetData(current)), getCircleOriginalY(KDgetData(current)), getRectangleCenterX(KDgetData(getRunTo(KDgetData(current)))), getRectangleCenterY(KDgetData(getRunTo(KDgetData(current)))));
                fprintf(svg_source, "\t</circle>\n");
            }
            else {
                fprintf(svg_source, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"%.2lf\" id=\"%s\" stroke=\"%s\" stroke-width=\".5\" fill=\"%s\" fill-opacity = \"0.5\" />\n", getCircleX(KDgetData(current)), getCircleY(KDgetData(current)), getCircleRadius(KDgetData(current)), getCircleId(KDgetData(current)), getCircleStroke(KDgetData(current)), getCircleFill(KDgetData(current)));
            }
        } else {
            fprintf(svg_source, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"%.2lf\" id=\"%s\" stroke=\"black\" stroke-width=\".5\" fill=\"black\" fill-opacity = \"0.5\" />\n", getCircleX(KDgetData(current)), getCircleY(KDgetData(current)), getCircleRadius(KDgetData(current)), getCircleId(KDgetData(current)));
            fprintf(svg_source, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" stroke=\"white\" stroke-width=\".6\"/>\n", getCircleX(KDgetData(current)) - getCircleRadius(KDgetData(current))/2, getCircleY(KDgetData(current)), getCircleX(KDgetData(current)) + getCircleRadius(KDgetData(current))/2, getCircleY(KDgetData(current)));  //Horizontal
            fprintf(svg_source, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" stroke=\"white\" stroke-width=\".6\"/>\n", getCircleX(KDgetData(current)), getCircleY(KDgetData(current)) - getCircleRadius(KDgetData(current))/2, getCircleX(KDgetData(current)), getCircleY(KDgetData(current)) + getCircleRadius(KDgetData(current))/2 );  //Vertical
        }
        printCircleInOrder(svg_source, initialTree, KDgetRightNode(current));
    }
}

void printNves(FILE* nveTemp, FILE* svg_source) {
    double posX, posY, radiation;
    char color[8];
    while (fscanf(nveTemp, "%lf %lf %lf", &posX, &posY, &radiation) != -1) {
        if (radiation < 25) {
            strcpy(color, "#00ffff");
        } else if (radiation >= 25 && radiation < 50) {
            strcpy(color, "#00ff00");
        } else if (radiation >= 50 && radiation < 100) {
            strcpy(color, "#ff00ff");
        } else if (radiation >= 100 && radiation < 250) {
            strcpy(color, "#0000ff");
        } else if (radiation >= 250 && radiation < 600) {
            strcpy(color, "#800080");
        } else if (radiation >= 600 && radiation < 1000) {
            strcpy(color, "#000080");
        } else if (radiation >= 1000 && radiation < 8000) {
            strcpy(color, "#ff0000");
        } else if (radiation >= 8000) {
            strcpy(color, "#000000");
        }

        fprintf(svg_source, "\t<rect x=\"%.2lf\" y=\"%.2lf\" width=\"5\" height=\"5\"\n  style=\"fill:%s;stroke:%s;stroke-width:.5;fill-opacity:0.5;stroke-opacity:1\" rx=\"1\"/>\n", posX, posY, color, color);
        fprintf(svg_source, "\t<text x=\"%.2lf\" y=\"%.2lf\" fill=\"white\" font-size=\"1\">%.2lf</text>\n", posX + 1, posY + 2, radiation);
    }
}

void printIms(FILE* imExist, FILE* svg_source) {
    double x, y, radius;
    while (fscanf(imExist, "%lf %lf %lf", &x, &y, &radius) != -1) {
        fprintf(svg_source, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"%.2lf\" stroke=\"dimgrey\" stroke-width=\".5\" fill=\"dimgrey\" fill-opacity = \"0.1\" />\n", x, y, radius);
    }
}

void printFgs(FILE* fgExist, FILE* svg_source) {
    double x, y;
    int number_of_sheltered;
    while (fscanf(fgExist, "%lf %lf %d", &x, &y, &number_of_sheltered) != -1) {
        fprintf(svg_source, "\t<text x=\"%.2lf\" y=\"%.2lf\" font-size=\"5\">%d</text>\n", x, y, number_of_sheltered);
    }
}

void writeOnSvg(FILE* svg_source, tree rectTree, tree circleTree, path paths) {
    if (!KDgetSize(rectTree) && !KDgetSize(circleTree)) {
        fprintf(svg_source, "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" width=\"100%%\" height=\"100%%\">\n \t<svg>");
        fclose(svg_source);
    }
    fprintf(svg_source, "<!-- Rodrigo Mimura Shimomura -->\n <svg viewBox = \"0 0 %.2lf %.2lf\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n", max(getBiggestX(rectTree), getBiggestX(circleTree)) + 15, max(getBiggestY(rectTree), getBiggestY(circleTree)) + 15);
    fprintf(svg_source, "\t<rect x=\"0\" y=\"0\" width=\"%.2lf\" height=\"%.2lf\" \n  style=\"fill:lightgrey;stroke:yellow;stroke-width:.5;fill-opacity:0.1;stroke-opacity:1\" />\n", max(getBiggestX(rectTree), getBiggestX(circleTree)) + 15, max(getBiggestY(rectTree), getBiggestY(circleTree)) + 15);
    if (KDgetSize(rectTree)) {
        printRectangleInOrder(svg_source, rectTree, KDgetRootNode(rectTree));
    }
    if (KDgetSize(circleTree)) {
        printCircleInOrder(svg_source, circleTree, KDgetRootNode(circleTree));
    }
    
    FILE* nveExist = fopen("nveTemp.txt", "r");
    if (nveExist) {
        setvbuf(nveExist, 0, _IONBF, 0);
        printNves(nveExist, svg_source);
        fclose(nveExist);
        remove("nveTemp.txt");
    }

    FILE* imExist = fopen("imTemp.txt", "r");
    if (imExist) {
        setvbuf(imExist, 0, _IONBF, 0);
        printIms(imExist, svg_source);
        fclose(imExist);
        remove("imTemp.txt");
    }

    FILE* fgExist = fopen("fgTemp.txt", "r");
    if(fgExist){
        setvbuf(fgExist, 0, _IONBF, 0);
        printFgs(fgExist, svg_source);
        fclose(fgExist);
        remove("fgTemp.txt");
    }


    fprintf(svg_source, "</svg>");
}