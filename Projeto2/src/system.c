#include "system.h"

#include "bibliotecas.h"
#include "circle.h"
#include "dynamicList.h"
#include "kdTree.h"
#include "paths.h"
#include "qry.h"
#include "rectangle.h"
#include "svg.h"

//Evitar sets desnecessarios
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

        if (!strcmp(argv[i], "-e")) {  //Diretório-base de entrada (BED)

            char* input_directory = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            strcpy(input_directory, argv[i + 1]);
            
            if(input_directory[strlen(input_directory) - 1] != '/'){
            
                input_directory = realloc(input_directory, strlen(input_directory) + 2);
                strcat(input_directory, "/");
            
            }

            input_directory_inserted = true;
            set_input_directory(paths, input_directory);

        } else if (!strcmp(argv[i], "-f")) {  //Arquivo .geo inicial. Este arquivo deve estar sob o diretório BED.
            
            char* initial_geo_file = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            char* geo_name = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            int index = 0;
            int name_position = 0;
            bool found = false;
            strcpy(initial_geo_file, argv[i + 1]);
            set_initial_geo_file(paths, initial_geo_file);

            for (int i = 0; i < strlen(initial_geo_file); i++) {  //Se for passado um caminho relativo na localizacao do .geo inicial
                
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

        } else if (!strcmp(argv[i], "-o")) {  //Diretório-base de saída (BSD)

            char* output_directory = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            strcpy(output_directory, argv[i+1]);
            
            if(output_directory[strlen(output_directory) - 1] != '/'){

                output_directory = realloc(output_directory, strlen(output_directory) + 2);
                strcat(output_directory, "/");
            
            }

            set_output_directory(paths, output_directory);

        } else if (!strcmp(argv[i], "-q")) {  //Arquivo com consultas. Este arquivo deve estar sob o diretório BED.
            
            char* qry_file = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            char* qry_name = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            strcpy(qry_file, argv[i + 1]);
            set_current_qry_file(paths, qry_file);
            int index = 0;
            int name_position = 0;
            bool found = false;

            for (int i = 0; i < strlen(qry_file); i++) {  //Se for passado um caminho relativo na localizacao do .geo inicial
            
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

    //Apos coletar todas as informacoes, esta na hora de arrumar e organizar todos os dados reunidos, nomes autoexplicativos
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
        set_input_directory(paths,input_directory);
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
    node rectangleRoot = KDgetRootNode(rectangleTree);
    node circleRoot = KDgetRootNode(circleTree);

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
            setType(circleTree, 'c');
            void* aux_circle = createCircle();
            setRunTo(aux_circle, NULL);
            setFg(aux_circle, false);
            setNearestDistance(aux_circle, __DBL_MAX__);
            setCircleStroke(aux_circle, circStroke);
            setCircleFill(aux_circle, circFill);
            fscanf(arq, "%s %lf %lf %lf", id, &x, &y, &radius);
            setCircleId(aux_circle, id);
            setCircleX(aux_circle, x);
            setCircleY(aux_circle, y);
            setCircleOriginalX(aux_circle, x);
            setCircleOriginalY(aux_circle, y);
            setCircleRadius(aux_circle, radius);
            setRadiation(aux_circle, 0.0);
            setCircleAlive(aux_circle, true);
            setCircleMarkedForDeath(aux_circle, false);
            if (getBiggestX(circleTree) < x + radius) {
                setBiggestX(circleTree, x + radius);
            }
            if (getBiggestY(circleTree) < y + radius) {
                setBiggestY(circleTree, y + radius);
            }
            if (firstCir) {
                circleRoot = KDinsertCirc(circleTree, circleRoot, circleRoot, aux_circle, 0);
                firstCir = false;
            } else {
                KDinsertCirc(circleTree, circleRoot, circleRoot, aux_circle, 0);
            }
        } else if (!strcmp(command, "r")) {
            setType(rectangleTree, 'r');
            void* aux_rect = createRectangle();
            setRectangleStroke(aux_rect, rectStroke);
            setRectangleFill(aux_rect, rectFill);
            fscanf(arq, "%s %lf %lf %lf %lf", id, &x, &y, &width, &height);
            setRectangleId(aux_rect, id);
            setRectangleX(aux_rect, x);
            setRectangleY(aux_rect, y);
            setRectangleWidth(aux_rect, width);
            setRectangleHeight(aux_rect, height);
            setRectangleCenterX(aux_rect, getRectangleX(aux_rect) + (getRectangleWidth(aux_rect)) / 2);
            setRectangleCenterY(aux_rect, getRectangleY(aux_rect) + (getRectangleHeight(aux_rect)) / 2);
            setVectorOfPeopleStarted(aux_rect, 0);
            setNumberOfPeopleInside(aux_rect, 0);
            if (getBiggestX(rectangleTree) < x + width) {
                setBiggestX(rectangleTree, x + width);
            }
            if (getBiggestY(rectangleTree) < y + height) {
                setBiggestY(rectangleTree, y + height);
            }

            if (firstRet) {
                rectangleRoot = KDinsertRect(rectangleTree, rectangleRoot, rectangleRoot, aux_rect, 0);
                firstRet = false;
            } else {
                KDinsertRect(rectangleTree, rectangleRoot, rectangleRoot, aux_rect, 0);
            }
        }
    }
    KDsetRootNode(rectangleTree, rectangleRoot);
    KDsetRootNode(circleTree, circleRoot);

    fclose(arq);
}

void get_functions(tree rectangleTree, tree circleTree, dynamicList listOfTreesShadows, path paths) {  //Leitura do .qry
    FILE* Svg_Modificado = fopen(get_path_modified_SVG(paths), "w+");
    setvbuf(Svg_Modificado, 0, _IONBF, 0);
    FILE* comandos = fopen(get_path_current_qry_file(paths), "r");
    setvbuf(comandos, 0, _IONBF, 0);
    dynamicList fgData = createList();
    dynamicList imData = createList();
    dynamicList nveData = createList();
    double x = 0.0;
    double y = 0.0;
    double radius = 0;
    char id[100];
    char comando[5];
    double radiation = 0.0;
    while (fscanf(comandos, "%s", comando) != -1) {
        if (!strcmp(comando, "dpi")) {
            fscanf(comandos, "%lf %lf", &x, &y);
            dpi(rectangleTree, x, y, paths);
        } else if (!strcmp(comando, "dr")) {
            fscanf(comandos, "%s", id);
            dr(rectangleTree, id, paths);

        } else if (!strcmp(comando, "fg")) {
            fscanf(comandos, "%lf %lf %lf", &x, &y, &radius);
            fg(rectangleTree, circleTree, x, y, radius, paths, fgData);

        } else if (!strcmp(comando, "im")) {
            fscanf(comandos, "%lf %lf %lf", &x, &y, &radiation);
            im(rectangleTree, circleTree, listOfTreesShadows, x, y, radiation, paths, imData);
        } else if (!strcmp(comando, "t30")) {
            t30(circleTree, paths);
        } else if (!strcmp(comando, "nve")) {
            fscanf(comandos, "%lf %lf", &x, &y);
            nve(listOfTreesShadows, paths, x, y, nveData);
        }
    }
    new_write_on_svg(Svg_Modificado, rectangleTree, circleTree, paths, fgData, imData, nveData);
    freeList(fgData);
    freeList(imData);
    freeList(nveData);
    fclose(comandos);
    fclose(Svg_Modificado);
}