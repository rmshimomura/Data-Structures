#include "libs.h"

#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

void get_arguments(int argc, char** argv, path paths, flag flags);    
void get_data(tree blocks, hash residents, hash location, path paths, flag flags);        
int find_nx(path paths);

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