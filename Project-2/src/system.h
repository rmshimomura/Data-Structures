#include "bibliotecas.h"

#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

void get_data(tree rectangleTree, tree circleTree, path paths);  
int get_arguments(int argc, char** argv, path paths);            
void get_functions(tree rectangleTree, tree circleTree, dynamicList listOfTreesShadows, path paths);
path create_general_paths(); 


char* get_input_directory(path paths);
char* get_output_directory(path paths);
char* get_initial_geo_file(path paths);
char* get_current_qry_file(path paths);
char* get_qry_name(path paths);
char* get_geo_name(path paths);
char* get_final_SVG_file_name(path paths);
char* getTituloGrafFinal(path paths);
char* get_path_initial_geo_file(path paths);
char* get_path_current_qry_file(path paths);
char* get_path_original_SVG(path paths);
char* get_path_modified_SVG(path paths);
char* get_path_TXT_with_qry(path paths);
char* get_final_graphic_SVG(path paths);
char* get_path_final_TXT(path paths);

#endif