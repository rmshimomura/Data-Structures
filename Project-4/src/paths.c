#include "paths.h"

typedef struct generalPaths {
    char* input_directory;         //Diretorio de entrada
    char* output_directory;        //Diretorio de saida
    char* initial_geo_file;        //Arquivo .geo (sem diretorio)
    char* current_qry_file;        //Arquivo .qry (sem diretorio)
    char* roads_file;               //Arquivo .via (sem diretorio)
    char* qry_name;                //Nome do .qry sem o .qry
    char* geo_name;                //Nome do .geo sem o .geo
    char* final_SVG_file_name;     //Nome do .svg final sem o .svg
    char* path_roads_file;          //Path ate o .via inicial
    char* path_initial_geo_file;   //Path ate o .geo inicial
    char* path_current_qry_file;   //Path ate o .qry que esta sendo usado
    char* path_original_SVG;       //Path ate o svg que sera gerado sem alteracoes
    char* path_modified_SVG;       //Path ate o svg com as alteracoes do qry
    char* path_TXT_with_qry;       //Path ate o txt com as alteracoes do qry

} generalPaths;

path create_general_paths() {
    generalPaths* aux = calloc(1, sizeof(generalPaths));
    return aux;
}

char* get_input_directory(path paths) {
    generalPaths* aux = paths;
    return aux->input_directory;
}

char* get_output_directory(path paths) {
    generalPaths* aux = paths;
    return aux->output_directory;
}

char* get_initial_geo_file(path paths) {
    generalPaths* aux = paths;
    return aux->initial_geo_file;
}

char* get_current_qry_file(path paths) {
    generalPaths* aux = paths;
    return aux->current_qry_file;
}

char* get_roads_file(path paths){
    generalPaths* aux = paths;
    return aux->roads_file;
}

char* get_qry_name(path paths) {
    generalPaths* aux = paths;
    return aux->qry_name;
}

char* get_geo_name(path paths) {
    generalPaths* aux = paths;
    return aux->geo_name;
}

char* get_final_SVG_file_name(path paths) {
    generalPaths* aux = paths;
    return aux->final_SVG_file_name;
}

char* get_path_roads_file(path paths){
    generalPaths* aux = paths;
    return aux->path_roads_file;
}

char* get_path_initial_geo_file(path paths) {
    generalPaths* aux = paths;
    return aux->path_initial_geo_file;
}

char* get_path_current_qry_file(path paths) {
    generalPaths* aux = paths;
    return aux->path_current_qry_file;
}

char* get_path_original_SVG(path paths) {
    generalPaths* aux = paths;
    return aux->path_original_SVG;
}

char* get_path_modified_SVG(path paths) {
    generalPaths* aux = paths;
    return aux->path_modified_SVG;
}

char* get_path_TXT_with_qry(path paths) {
    generalPaths* aux = paths;
    return aux->path_TXT_with_qry;
}

void set_input_directory(path paths, char* newSet) {
    generalPaths* aux = paths;
    aux->input_directory = newSet;
}

void set_output_directory(path paths, char* newSet) {
    generalPaths* aux = paths;
    aux->output_directory = newSet;
}

void set_initial_geo_file(path paths, char* newSet) {
    generalPaths* aux = paths;
    aux->initial_geo_file = newSet;
}

void set_current_qry_file(path paths, char* newSet) {
    generalPaths* aux = paths;
    aux->current_qry_file = newSet;
}

void set_qry_name(path paths, char* newSet) {
    generalPaths* aux = paths;
    aux->qry_name = newSet;
}

void set_geo_name(path paths, char* newSet) {
    generalPaths* aux = paths;
    aux->geo_name = newSet;
}

void set_roads_file(path paths, char* newSet) {
    generalPaths* aux = paths;
    aux->roads_file = newSet;
}

void set_final_SVG_file_name(path paths, char* newSet) {
    generalPaths* aux = paths;
    aux->final_SVG_file_name = newSet;
}

void set_path_roads_file(path paths, char* newSet) {
    generalPaths* aux = paths;
    aux->path_roads_file = newSet;
}

