#include "system.h"

#include "bibliotecas.h"
#include "circle.h"
#include "dynamicList.h"
#include "kdTree.h"
#include "paths.h"
#include "qry.h"
#include "rectangle.h"
#include "svg.h"

// Avoid unnecessary sets
void set_input_directory(path paths, char* newSet);
void set_output_directory(path paths, char* newSet);
void set_initial_geo_file(path paths, char* newSet);
void set_current_qry_file(path paths, char* newSet);
void set_qry_name(path paths, char* newSet);
void set_geo_name(path paths, char* newSet);
void set_final_SVG_file_name(path paths, char* newSet);
void set_path_initial_geo_file(path paths, char* newSet);
void set_path_current_qry_file(path paths, char* newSet);
void set_path_original_SVG(path paths, char* newSet);
void set_path_modified_SVG(path paths, char* newSet);
void set_path_TXT_with_qry(path paths, char* newSet);
void set_final_graphic_SVG(path paths, char* newSet);
void set_path_final_TXT(path paths, char* newSet);

int get_arguments(int argc, char** argv, path paths) {
    if (argc < 2) return -1;

    bool input_directory_inserted = false;
    bool qry_executed = false;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-e")) { 

            char* input_directory = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            strcpy(input_directory, argv[i + 1]);

            if (input_directory[strlen(input_directory) - 1] != '/') {
                input_directory = realloc(input_directory, strlen(input_directory) + 2);
                strcat(input_directory, "/");
            }

            input_directory_inserted = true;
            set_input_directory(paths, input_directory);

        } else if (!strcmp(argv[i], "-f")) {  

            char* initial_geo_file = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            char* geo_name = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            int index = 0;
            int name_position = 0;
            bool found = false;
            strcpy(initial_geo_file, argv[i + 1]);
            set_initial_geo_file(paths, initial_geo_file);

            for (int i = 0; i < strlen(initial_geo_file); i++) {  

                if (initial_geo_file[i] == '/') {
                    index = i;
                    found = true;
                }
            }

            if (found) {
                for (int i = index + 1; i < strlen(initial_geo_file); i++) {
                    if (initial_geo_file[i] == '.') {
                        geo_name[name_position] = '\0';
                        break;

                    } else {
                        geo_name[name_position] = initial_geo_file[i];
                        name_position++;
                    }
                }

                set_geo_name(paths, geo_name);

            } else {
                strcpy(geo_name, argv[i + 1]);

                for (int i = 0; i < strlen(geo_name); i++) {
                    if (geo_name[i] == '.') {
                        geo_name[i] = '\0';
                    }
                }

                set_geo_name(paths, geo_name);
            }

        } else if (!strcmp(argv[i], "-o")) {  

            char* output_directory = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            strcpy(output_directory, argv[i + 1]);

            if (output_directory[strlen(output_directory) - 1] != '/') {
                output_directory = realloc(output_directory, strlen(output_directory) + 2);
                strcat(output_directory, "/");
            }

            set_output_directory(paths, output_directory);

        } else if (!strcmp(argv[i], "-q")) {  

            char* qry_file = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            char* qry_name = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            strcpy(qry_file, argv[i + 1]);
            set_current_qry_file(paths, qry_file);
            int index = 0;
            int name_position = 0;
            bool found = false;

            for (int i = 0; i < strlen(qry_file); i++) {  

                if (qry_file[i] == '/') {
                    index = i;
                    found = true;
                }
            }

            if (found) {
                for (int i = index + 1; i < strlen(qry_file); i++) {
                    if (qry_file[i] == '.') {
                        qry_name[name_position] = '\0';
                        break;
                    } else {
                        qry_name[name_position] = qry_file[i];
                        name_position++;
                    }
                }

                set_qry_name(paths, qry_name);
            } else {
                strcpy(qry_name, argv[i + 1]);
                for (int i = 0; i < strlen(qry_name); i++) {
                    if (qry_name[i] == '.') {
                        qry_name[i] = '\0';
                    }
                }

                set_qry_name(paths, qry_name);
            }
            qry_executed = true;
        }
    }

    // After collecting all data from argv, we're going to organize for building correct paths

    char* path_original_SVG = calloc(strlen(get_output_directory(paths)) + strlen(get_geo_name(paths)) + 10, sizeof(char));
    sprintf(path_original_SVG, "%s%s.svg", get_output_directory(paths), get_geo_name(paths));
    set_path_original_SVG(paths, path_original_SVG);

    if (input_directory_inserted) {
        char* path_initial_geo_file = calloc(strlen(get_input_directory(paths)) + strlen(get_initial_geo_file(paths)) + 2, sizeof(char));
        strcpy(path_initial_geo_file, get_input_directory(paths));
        strcat(path_initial_geo_file, get_initial_geo_file(paths));
        set_initial_geo_file(paths, path_initial_geo_file);

    } else {
        char* input_directory = calloc(3, sizeof(char));
        strcpy(input_directory, "./");
        set_input_directory(paths, input_directory);
        char* path_intial_geo_file = calloc(strlen(get_input_directory(paths)) + strlen(get_initial_geo_file(paths)) + 2, sizeof(char));
        strcpy(path_intial_geo_file, get_input_directory(paths));
        strcat(path_intial_geo_file, get_initial_geo_file(paths));
        set_initial_geo_file(paths, path_intial_geo_file);
    }

    if (qry_executed) {
        char* path_current_qry_file = calloc(strlen(get_input_directory(paths)) + strlen(get_current_qry_file(paths)) + 10, sizeof(char));
        sprintf(path_current_qry_file, "%s%s", get_input_directory(paths), get_current_qry_file(paths));
        set_current_qry_file(paths, path_current_qry_file);
        char* path_txt_with_qry = calloc(strlen(get_output_directory(paths)) + strlen(get_geo_name(paths)) + strlen(get_qry_name(paths)) + 10, sizeof(char));
        char* path_modified_svg = calloc(strlen(get_output_directory(paths)) + strlen(get_geo_name(paths)) + strlen(get_qry_name(paths)) + 10, sizeof(char));
        sprintf(path_txt_with_qry, "%s%s-%s.txt", get_output_directory(paths), get_geo_name(paths), get_qry_name(paths));
        set_path_TXT_with_qry(paths, path_txt_with_qry);
        sprintf(path_modified_svg, "%s%s-%s.svg", get_output_directory(paths), get_geo_name(paths), get_qry_name(paths));
        set_path_modified_SVG(paths, path_modified_svg);
        return 1;
    }

    return 0;
}

