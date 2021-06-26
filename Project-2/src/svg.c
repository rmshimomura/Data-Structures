#include "svg.h"

#include "circle.h"
#include "dynamicList.h"
#include "kdTree.h"
#include "rectangle.h"
#include "system.h"

double get_temp_x(void* node);
double get_temp_y(void* node);
double get_temp_joker(void* node);

double max(double x1, double x2) {
    return x2 > x1 ? x2 : x1;
}

void print_rectangle_in_order(FILE* svg_source, tree initialTree, node current) {
    if (current != NULL) {
        print_rectangle_in_order(svg_source, initialTree, KD_get_left_node(current));

        if (KD_get_state(current)) {
            fprintf(svg_source, "\t<rect x=\"%.2lf\" y=\"%.2lf\" width=\"%.2lf\" height=\"%.2lf\" id=\"%s\"\n  style=\"fill:%s;stroke:%s;stroke-width:.5;fill-opacity:0.5;stroke-opacity:1\" />\n", get_rectangle_x(KD_get_data(current)), get_rectangle_y(KD_get_data(current)), get_rectangle_width(KD_get_data(current)), get_rectangle_height(KD_get_data(current)), get_rectangle_id(KD_get_data(current)), get_rectangle_fill(KD_get_data(current)), get_rectangle_stroke(KD_get_data(current)));
        }

        print_rectangle_in_order(svg_source, initialTree, KD_get_right_node(current));
    }
}

void print_circle_in_order(FILE* svg_source, tree initialTree, node current) {
    if (current != NULL) {
        print_circle_in_order(svg_source, initialTree, KD_get_left_node(current));

        if (KD_get_state(current) && get_circle_alive(KD_get_data(current))) {
            if (get_fg(KD_get_data(current)) && get_run_to(KD_get_data(current)) != NULL && KD_get_state(get_run_to(KD_get_data(current)))) {
                fprintf(svg_source, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"%.2lf\" id=\"%s\" stroke=\"grey\" stroke-width=\".5\" fill=\"lightgrey\" fill-opacity = \"0.3\" />\n", get_circle_original_x(KD_get_data(current)), get_circle_original_y(KD_get_data(current)), get_circle_radius(KD_get_data(current)), get_circle_id(KD_get_data(current)));
                fprintf(svg_source, "\t<path fill=\"none\" stroke=\"red\" stroke-dasharray=\"2\" d=\"M%.2lf,%.2lf %.2lf,%.2lf z\"/>\n", get_circle_original_x(KD_get_data(current)), get_circle_original_y(KD_get_data(current)), get_rectangle_center_x(KD_get_data(get_run_to(KD_get_data(current)))), get_rectangle_center_y(KD_get_data(get_run_to(KD_get_data(current)))));
                fprintf(svg_source, "\t<circle r=\"%.2lf\" id=\"%s\" stroke=\"%s\" stroke-width=\".5\" fill=\"%s\" fill-opacity = \"0.5\" >\n", get_circle_radius(KD_get_data(current)), get_circle_id(KD_get_data(current)), get_circle_stroke(KD_get_data(current)), get_circle_fill(KD_get_data(current)));
                fprintf(svg_source, "\t\t<animateMotion dur=\"10s\" repeatCount=\"indefinite\" path=\"M%.2lf,%.2lf %.2lf,%.2lf z\"/>\n", get_circle_original_x(KD_get_data(current)), get_circle_original_y(KD_get_data(current)), get_rectangle_center_x(KD_get_data(get_run_to(KD_get_data(current)))), get_rectangle_center_y(KD_get_data(get_run_to(KD_get_data(current)))));
                fprintf(svg_source, "\t</circle>\n");

            } else {
                fprintf(svg_source, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"%.2lf\" id=\"%s\" stroke=\"%s\" stroke-width=\".5\" fill=\"%s\" fill-opacity = \"0.5\" />\n", get_circle_x(KD_get_data(current)), get_circle_y(KD_get_data(current)), get_circle_radius(KD_get_data(current)), get_circle_id(KD_get_data(current)), get_circle_stroke(KD_get_data(current)), get_circle_fill(KD_get_data(current)));
            }

        } else {
            fprintf(svg_source, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"%.2lf\" id=\"%s\" stroke=\"black\" stroke-width=\".5\" fill=\"black\" fill-opacity = \"0.5\" />\n", get_circle_x(KD_get_data(current)), get_circle_y(KD_get_data(current)), get_circle_radius(KD_get_data(current)), get_circle_id(KD_get_data(current)));
            fprintf(svg_source, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" stroke=\"white\" stroke-width=\".6\"/>\n", get_circle_x(KD_get_data(current)) - get_circle_radius(KD_get_data(current)) / 2, get_circle_y(KD_get_data(current)), get_circle_x(KD_get_data(current)) + get_circle_radius(KD_get_data(current)) / 2, get_circle_y(KD_get_data(current)));  //Horizontal
            fprintf(svg_source, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" stroke=\"white\" stroke-width=\".6\"/>\n", get_circle_x(KD_get_data(current)), get_circle_y(KD_get_data(current)) - get_circle_radius(KD_get_data(current)) / 2, get_circle_x(KD_get_data(current)), get_circle_y(KD_get_data(current)) + get_circle_radius(KD_get_data(current)) / 2);  //Vertical
        }
        print_circle_in_order(svg_source, initialTree, KD_get_right_node(current));
    }
}

