#include "libs.h"

#ifndef PATHS_H
#define PATHS_H

path create_general_paths();
char* get_input_directory(path paths);
char* get_output_directory(path paths);
char* get_initial_geo_file(path paths);
char* get_current_qry_file(path paths);
char* get_qry_name(path paths);
char* get_geo_name(path paths);
char* get_people_file(path paths);
char* get_final_SVG_file_name(path paths);
char* get_path_people_file(path paths);
char* get_path_initial_geo_file(path paths);
char* get_path_current_qry_file(path paths);
char* get_path_original_SVG(path paths);
char* get_path_modified_SVG(path paths);
char* get_path_TXT_with_qry(path paths);
char* get_path_final_TXT(path paths);
void showPaths(path paths);
void freePaths(path paths);

#endif