void get_data(tree rectangleTree, tree circleTree, path paths) {
    FILE* arq = fopen(get_path_initial_geo_file(paths), "r");
    setvbuf(arq, 0, _IONBF, 0);
    double x, y, width, height, radius;
    char id[100], rectStroke[100], rectFill[100], circStroke[100], circFill[100], command[20];
    bool firstRet = true;
    bool firstCir = true;
    node rectangleRoot = KD_get_root_node(rectangleTree);
    node circleRoot = KD_get_root_node(circleTree);

    while (fscanf(arq, "%s", command) != -1) {
        if (!strcmp(command, "cc")) {
            fscanf(arq, "%s", rectStroke);
            if (!strcmp(rectStroke, "@")) {
                strcpy(rectStroke, "none");
            }
        } else if (!strcmp(command, "cp")) {
            fscanf(arq, "%s", rectFill);
            if (!strcmp(rectFill, "@")) {
                strcpy(rectFill, "none");
            }
        } else if (!strcmp(command, "bc")) {
            fscanf(arq, "%s", circStroke);
            if (!strcmp(circStroke, "@")) {
                strcpy(circStroke, "none");
            }
        } else if (!strcmp(command, "pc")) {
            fscanf(arq, "%s", circFill);
            if (!strcmp(circFill, "@")) {
                strcpy(circFill, "none");
            }
        } else if (!strcmp(command, "c")) {
            set_type(circleTree, 'c');
            void* aux_circle = create_circle();
            set_run_to(aux_circle, NULL);
            set_fg(aux_circle, false);
            set_nearest_distance(aux_circle, __DBL_MAX__);
            set_circle_stroke(aux_circle, circStroke);
            set_circle_fill(aux_circle, circFill);
            fscanf(arq, "%s %lf %lf %lf", id, &x, &y, &radius);
            set_circle_id(aux_circle, id);
            set_circle_x(aux_circle, x);
            set_circle_y(aux_circle, y);
            set_circle_original_x(aux_circle, x);
            set_circle_original_y(aux_circle, y);
            set_circle_radius(aux_circle, radius);
            set_radiation(aux_circle, 0.0);
            set_circle_alive(aux_circle, true);
            set_circle_marked_for_death(aux_circle, false);
            if (get_biggest_x(circleTree) < x + radius) {
                set_biggest_x(circleTree, x + radius);
            }
            if (get_biggest_y(circleTree) < y + radius) {
                set_biggest_y(circleTree, y + radius);
            }
            if (firstCir) {
                circleRoot = KD_insert_circ(circleTree, circleRoot, circleRoot, aux_circle, 0);
                firstCir = false;
            } else {
                KD_insert_circ(circleTree, circleRoot, circleRoot, aux_circle, 0);
            }
        } else if (!strcmp(command, "r")) {
            set_type(rectangleTree, 'r');
            void* aux_rect = create_rectangle();
            set_rectangle_stroke(aux_rect, rectStroke);
            set_rectangle_fill(aux_rect, rectFill);
            fscanf(arq, "%s %lf %lf %lf %lf", id, &x, &y, &width, &height);
            set_rectangle_id(aux_rect, id);
            set_rectangle_x(aux_rect, x);
            set_rectangle_y(aux_rect, y);
            set_rectangle_width(aux_rect, width);
            set_rectangle_height(aux_rect, height);
            set_rectangle_center_x(aux_rect, get_rectangle_x(aux_rect) + (get_rectangle_width(aux_rect)) / 2);
            set_rectangle_center_y(aux_rect, get_rectangle_y(aux_rect) + (get_rectangle_height(aux_rect)) / 2);
            set_vector_of_people_started(aux_rect, 0);
            set_number_of_people_inside(aux_rect, 0);
            if (get_biggest_x(rectangleTree) < x + width) {
                set_biggest_x(rectangleTree, x + width);
            }
            if (get_biggest_y(rectangleTree) < y + height) {
                set_biggest_y(rectangleTree, y + height);
            }

            if (firstRet) {
                rectangleRoot = KD_insert_rect(rectangleTree, rectangleRoot, rectangleRoot, aux_rect, 0);
                firstRet = false;
            } else {
                KD_insert_rect(rectangleTree, rectangleRoot, rectangleRoot, aux_rect, 0);
            }
        }
    }
    KD_set_root_node(rectangleTree, rectangleRoot);
    KD_set_root_node(circleTree, circleRoot);

    fclose(arq);
}

