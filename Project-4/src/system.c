#include "system.h"

#include "AVL_Tree/AVL.h"
#include "Dynamic_list/dynamic_list.h"
#include "Graph/graph.h"
#include "Hash/hash.h"
#include "block.h"
#include "checks.h"
#include "paths.h"
#include "svg.h"

void set_input_directory(path paths, char* newSet);
void set_output_directory(path paths, char* newSet);
void set_initial_geo_file(path paths, char* newSet);
void set_current_qry_file(path paths, char* newSet);
void set_qry_name(path paths, char* newSet);
void set_geo_name(path paths, char* newSet);
void set_roads_file(path paths, char* newSet);
void set_final_SVG_file_name(path paths, char* newSet);
void set_path_initial_geo_file(path paths, char* newSet);
void set_path_current_qry_file(path paths, char* newSet);
void set_path_roads_file(path paths, char* newSet);
void set_path_original_SVG(path paths, char* newSet);
void set_path_modified_SVG(path paths, char* newSet);
void set_path_TXT_with_qry(path paths, char* newSet);

void get_arguments(int argc, char** argv, path paths, flag flags) {
    
    if (argc < 2) return;

    bool input_directory_inserted = false;
    bool qry_executed = false;
    bool via_inserted = false;

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

            set_qry_inserted(flags, true);
            qry_executed = true;

        } else if (!strcmp(argv[i], "-v")) {
            
            char* via_file = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            strcpy(via_file, argv[i + 1]);
            set_roads_file(paths, via_file);
            via_inserted = true;
            set_roads_inserted(flags, true);

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

    if (via_inserted) {

        char* path_via_file = calloc(strlen(get_input_directory(paths)) + strlen(get_roads_file(paths)) + 10, sizeof(char));
        sprintf(path_via_file, "%s%s", get_input_directory(paths), get_roads_file(paths));
        set_path_roads_file(paths, path_via_file);

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

    }
    
}

void get_data (void* connections, void* blocks, void* blocks_hash, void* paths, void* flags) {

    FILE* file_blocks = fopen(get_path_initial_geo_file(paths), "r");
    setvbuf(file_blocks, 0, _IONBF, 0);

    void* blocks_root = get_root(blocks);

    char command[20], cep[50], cfill[30], cstroke[30];
    double x, y, w, h;
    char sw[10];

    while (fscanf(file_blocks, "%s", command) != EOF) {
        
        if (!strcmp(command, "cq")) {
            
            fscanf(file_blocks, "%s %s %s", sw, cfill, cstroke);

        }

        if (!strcmp(command, "q")) {

            fscanf(file_blocks, "%s %lf %lf %lf %lf", cep, &x, &y, &w, &h);
            void* new_block = create_block();
            set_block_properties(new_block, cep, x, y, w, h, sw, cfill, cstroke);
            blocks_root = insert(blocks, blocks_root, new_block, compare_x);
            hash_table_insert_data(blocks_hash, cep, new_block);
            
        }
    }

    if(get_roads_inserted(flags)) {

        FILE* file_roads = fopen(get_path_roads_file(paths), "r");
        setvbuf(file_roads, 0, _IONBF, 0);

        create_graph_with_data(connections, file_roads);

        fclose(file_roads);

    }

    fclose(file_blocks);
    
    set_root(blocks, blocks_root);

}

int structures_size(void* paths) {

    int size = 0;
    FILE* arq = fopen(get_path_roads_file(paths), "r");
    setvbuf(arq, 0, _IONBF, 0);
    fscanf(arq, "%d", &size);

    fclose(arq);

    return size > 0 ? size : -1;

}

void format_qry_results(void* connections, void* blocks, void* blocks_hash, void* paths, void* flags) {

    FILE* txt_results = fopen(get_path_TXT_with_qry(paths), "w+");
    setvbuf(txt_results, 0, _IONBF, 0);
    fprintf(txt_results, "Rodrigo Mimura Shimomura\n");
    fprintf(txt_results, "FUNCTIONS EXECUTED:\n\n====================================================\n");
    get_functions(connections, blocks, blocks_hash, paths, flags, txt_results);
    fclose(txt_results);
    
}

void get_functions(void* connections, void* blocks, void* blocks_hash, void* paths, void* flags, FILE* txt_results) {

    FILE* modified_SVG = fopen(get_path_modified_SVG(paths), "w+");
    setvbuf(modified_SVG, 0, _IONBF, 0);
    FILE* functions_file = fopen(get_path_current_qry_file(paths), "r");
    setvbuf(functions_file, 0, _IONBF, 0);

    fprintf(modified_SVG, "<!-- Rodrigo Mimura Shimomura -->\n <svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n");

    char command[512], cep[512], face, cmc[512], cmr[512];
    double num, x, y, w, h, f, limiar;
    

    while(fscanf(functions_file, "%s", command) != EOF) {

        if(!strcmp(command, "@o?")) {

            fscanf(functions_file, "%s %c %lf", cep, &face, &num);

        } else if (!strcmp(command, "catac")) {

            fscanf(functions_file, "%lf %lf %lf %lf", &x, &y, &w, &h);

        } else if (!strcmp(command, "rv")) {

            fscanf(functions_file, "%lf %lf %lf %lf %lf", &x, &y, &w, &h, &f);

        } else if (!strcmp(command, "cx")) {

            fscanf(functions_file, "%lf", &limiar);

        } else if (!strcmp(command, "p?")) {

            fscanf(functions_file, "%s %c %lf %s %s", cep, &face, &num, cmc, cmr);

        }

    }



    void* blocks_root = get_root(blocks);

    recursive_print_svg(blocks_root, modified_SVG);





    fprintf(modified_SVG, "</svg>\n");
    fclose(functions_file);
    fclose(modified_SVG);

}