void write_on_svg(FILE* svg_source, tree rectTree, tree circleTree, path paths) {
    fprintf(svg_source, "<!-- Rodrigo Mimura Shimomura -->\n <svg viewBox = \"0 0 %.2lf %.2lf\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n", max(get_biggest_x(rectTree), get_biggest_x(circleTree)) + 100, max(get_biggest_y(rectTree), get_biggest_y(circleTree)) + 100);

    if (KD_get_size(rectTree)) {
        print_rectangle_in_order(svg_source, rectTree, KD_get_root_node(rectTree));
    }
    if (KD_get_size(circleTree)) {
        print_circle_in_order(svg_source, circleTree, KD_get_root_node(circleTree));
    }

    fprintf(svg_source, "</svg>");
}

void new_write_on_svg(FILE* svg_source, tree rectTree, tree circleTree, path paths, dynamicList fgData, dynamicList imData, dynamicList nveData) {
    fprintf(svg_source, "<!-- Rodrigo Mimura Shimomura -->\n <svg viewBox = \"0 0 %.2lf %.2lf\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n", max(get_biggest_x(rectTree), get_biggest_x(circleTree)) + 100, max(get_biggest_y(rectTree), get_biggest_y(circleTree)) + 100);

    if (KD_get_size(rectTree)) {
        print_rectangle_in_order(svg_source, rectTree, KD_get_root_node(rectTree));
    }
    if (KD_get_size(circleTree)) {
        print_circle_in_order(svg_source, circleTree, KD_get_root_node(circleTree));
    }

    for (void* auxFg = get_head(fgData); auxFg; auxFg = get_next(fgData, auxFg)) {
        double x, y, number_of_sheltered;
        x = get_temp_x(get_item(fgData, auxFg));
        y = get_temp_y(get_item(fgData, auxFg));
        number_of_sheltered = get_temp_joker(get_item(fgData, auxFg));
        fprintf(svg_source, "\t<text x=\"%.2lf\" y=\"%.2lf\" font-size=\"5\">%.lf</text>\n", x, y, number_of_sheltered);
    }

    for (void* auxIm = get_head(imData); auxIm; auxIm = get_next(imData, auxIm)) {
        double x, y, radius;
        x = get_temp_x(get_item(imData, auxIm));
        y = get_temp_y(get_item(imData, auxIm));
        radius = get_temp_joker(get_item(imData, auxIm));
        fprintf(svg_source, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"%.2lf\" stroke=\"dimgrey\" stroke-width=\".5\" fill=\"dimgrey\" fill-opacity = \"0.1\" />\n", x, y, radius);
    }

    for (void* auxNve = get_head(nveData); auxNve; auxNve = get_next(nveData, auxNve)) {
        double posX, posY, radiation;
        char color[8];
        posX = get_temp_x(get_item(nveData, auxNve));
        posY = get_temp_y(get_item(nveData, auxNve));

        radiation = get_temp_joker(get_item(nveData, auxNve));
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
        fprintf(svg_source, "\t<text x=\"%.2lf\" y=\"%.2lf\" fill=\"white\" font-size=\"1.5\">%.2lf</text>\n", posX + 0.5, posY + 2, radiation);
    }

    fprintf(svg_source, "</svg>");
}