void get_functions(tree rectangleTree, tree circleTree, dynamicList listOfTreesShadows, path paths) {  //Leitura do .qry
    FILE* modified_SVG = fopen(get_path_modified_SVG(paths), "w+");
    setvbuf(modified_SVG, 0, _IONBF, 0);
    FILE* arq = fopen(get_path_current_qry_file(paths), "r");
    setvbuf(arq, 0, _IONBF, 0);
    dynamicList fgData = create_list();
    dynamicList imData = create_list();
    dynamicList nveData = create_list();
    double x = 0.0;
    double y = 0.0;
    double radius = 0;
    char id[100];
    char commands[5];
    double radiation = 0.0;
    while (fscanf(arq, "%s", commands) != -1) {
        if (!strcmp(commands, "dpi")) {
            fscanf(arq, "%lf %lf", &x, &y);
            dpi(rectangleTree, x, y, paths);
        } else if (!strcmp(commands, "dr")) {
            fscanf(arq, "%s", id);
            dr(rectangleTree, id, paths);

        } else if (!strcmp(commands, "fg")) {
            fscanf(arq, "%lf %lf %lf", &x, &y, &radius);
            fg(rectangleTree, circleTree, x, y, radius, paths, fgData);

        } else if (!strcmp(commands, "im")) {
            fscanf(arq, "%lf %lf %lf", &x, &y, &radiation);
            im(rectangleTree, circleTree, listOfTreesShadows, x, y, radiation, paths, imData);
        } else if (!strcmp(commands, "t30")) {
            t30(circleTree, paths);
        } else if (!strcmp(commands, "nve")) {
            fscanf(arq, "%lf %lf", &x, &y);
            nve(listOfTreesShadows, paths, x, y, nveData);
        }
    }
    new_write_on_svg(modified_SVG, rectangleTree, circleTree, paths, fgData, imData, nveData);
    free_list(fgData);
    free_list(imData);
    free_list(nveData);
    fclose(arq);
    fclose(modified_SVG);
}