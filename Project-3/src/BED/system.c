#include "system.h"

void set_input_directory(path paths, char* newSet);
void set_output_directory(path paths, char* newSet);
void set_initial_geo_file(path paths, char* newSet);
void set_current_qry_file(path paths, char* newSet);
void set_qry_name(path paths, char* newSet);
void set_geo_name(path paths, char* newSet);
void set_people_file(path paths, char* newSet);
void set_final_SVG_file_name(path paths, char* newSet);
void set_path_initial_geo_file(path paths, char* newSet);
void set_path_current_qry_file(path paths, char* newSet);
void set_path_people_file(path paths, char* newSet);
void set_path_original_SVG(path paths, char* newSet);
void set_path_modified_SVG(path paths, char* newSet);
void set_path_TXT_with_qry(path paths, char* newSet);
void set_final_graphic_SVG(path paths, char* newSet);
void set_path_final_TXT(path paths, char* newSet);

int get_arguments(int argc, char** argv, path paths) {
    
    if (argc < 2) return -1;

    bool input_directory_inserted = false;
    bool qry_executed = false;
    bool pm_inserted = false;

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
        } else if(!strcmp(argv[i], "-pm")){
            char* pm_file = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            strcpy(pm_file, argv[i + 1]);
            set_people_file(paths, pm_file);
            pm_inserted = true;
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
        set_path_initial_geo_file(paths, path_initial_geo_file);

    } else {
        char* input_directory = calloc(3, sizeof(char));
        strcpy(input_directory, "./");
        set_input_directory(paths, input_directory);
        char* path_intial_geo_file = calloc(strlen(get_input_directory(paths)) + strlen(get_initial_geo_file(paths)) + 2, sizeof(char));
        strcpy(path_intial_geo_file, get_input_directory(paths));
        strcat(path_intial_geo_file, get_initial_geo_file(paths));
        set_path_initial_geo_file(paths, path_intial_geo_file);
    }

    if(pm_inserted){
        char* path_people_file = calloc(strlen(get_input_directory(paths)) + strlen(get_people_file(paths)) + 10, sizeof(char));
        sprintf(path_people_file, "%s%s", get_input_directory(paths), get_people_file(paths));
        set_path_people_file(paths, path_people_file);
    }

    if (qry_executed) {
        char* path_current_qry_file = calloc(strlen(get_input_directory(paths)) + strlen(get_current_qry_file(paths)) + 10, sizeof(char));
        sprintf(path_current_qry_file, "%s%s", get_input_directory(paths), get_current_qry_file(paths));
        set_path_current_qry_file(paths, path_current_qry_file);
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