void set_path_initial_geo_file(path paths, char* newSet) {
    generalPaths* aux = paths;
    aux->path_initial_geo_file = newSet;
}

void set_path_current_qry_file(path paths, char* newSet) {
    generalPaths* aux = paths;
    aux->path_current_qry_file = newSet;
}

void set_path_original_SVG(path paths, char* newSet) {
    generalPaths* aux = paths;
    aux->path_original_SVG = newSet;
}

void set_path_modified_SVG(path paths, char* newSet) {
    generalPaths* aux = paths;
    aux->path_modified_SVG = newSet;
}

void set_path_TXT_with_qry(path paths, char* newSet) {
    generalPaths* aux = paths;
    aux->path_TXT_with_qry = newSet;
}

void showPaths(path paths) {
    generalPaths* aux = paths;
    if (aux->input_directory) {
        puts("DirBaseDeEntrada :");
        puts(aux->input_directory);
        puts("====================");
    }
    if (aux->output_directory) {
        puts("DirBaseDeSaida : ");
        puts(aux->output_directory);
        puts("====================");
    }
    if (aux->initial_geo_file) {
        puts("GeoInicial : ");
        puts(aux->initial_geo_file);
        puts("====================");
    }
    if (aux->current_qry_file) {
        puts("QryConsultas : ");
        puts(aux->current_qry_file);
        puts("====================");
    }
    if(aux->roads_file){
        puts("ArquivoVia : ");
        puts(aux->roads_file);
        puts("====================");
    }
    if (aux->final_SVG_file_name) {
        puts("NomeArqSVGFinal : ");
        puts(aux->final_SVG_file_name);
        puts("====================");
    }
    if (aux->geo_name) {
        puts("NomeGEO : ");
        puts(aux->geo_name);
        puts("====================");
    }
    if (aux->qry_name) {
        puts("NomeQRY : ");
        puts(aux->qry_name);
        puts("====================");
    }
    if (aux->path_roads_file) {
        puts("Path arquivo Via : ");
        puts(aux->path_roads_file);
        puts("====================");
    }
    if (aux->path_initial_geo_file) {
        puts("PathArquivoGeoInicial : ");
        puts(aux->path_initial_geo_file);
        puts("====================");
    }

    if (aux->path_current_qry_file) {
        puts("PathArquivoQryAtual : ");
        puts(aux->path_current_qry_file);
        puts("====================");
    }
    if (aux->path_modified_SVG) {
        puts("PathDoSvgComOQryExecutado : ");
        puts(aux->path_modified_SVG);
        puts("====================");
    }
    if (aux->path_original_SVG) {
        puts("PathDoSvgDoGeoSemMudanca : ");
        puts(aux->path_original_SVG);
        puts("====================");
    }
    if (aux->path_TXT_with_qry) {
        puts("PathDoTXTComOQryExecutado : ");
        puts(aux->path_TXT_with_qry);
        puts("====================");
    }
    
}

void freePaths(path paths) {
    generalPaths* aux = paths;
    if (aux->input_directory) {
        free(aux->input_directory);
    }
    if (aux->output_directory) {
        free(aux->output_directory);
    }
    if (aux->initial_geo_file) {
        free(aux->initial_geo_file);
    }
    if (aux->final_SVG_file_name) {
        free(aux->final_SVG_file_name);
    }
    if(aux->current_qry_file){
        free(aux->current_qry_file);
    }
    if(aux->roads_file) {
        free(aux->roads_file);
    }
    if (aux->geo_name) {
        free(aux->geo_name);
    }
    if (aux->qry_name) {
        free(aux->qry_name);
    }
    if(aux->path_roads_file){
        free(aux->path_roads_file);
    }
    if (aux->path_initial_geo_file) {
        free(aux->path_initial_geo_file);
    }
    if (aux->path_current_qry_file) {
        free(aux->path_current_qry_file);
    }
    if (aux->path_modified_SVG) {
        free(aux->path_modified_SVG);
    }
    if (aux->path_original_SVG) {
        free(aux->path_original_SVG);
    }
    if (aux->path_TXT_with_qry) {
        free(aux->path_TXT_with_qry);
    }
    

    free(paths);
}