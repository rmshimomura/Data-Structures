#include "bibliotecas.h"

#ifndef PATHS_H
#define PATHS_H

path create_general_paths();
//Funcoes do tipo get servem para revelar os dados passados nos argumentos
//que serao usados nas funcoes da qry, svg... (nomes autoexplicativos do que elas retornam)//
char* get_input_directory(path paths);
char* get_output_directory(path paths);
char* get_initial_geo_file(path paths);
char* get_current_qry_file(path paths);
char* get_qry_name(path paths);
char* get_geo_name(path paths);
char* get_final_SVG_file_name(path paths);
char* get_path_initial_geo_file(path paths);
char* get_path_current_qry_file(path paths);
char* get_path_original_SVG(path paths);
char* get_path_modified_SVG(path paths);
char* get_path_TXT_with_qry(path paths);
char* get_path_final_TXT(path paths);

//Debug
void showPaths(path paths);

//Liberar os espacos alocados da struct dos paths
void freePaths(path paths);

#endif