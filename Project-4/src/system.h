#include "libs.h"

#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

void get_arguments(int argc, char** argv, path paths, flag flags);    
int structures_size(void* paths);
void get_data (void* connections, void* blocks, void* blocks_hash, void* paths, void* flags, void* view_box);
void get_functions(void* connections, void* blocks, void* blocks_hash, void* paths, void* flags, void* view_box, FILE* txt_results);
void format_qry_results(void* connections, void* blocks, void* blocks_hash, void* paths, void* flags, void* view_box);

path create_general_paths(); 

char* get_input_directory(path paths);
char* get_output_directory(path paths);
char* get_initial_geo_file(path paths);
char* get_current_qry_file(path paths);
char* get_people_file(path paths);
char* get_qry_name(path paths);
char* get_geo_name(path paths);
char* get_final_SVG_file_name(path paths);
char* get_path_people_file(path paths);
char* get_people_file(path paths);
char* get_path_initial_geo_file(path paths);
char* get_path_current_qry_file(path paths);
char* get_path_original_SVG(path paths);
char* get_path_modified_SVG(path paths);
char* get_path_TXT_with_qry(path paths);
char* get_final_graphic_SVG(path paths);
char* get_path_final_TXT(path paths);

#endif