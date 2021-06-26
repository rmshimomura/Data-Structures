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
    char rect_name[100];
    void** people_inside;
    void* original_rect;
    int number_of_people_inside;

} data_s;

typedef struct sorting {
    data_s* data;
    int size;

} sorting_t;

typedef struct circleData {
    char circle_name[100];
    double radiation;

} circle_data_t;

typedef struct imSorting {
    circle_data_t* data;
    int pos;

} imSorting_t;

typedef struct tempFile {
    double x, y, joker;

} tempFile_t;

int sorting_names_rectangle(const void* pos1, const void* pos2) {
    const data_s* aux1 = pos1;
    const data_s* aux2 = pos2;
    return strcmp(aux1->rect_name, aux2->rect_name);
}

int sorting_names_circle(const void* pos1, const void* pos2) {
    const circle_data_t* aux1 = pos1;
    const circle_data_t* aux2 = pos2;
    return strcmp(aux1->circle_name, aux2->circle_name);
}

int sort_names(const void* name1, const void* name2) {
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

void dpi_in_order(tree rectangleTree, node currentNode, double x, double y, char** names, int* index, int level) {
    if (currentNode) {
        if (inside(x, y, 0, 0, get_rectangle_x(KD_get_data(currentNode)), get_rectangle_y(KD_get_data(currentNode)), get_rectangle_width(KD_get_data(currentNode)), get_rectangle_height(KD_get_data(currentNode))) && KD_get_state(currentNode)) {
            names[*index] = calloc(strlen(get_rectangle_id(KD_get_data(currentNode))) + 1, sizeof(char));
            strcpy(names[*index], get_rectangle_id(KD_get_data(currentNode)));
            KD_set_state(currentNode, 0);
            KD_set_size(rectangleTree, KD_get_size(rectangleTree) - 1);
            *index = *index + 1;
        }

        if (level % 2 == 0) {
            if (x < get_rectangle_x(KD_get_data(currentNode))) {
                dpi_in_order(rectangleTree, KD_get_left_node(currentNode), x, y, names, index, level + 1);

            } else if (x >= get_rectangle_x(KD_get_data(currentNode))) {
                dpi_in_order(rectangleTree, KD_get_left_node(currentNode), x, y, names, index, level + 1);
                dpi_in_order(rectangleTree, KD_get_right_node(currentNode), x, y, names, index, level + 1);
            }

        } else if (level % 2 == 1) {
            if (y < get_rectangle_y(KD_get_data(currentNode))) {
                dpi_in_order(rectangleTree, KD_get_left_node(currentNode), x, y, names, index, level + 1);

            } else if (y >= get_rectangle_y(KD_get_data(currentNode))) {
                dpi_in_order(rectangleTree, KD_get_left_node(currentNode), x, y, names, index, level + 1);
                dpi_in_order(rectangleTree, KD_get_right_node(currentNode), x, y, names, index, level + 1);
            }
        }
    }
}

void dpi(tree rectangleTree, double x, double y, path paths) {
    FILE* results = fopen(get_path_TXT_with_qry(paths), "a+");
    setvbuf(results, 0, _IONBF, 0);
    int size = KD_get_size(rectangleTree);

    int pos = 0;
    char** names = calloc(KD_get_size(rectangleTree), sizeof(char*));

    if (!size) {
        fprintf(results, "dpi\nTree size = 0 :( \n");
        fprintf(results, "========================================================");
        fclose(results);
        return;
    }

    void* root = KD_get_root_node(rectangleTree);
    fprintf(results, "\ndpi:\n\n");
    dpi_in_order(rectangleTree, root, x, y, names, &pos, 0);
    qsort(names, pos, sizeof(char*), sort_names);
    for (int i = 0; i < pos; i++) {
        fprintf(results, "%s\n", names[i]);
    }
    for (int i = 0; i < size; i++) {
        free(names[i]);
    }
    free(names);
    fprintf(results, "\n========================================================\n");
    fclose(results);
}

void dr_in_order(tree rectangleTree, node current, node foundId, char** names, int* index, int level) {
    if (current) {
        if (inside(get_rectangle_x(KD_get_data(current)), get_rectangle_y(KD_get_data(current)), get_rectangle_width(KD_get_data(current)), get_rectangle_height(KD_get_data(current)), get_rectangle_x(KD_get_data(foundId)), get_rectangle_y(KD_get_data(foundId)), get_rectangle_width(KD_get_data(foundId)), get_rectangle_height(KD_get_data(foundId))) && get_rectangle_id(KD_get_data(current)) != get_rectangle_id(KD_get_data(foundId))) {
            names[*index] = calloc(strlen(get_rectangle_id(KD_get_data(current))) + 1, sizeof(char));
            strcpy(names[*index], get_rectangle_id(KD_get_data(current)));

            KD_set_state(current, 0);
            KD_set_size(rectangleTree, KD_get_size(rectangleTree) - 1);
            *index = *index + 1;
        }

        if (level % 2 == 0) {
            if (get_rectangle_x(KD_get_data(current)) < get_rectangle_x(KD_get_data(foundId))) {
                dr_in_order(rectangleTree, KD_get_right_node(current), foundId, names, index, level + 1);

            } else {
                dr_in_order(rectangleTree, KD_get_left_node(current), foundId, names, index, level + 1);
                dr_in_order(rectangleTree, KD_get_right_node(current), foundId, names, index, level + 1);
            }

        } else {
            if (get_rectangle_y(KD_get_data(current)) < get_rectangle_y(KD_get_data(foundId))) {
                dr_in_order(rectangleTree, KD_get_right_node(current), foundId, names, index, level + 1);

            } else {
                dr_in_order(rectangleTree, KD_get_left_node(current), foundId, names, index, level + 1);
                dr_in_order(rectangleTree, KD_get_right_node(current), foundId, names, index, level + 1);
            }
        }
    }
}

void dr(tree rectangleTree, char* id, path paths) {
    FILE* results = fopen(get_path_TXT_with_qry(paths), "a+");
    setvbuf(results, 0, _IONBF, 0);
    char** names = calloc(KD_get_size(rectangleTree), sizeof(char*));
    int size = KD_get_size(rectangleTree);

    if (!KD_get_size(rectangleTree)) {
        fprintf(results, "dr\nTree size = 0 :( \n");
        fclose(results);
        return;
    }

    int pos = 0;
    fprintf(results, "\ndr:\n\n");

    if (!KD_search_ID(KD_get_root_node(rectangleTree), id)) {
        fprintf(results, "id does not match any nodes in the tree :( \n");
        fprintf(results, "========================================================\n");
        fclose(results);
        return;
    }

    dr_in_order(rectangleTree, KD_get_root_node(rectangleTree), KD_search_ID(KD_get_root_node(rectangleTree), id), names, &pos, 0);
    qsort(names, pos, sizeof(char*), sort_names);
    for (int i = 0; i < pos; i++) {
        fprintf(results, "%s\n", names[i]);
    }
    for (int i = 0; i < size; i++) {
        free(names[i]);
    }
    free(names);
    fprintf(results, "\n========================================================\n");
    fclose(results);
}

void fg_in_order_rectangle(tree rectangleTree, FILE* results, void* current_rect, void* current_circ) {
    if (current_rect) {
        if (sqrt(pow((get_circle_x(KD_get_data(current_circ)) - get_rectangle_center_x(KD_get_data(current_rect))), 2) + (pow((get_circle_y(KD_get_data(current_circ)) - get_rectangle_center_y(KD_get_data(current_rect))), 2))) < get_nearest_distance(KD_get_data(current_circ)) && KD_get_state(current_rect)) {
            set_nearest_distance(KD_get_data(current_circ), sqrt(pow(get_circle_x(KD_get_data(current_circ)) - get_rectangle_center_x(KD_get_data(current_rect)), 2) + pow((get_circle_y(KD_get_data(current_circ)) - get_rectangle_center_y(KD_get_data(current_rect))), 2)));
            set_run_to(KD_get_data(current_circ), current_rect);
            set_fg(KD_get_data(current_circ), true);
        }

        fg_in_order_rectangle(rectangleTree, results, KD_get_left_node(current_rect), current_circ);

        fg_in_order_rectangle(rectangleTree, results, KD_get_right_node(current_rect), current_circ);
    }
}

void fg_in_order_circle(tree rectangleTree, tree circleTree, FILE* results, void* current_rect, void* current_circ, double x, double y, double radius) {
    if (current_circ) {
        fg_in_order_circle(rectangleTree, circleTree, results, current_rect, KD_get_left_node(current_circ), x, y, radius);

        if ((pow(abs(x - get_circle_x(KD_get_data(current_circ))), 2) + pow(abs(y - get_circle_y(KD_get_data(current_circ))), 2) <= pow(radius, 2))) {
            fg_in_order_rectangle(rectangleTree, results, KD_get_root_node(rectangleTree), current_circ);  //Find closest rectangle

            if (!get_vector_of_people_started(KD_get_data(get_run_to(KD_get_data(current_circ))))) {
                set_vector_of_people_started(KD_get_data(get_run_to(KD_get_data(current_circ))), 1);
            }

            allocate_vector_of_people(KD_get_data(get_run_to(KD_get_data(current_circ))));

            int exist = 0;

            for (int i = 0; i < get_number_of_people_inside(KD_get_data(get_run_to(KD_get_data(current_circ)))); i++) {  //Compare if someone that is already inside is trying to enter again

                if (!strcmp(get_circle_id(KD_get_data(get_vector_of_people(KD_get_data(get_run_to(KD_get_data(current_circ))))[i])), get_circle_id(KD_get_data(current_circ)))) {
                    exist = 1;
                }
            }

            if (!exist) {
                set_addresses(KD_get_data(get_run_to(KD_get_data(current_circ))), current_circ, get_number_of_people_inside(KD_get_data(get_run_to(KD_get_data(current_circ)))));
                set_number_of_people_inside(KD_get_data(get_run_to(KD_get_data(current_circ))), get_number_of_people_inside(KD_get_data(get_run_to(KD_get_data(current_circ)))) + 1);
            }
        }

        fg_in_order_circle(rectangleTree, circleTree, results, current_rect, KD_get_right_node(current_circ), x, y, radius);
    }
}

void loop_rectangle_tree(sorting_t rectangles_to_sort, void* current_rect, int* size) {
    if (current_rect) {
        if (get_vector_of_people_started(KD_get_data(current_rect))) {
            strcpy(rectangles_to_sort.data[*size].rect_name, get_rectangle_id(KD_get_data(current_rect)));
            rectangles_to_sort.data[*size].people_inside = get_vector_of_people(KD_get_data(current_rect));
            rectangles_to_sort.data[*size].number_of_people_inside = get_number_of_people_inside(KD_get_data(current_rect));
            rectangles_to_sort.data[*size].original_rect = current_rect;
            *size = *size + 1;
        }

        loop_rectangle_tree(rectangles_to_sort, KD_get_left_node(current_rect), size);
        loop_rectangle_tree(rectangles_to_sort, KD_get_right_node(current_rect), size);
    }
}

void store_rectangles_to_sort(tree rectangleTree, FILE* results, dynamicList tempInfo) {
    sorting_t rectangles_to_sort;
    rectangles_to_sort.data = calloc(KD_get_size(rectangleTree), sizeof(data_s));
    rectangles_to_sort.size = 0;
    int size = 0;

    loop_rectangle_tree(rectangles_to_sort, KD_get_root_node(rectangleTree), &size);

    qsort(rectangles_to_sort.data, size, sizeof(data_s), sorting_names_rectangle);

    for (int i = 0; i < size; i++) {
        void** arrayOfPeople = rectangles_to_sort.data[i].people_inside;
        char** temp = calloc(rectangles_to_sort.data[i].number_of_people_inside, sizeof(char*));
        tempFile_t* fgData = calloc(1, sizeof(tempFile_t));

        for (int j = 0; j < rectangles_to_sort.data[i].number_of_people_inside; j++) {
            temp[j] = calloc(strlen(get_circle_id(KD_get_data(rectangles_to_sort.data[i].people_inside[j]))) + 1, sizeof(char));
            strcpy(temp[j], get_circle_id(KD_get_data(rectangles_to_sort.data[i].people_inside[j])));
        }

        qsort(temp, rectangles_to_sort.data[i].number_of_people_inside, sizeof(char*), sort_names);

        fprintf(results, "✷ %s:\n", rectangles_to_sort.data[i].rect_name);

        for (int j = 0; j < rectangles_to_sort.data[i].number_of_people_inside; j++) {
            fprintf(results, "-> %s\n", temp[j]);
        }

        if (rectangles_to_sort.data[i].number_of_people_inside) {
            fprintf(results, "\n");
        }

        for (int j = 0; j < rectangles_to_sort.data[i].number_of_people_inside; j++) {
            free(temp[j]);
        }

        free(temp);

        fgData->x = get_rectangle_x(KD_get_data(rectangles_to_sort.data[i].original_rect)) + 2;
        fgData->y = get_rectangle_y(KD_get_data(rectangles_to_sort.data[i].original_rect)) + 5;
        fgData->joker = rectangles_to_sort.data[i].number_of_people_inside;

        insert(tempInfo, fgData);

        free_vector_of_people(KD_get_data(rectangles_to_sort.data[i].original_rect));
        set_number_of_people_inside(KD_get_data(rectangles_to_sort.data[i].original_rect), 0);
        set_vector_of_people_started(KD_get_data(rectangles_to_sort.data[i].original_rect), 0);
    }

    free(rectangles_to_sort.data);
}

void update_circles_new_positions(tree circleTree, void* current_circ) {
    if (current_circ) {
        if (get_run_to(KD_get_data(current_circ))) {
            set_circle_x(KD_get_data(current_circ), get_rectangle_center_x(KD_get_data(get_run_to(KD_get_data(current_circ)))));
            set_circle_y(KD_get_data(current_circ), get_rectangle_center_y(KD_get_data(get_run_to(KD_get_data(current_circ)))));
        }

        update_circles_new_positions(circleTree, KD_get_left_node(current_circ));

        update_circles_new_positions(circleTree, KD_get_right_node(current_circ));
    }
}

void fg(tree rectangleTree, tree circleTree, double x, double y, double radius, path paths, dynamicList tempInfo) {
    FILE* results = fopen(get_path_TXT_with_qry(paths), "a+");
    setvbuf(results, 0, _IONBF, 0);
    fg_in_order_circle(rectangleTree, circleTree, results, KD_get_root_node(rectangleTree), KD_get_root_node(circleTree), x, y, radius);
    fprintf(results, "FG: \n\n");
    update_circles_new_positions(circleTree, KD_get_root_node(circleTree));
    store_rectangles_to_sort(rectangleTree, results, tempInfo);
    fprintf(results, "========================================================\n");
    fclose(results);
}

char* color_picker(double radiation) {
    if (radiation < 25)
        return "#00ffff";
    else if (radiation >= 25 && radiation < 50)
        return "#00ff00";
    else if (radiation >= 50 && radiation < 100)
        return "#ff00ff";
    else if (radiation >= 100 && radiation < 250)
        return "#0000ff";
    else if (radiation >= 250 && radiation < 500)
        return "#800080";
    else if (radiation >= 500 && radiation < 1000)
        return "#000080";
    else if (radiation >= 1000 && radiation < 8000)
        return "#ff0000";
    else if (radiation >= 8000)
        return "#000000";
}

void im_in_order_shadows(tree shadows, node currentShadowPolygon, node currentCircle, double xMeteor, double yMeteor) {
    if (currentShadowPolygon) {
        void* line = NT_get_data(currentShadowPolygon);  //Now has the array of segments
        int intersections = 0;

        for (int i = 0; i < 3; i++) {
            void* info = at_pos_array(line, i);
            void* point1 = get_P1(info);
            void* point2 = get_P2(info);

            if (get_line_intersection(get_point_x(point1), get_point_y(point1), get_point_x(point2), get_point_y(point2), get_circle_x(KD_get_data(currentCircle)), get_circle_y(KD_get_data(currentCircle)), xMeteor, yMeteor)) {
                if (get_circle_x(KD_get_data(currentCircle)) != get_point_x(point1) && get_circle_x(KD_get_data(currentCircle)) != get_point_x(point2) && get_circle_y(KD_get_data(currentCircle)) != get_point_y(point1) && get_circle_y(KD_get_data(currentCircle)) != get_point_y(point2))

                    intersections++;
            }
        }

        if (intersections) {
            set_inside_n_shadows(KD_get_data(currentCircle), get_inside_n_shadows(KD_get_data(currentCircle)) + 1);
        }

        if (get_circle_x(KD_get_data(currentCircle)) < get_minimum_x(NT_get_data(currentShadowPolygon))) {
            im_in_order_shadows(shadows, NT_get_left_node(currentShadowPolygon), currentCircle, xMeteor, yMeteor);

        } else {
            im_in_order_shadows(shadows, NT_get_left_node(currentShadowPolygon), currentCircle, xMeteor, yMeteor);
            im_in_order_shadows(shadows, NT_get_right_node(currentShadowPolygon), currentCircle, xMeteor, yMeteor);
        }
    }
}

void im_in_order_circles(tree shadows, node currentCircle, double radiation, double xMeteor, double yMeteor, imSorting_t circlesToSort, int* index) {
    if (currentCircle) {
        set_inside_n_shadows(KD_get_data(currentCircle), 0);
        im_in_order_shadows(shadows, NT_get_root_node(shadows), currentCircle, xMeteor, yMeteor);

        if (!get_inside_n_shadows(KD_get_data(currentCircle))) {
            set_radiation(KD_get_data(currentCircle), get_radiation(KD_get_data(currentCircle)) + radiation);

        } else {
            set_radiation(KD_get_data(currentCircle), get_radiation(KD_get_data(currentCircle)) + (pow(0.8, get_inside_n_shadows(KD_get_data(currentCircle))) * radiation));
        }

        set_circle_fill(KD_get_data(currentCircle), color_picker(get_radiation(KD_get_data(currentCircle))));
        set_circle_stroke(KD_get_data(currentCircle), color_picker(get_radiation(KD_get_data(currentCircle))));

        if (get_radiation(KD_get_data(currentCircle)) >= 1000 && get_radiation(KD_get_data(currentCircle)) < 8000) {
            strcpy(circlesToSort.data[*(index)].circle_name, get_circle_id(KD_get_data(currentCircle)));
            circlesToSort.data[*(index)].radiation = get_radiation(KD_get_data(currentCircle));
            *index = *index + 1;

            set_circle_marked_for_death(KD_get_data(currentCircle), true);

        } else if (get_radiation(KD_get_data(currentCircle)) >= 8000) {
            if (get_circle_alive(KD_get_data(currentCircle))) {
                strcpy(circlesToSort.data[*(index)].circle_name, get_circle_id(KD_get_data(currentCircle)));
                circlesToSort.data[*(index)].radiation = get_radiation(KD_get_data(currentCircle));
                *index = *index + 1;

                set_circle_alive(KD_get_data(currentCircle), false);
            }
        }

        im_in_order_circles(shadows, KD_get_left_node(currentCircle), radiation, xMeteor, yMeteor, circlesToSort, index);
        im_in_order_circles(shadows, KD_get_right_node(currentCircle), radiation, xMeteor, yMeteor, circlesToSort, index);
    }
}

void im(tree rectangleTree, tree circleTree, dynamicList listOfTreesShadows, double xMeteor, double yMeteor, double radiation, path paths, dynamicList tempInfo) {
    FILE* results = fopen(get_path_TXT_with_qry(paths), "a+");
    setvbuf(results, 0, _IONBF, 0);
    tree shadows = NT_create_tree();
    dynamicList segments = create_list();
    build_segments(rectangleTree, segments, KD_get_root_node(rectangleTree));
    add_wrap_around_rectangle(rectangleTree, circleTree, segments);
    void* vertexArray = build_vertex_array(segments, xMeteor, yMeteor);
    store_shadow_polygons(shadows, vertexArray, segments, xMeteor, yMeteor);
    fprintf(results, "IM: \n\n");

    imSorting_t toSortCircles;
    toSortCircles.data = calloc(KD_get_size(circleTree), sizeof(circle_data_t));
    int pos = 0;
    im_in_order_circles(shadows, KD_get_root_node(circleTree), radiation, xMeteor, yMeteor, toSortCircles, &pos);
    qsort(toSortCircles.data, pos, sizeof(circle_data_t), sorting_names_circle);

    for (int i = 0; i < pos; i++) {
        if (toSortCircles.data[i].radiation >= 1000 && toSortCircles.data[i].radiation < 8000) {
            fprintf(results, "%s - Morte Iminente\n", toSortCircles.data[i].circle_name);

        } else if (toSortCircles.data[i].radiation >= 8000) {
            fprintf(results, "%s - Morte Instantanea\n", toSortCircles.data[i].circle_name);
        }
    }

    fprintf(results, "\n========================================================\n");
    free(toSortCircles.data);
    tempFile_t* imData = calloc(1, sizeof(tempFile_t));
    imData->x = xMeteor;
    imData->y = yMeteor;
    imData->joker = radiation / 3;
    insert(tempInfo, imData);
    void* auxNode = insert(listOfTreesShadows, shadows);
    set_data_radiation(auxNode, radiation);
    set_data_x_meteor(auxNode, xMeteor);
    set_data_y_meteor(auxNode, yMeteor);
    free(vertexArray);
    free_list_of_segments(segments);
    fclose(results);
}

void t30_in_order(tree circleTree, node currentCircle, char** allNames, int* pos) {
    if (currentCircle) {
        if (get_circle_marked_for_death(KD_get_data(currentCircle)) && get_circle_alive(KD_get_data(currentCircle))) {
            allNames[*pos] = calloc(strlen(get_circle_id(KD_get_data(currentCircle))) + 1, sizeof(char));
            strcpy(allNames[*pos], get_circle_id(KD_get_data(currentCircle)));
            *pos = *pos + 1;

            set_circle_alive(KD_get_data(currentCircle), false);
        }

        t30_in_order(circleTree, KD_get_left_node(currentCircle), allNames, pos);
        t30_in_order(circleTree, KD_get_right_node(currentCircle), allNames, pos);
    }
}

void t30(tree circleTree, path paths) {
    FILE* results = fopen(get_path_TXT_with_qry(paths), "a+");
    setvbuf(results, 0, _IONBF, 0);
    char** allNames = calloc(KD_get_size(circleTree), sizeof(char*));
    int pos = 0;
    fprintf(results, "T30: \n\n");
    t30_in_order(circleTree, KD_get_root_node(circleTree), allNames, &pos);
    qsort(allNames, pos, sizeof(char*), sort_names);

    for (int i = 0; i < pos; i++) {
        fprintf(results, "ID %s morto por tempo\n", allNames[i]);
    }

    fprintf(results, "\n========================================================\n");
    fclose(results);

    for (int i = 0; i < KD_get_size(circleTree); i++) {
        free(allNames[i]);
    }

    free(allNames);
}

void nve_update_radiation(void* currentPolygon, double xNve, double yNve, int* inside_polygons, double xMeteor, double yMeteor) {
    int insideNPolygons = 0;
    void* line = NT_get_data(currentPolygon);
    int intersections = 0;

    for (int i = 0; i < 3; i++) {
        void* info = at_pos_array(line, i);
        void* point1 = get_P1(info);
        void* point2 = get_P2(info);

        if (get_line_intersection(get_point_x(point1), get_point_y(point1), get_point_x(point2), get_point_y(point2), xNve, yNve, xMeteor, yMeteor)) {
            if (xNve != get_point_x(point1) && xNve != get_point_x(point2) && yNve != get_point_y(point1) && yNve != get_point_y(point2))

                intersections++;
        }
    }

    if (intersections) {
        insideNPolygons++;
    }

    *inside_polygons += (insideNPolygons);
}

void nve_in_order(tree shadowTree, node currentListPosition, node currentPolygon, int* insideNPolygons, double x, double y, double xMeteor, double yMeteor) {
    if (currentPolygon) {
        nve_update_radiation(currentPolygon, x, y, insideNPolygons, xMeteor, yMeteor);

        if (x < get_minimum_x(NT_get_data(currentPolygon))) {
            nve_in_order(shadowTree, currentListPosition, NT_get_left_node(currentPolygon), insideNPolygons, x, y, xMeteor, yMeteor);

        } else {
            nve_in_order(shadowTree, currentListPosition, NT_get_left_node(currentPolygon), insideNPolygons, x, y, xMeteor, yMeteor);
            nve_in_order(shadowTree, currentListPosition, NT_get_right_node(currentPolygon), insideNPolygons, x, y, xMeteor, yMeteor);
        }
    }
}

void nve(dynamicList listOfTreesShadows, path paths, double x, double y, dynamicList tempInfo) {
    FILE* results = fopen(get_path_TXT_with_qry(paths), "a+");
    setvbuf(results, 0, _IONBF, 0);
    double radiationAtThePoint = 0.0;
    void* posAuxList = get_head(listOfTreesShadows);

    for (int i = 0; i < get_size(listOfTreesShadows); i++) {
        int inside_n_polygons = 0;
        void* treeAux = get_item(listOfTreesShadows, posAuxList);
        void* treeNodeAux = NT_get_root_node(treeAux);
        nve_in_order(treeAux, posAuxList, treeNodeAux, &inside_n_polygons, x, y, get_data_x_meteor(posAuxList), get_data_y_meteor(posAuxList));

        if (!inside_n_polygons)
            radiationAtThePoint += (get_data_radiation(posAuxList));
        else {
            double factor = 1;
            for (int i = 0; i < inside_n_polygons; i++) {
                factor *= 0.8;
            }
            radiationAtThePoint += (factor * get_data_radiation(posAuxList));
        }

        posAuxList = get_next(listOfTreesShadows, posAuxList);
    }

    tempFile_t* nveData = calloc(1, sizeof(tempFile_t));
    nveData->x = x;
    nveData->y = y;
    nveData->joker = radiationAtThePoint;
    insert(tempInfo, nveData);

    fprintf(results, "NVE: \n\n(%.6lf, %.6lf) has %.6lf mSv\n", x, y, radiationAtThePoint);

    fprintf(results, "\n========================================================\n");

    fclose(results);
}

double get_temp_x(void* node) {
    tempFile_t* aux = node;
    return aux->x;
}

double get_temp_y(void* node) {
    tempFile_t* aux = node;
    return aux->y;
}

double get_temp_joker(void* node) {
    tempFile_t* aux = node;
    return aux->joker;
}