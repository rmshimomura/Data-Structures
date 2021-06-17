#include "system.h"

#include "bibliotecas.h"
#include "circle.h"
#include "kdTree.h"
#include "paths.h"
#include "qry.h"
#include "rectangle.h"
#include "svg.h"

//Evitar sets desnecessarios

void allocateDirbaseDeEntrada(path paths, int size);
void allocateDirBaseDeSaida(path paths, int size);
void allocateGeoInicial(path paths, int size);
void allocateQryConsultas(path paths, int size);
void allocateNomeQRY(path paths, int size);
void allocateNomeGEO(path paths, int size);
void allocateNomeArqSVGFinal(path paths, int size);
void allocatePathArquivoGeoInicial(path paths, int size);
void allocatePathArquivoQryAtual(path paths, int size);
void allocatePathDoSvgDoGeoSemMudanca(path paths, int size);
void allocatePathDoSvgComOQryExecutado(path paths, int size);
void allocatePathDoTXTComOQryExecutado(path paths, int size);
void allocatePathTXTFinal(path paths, int size);

void reallocateDirbaseDeEntrada(path paths, int newSize);
void reallocateDirBaseDeSaida(path paths, int newSize);
void reallocateGeoInicial(path paths, int newSize);
void reallocateQryConsultas(path paths, int newSize);
void reallocateNomeQRY(path paths, int newSize);
void reallocateNomeGEO(path paths, int newSize);
void reallocateNomeArqSVGFinal(path paths, int newSize);
void reallocatePathArquivoGeoInicial(path paths, int newSize);
void reallocatePathArquivoQryAtual(path paths, int newSize);
void reallocatePathDoSvgDoGeoSemMudanca(path paths, int newSize);
void reallocatePathDoSvgComOQryExecutado(path paths, int newSize);
void reallocatePathDoTXTComOQryExecutado(path paths, int newSize);
void reallocatePathTXTFinal(path paths, int newSize);

void strcpyDirbaseDeEntrada(path paths, char* assemble);
void strcpyDirBaseDeSaida(path paths, char* assemble);
void strcpyGeoInicial(path paths, char* assemble);
void strcpyQryConsultas(path paths, char* assemble);
void strcpyNomeQRY(path paths, char* assemble);
void strcpyNomeGEO(path paths, char* assemble);
void strcpyNomeArqSVGFinal(path paths, char* assemble);
void strcpyPathArquivoGeoInicial(path paths, char* assemble);
void strcpyPathArquivoQryAtual(path paths, char* assemble);
void strcpyPathDoSvgDoGeoSemMudanca(path paths, char* assemble);
void strcpyPathDoSvgComOQryExecutado(path paths, char* assemble);
void strcpyPathDoTXTComOQryExecutado(path paths, char* assemble);
void strcpyPathTXTFinal(path paths, char* assemble);

void strcatDirbaseDeEntrada(path paths, char* assemble);
void strcatDirBaseDeSaida(path paths, char* assemble);
void strcatGeoInicial(path paths, char* assemble);
void strcatQryConsultas(path paths, char* assemble);
void strcatNomeQRY(path paths, char* assemble);
void strcatNomeGEO(path paths, char* assemble);
void strcatNomeArqSVGFinal(path paths, char* assemble);
void strcatPathArquivoGeoInicial(path paths, char* assemble);
void strcatPathArquivoQryAtual(path paths, char* assemble);
void strcatPathDoSvgDoGeoSemMudanca(path paths, char* assemble);
void strcatPathDoSvgComOQryExecutado(path paths, char* assemble);
void strcatPathDoTXTComOQryExecutado(path paths, char* assemble);
void strcatPathTXTFinal(path paths, char* assemble);

int getArguments(int argc, char** argv, path paths) {
    if (argc < 2) {
        puts("Argumentos faltando.");
        return -1;
    }
    bool pathEntrada = false;
    bool qryvalido = true;
    bool consultaFeita = false;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-e")) {  //Diretório-base de entrada (BED)
            allocateDirbaseDeEntrada(paths, strlen(argv[i + 1]) + 1);
            strcpyDirbaseDeEntrada(paths, argv[i + 1]);
            if (getDirBaseDeEntrada(paths)[strlen(getDirBaseDeEntrada(paths)) - 1] != '/') {
                reallocateDirbaseDeEntrada(paths, strlen(getDirBaseDeEntrada(paths)) + 2);
                strcatDirbaseDeEntrada(paths, "/");
            }
            pathEntrada = true;

        } else if (!strcmp(argv[i], "-f")) {  //Arquivo .geo inicial. Este arquivo deve estar sob o diretório BED.
            char* temp = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            char* tempNomeGEO = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            allocateGeoInicial(paths, strlen(argv[i + 1]) + 1);
            allocateNomeGEO(paths, strlen(argv[i + 1]) + 1);
            int index = 0;
            int posNome = 0;
            bool found = false;
            strcpy(temp, argv[i + 1]);
            strcpyGeoInicial(paths, argv[i + 1]);
            for (int i = 0; i < strlen(temp); i++) {  //Se for passado um caminho relativo na localizacao do .geo inicial
                if (temp[i] == '/') {
                    index = i;
                    found = true;
                }
            }
            if (found) {
                for (int i = index + 1; i < strlen(temp); i++) {
                    if (temp[i] == '.') {
                        tempNomeGEO[posNome] = '\0';
                        break;
                    } else {
                        tempNomeGEO[posNome] = temp[i];
                        posNome++;
                    }
                }
                strcpyNomeGEO(paths, tempNomeGEO);
            } else {
                strcpy(tempNomeGEO, argv[i + 1]);
                for (int i = 0; i < strlen(tempNomeGEO); i++) {
                    if (tempNomeGEO[i] == '.') {
                        tempNomeGEO[i] = '\0';
                    }
                }
                strcpyNomeGEO(paths, tempNomeGEO);
            }
            free(temp);
            free(tempNomeGEO);
        } else if (!strcmp(argv[i], "-o")) {  //Diretório-base de saída (BSD)
            allocateDirBaseDeSaida(paths, strlen(argv[i + 1]) + 1);
            strcpyDirBaseDeSaida(paths, argv[i + 1]);
            if (getDirBaseDeSaida(paths)[strlen(getDirBaseDeSaida(paths)) - 1] != '/') {
                reallocateDirBaseDeSaida(paths, strlen(getDirBaseDeSaida(paths)) + 2);
                strcatDirBaseDeSaida(paths, "/");
            }

        } else if (!strcmp(argv[i], "-q")) {  //Arquivo com consultas. Este arquivo deve estar sob o diretório BED.
            char* temp = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            char* tempNomeQRY = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            allocateQryConsultas(paths, strlen(argv[i + 1]) + 1);
            allocateNomeQRY(paths, strlen(argv[i + 1]) + 1);
            strcpyQryConsultas(paths, argv[i + 1]);
            strcpy(temp, argv[i + 1]);
            int index;
            int posNome = 0;
            bool found = false;
            for (int i = 0; i < strlen(temp); i++) {  //Se for passado um caminho relativo na localizacao do .geo inicial
                if (temp[i] == '/') {
                    index = i;
                    found = true;
                }
            }
            if (found) {
                for (int i = index + 1; i < strlen(temp); i++) {
                    if (temp[i] == '.') {
                        tempNomeQRY[posNome] = '\0';
                        break;
                    } else {
                        tempNomeQRY[posNome] = temp[i];
                        posNome++;
                    }
                }
                strcpyNomeQRY(paths, tempNomeQRY);
            } else {
                strcpy(tempNomeQRY, argv[i + 1]);
                for (int i = 0; i < strlen(tempNomeQRY); i++) {
                    if (tempNomeQRY[i] == '.') {
                        tempNomeQRY[i] = '\0';
                    }
                }
                strcpyNomeQRY(paths, tempNomeQRY);
            }
            free(temp);
            free(tempNomeQRY);
            consultaFeita = true;
        }
    }

    //Apos coletar todas as informacoes, esta na hora de arrumar e organizar todos os dados reunidos, nomes autoexplicativos
    char* tempPathDoSvgDoGeoSemMudanca = calloc(strlen(getDirBaseDeSaida(paths)) + strlen(getNomeGEO(paths)) + 10, sizeof(char));
    sprintf(tempPathDoSvgDoGeoSemMudanca, "%s%s.svg", getDirBaseDeSaida(paths), getNomeGEO(paths));
    allocatePathDoSvgDoGeoSemMudanca(paths, strlen(tempPathDoSvgDoGeoSemMudanca) + 1);
    strcpyPathDoSvgDoGeoSemMudanca(paths, tempPathDoSvgDoGeoSemMudanca);
    if (pathEntrada) {
        allocatePathArquivoGeoInicial(paths, strlen(getDirBaseDeEntrada(paths)) + strlen(getGeoInicial(paths)) + 2);
        strcpyPathArquivoGeoInicial(paths, getDirBaseDeEntrada(paths));
        strcatPathArquivoGeoInicial(paths, getGeoInicial(paths));
    } else {
        allocateDirbaseDeEntrada(paths, 3);
        strcpyDirbaseDeEntrada(paths, "./");
        char* tempElse = calloc(strlen(getDirBaseDeEntrada(paths)) + strlen(getGeoInicial(paths)) + 2, sizeof(char));
        allocatePathArquivoGeoInicial(paths, strlen(getDirBaseDeEntrada(paths)) + strlen(getGeoInicial(paths)) + 2);
        strcpy(tempElse, getDirBaseDeEntrada(paths));
        strcat(tempElse, getGeoInicial(paths));
        strcpyPathArquivoGeoInicial(paths, tempElse);
        free(tempElse);
    }

    if (consultaFeita) {
        char* tempp = calloc(strlen(getDirBaseDeEntrada(paths)) + strlen(getQryConsultas(paths)) + 10, sizeof(char));
        allocatePathArquivoQryAtual(paths, strlen(getDirBaseDeEntrada(paths)) + strlen(getQryConsultas(paths)) + 2);

        sprintf(tempp, "%s%s", getDirBaseDeEntrada(paths), getQryConsultas(paths));
        strcpyPathArquivoQryAtual(paths, tempp);
        allocatePathDoSvgComOQryExecutado(paths, strlen(getDirBaseDeSaida(paths)) + strlen(getNomeGEO(paths)) + strlen(getNomeQRY(paths)) + 9);
        allocatePathDoTXTComOQryExecutado(paths, strlen(getDirBaseDeSaida(paths)) + strlen(getNomeGEO(paths)) + strlen(getNomeQRY(paths)) + 9);
        char* temp1 = calloc(strlen(getDirBaseDeSaida(paths)) + strlen(getNomeGEO(paths)) + strlen(getNomeQRY(paths)) + 10, sizeof(char));
        char* temp2 = calloc(strlen(getDirBaseDeSaida(paths)) + strlen(getNomeGEO(paths)) + strlen(getNomeQRY(paths)) + 10, sizeof(char));
        sprintf(temp1, "%s%s-%s.txt", getDirBaseDeSaida(paths), getNomeGEO(paths), getNomeQRY(paths));
        strcpyPathDoTXTComOQryExecutado(paths, temp1);
        sprintf(temp2, "%s%s-%s.svg", getDirBaseDeSaida(paths), getNomeGEO(paths), getNomeQRY(paths));
        strcpyPathDoSvgComOQryExecutado(paths, temp2);
        free(tempp);
        free(temp1);
        free(temp2);
        free(tempPathDoSvgDoGeoSemMudanca);
        return 1;
    }
    free(tempPathDoSvgDoGeoSemMudanca);
    return 0;
}

void getData(tree rectangleTree, tree circleTree, path paths) {
    FILE* arq = fopen(getPathArquivoGeoInicial(paths), "r");
    setvbuf(arq, 0, _IONBF, 0);
    double x;
    double y;
    double width;
    double height;
    double radius;
    char id[100];
    char rectStroke[100];
    char rectFill[100];
    char circStroke[100];
    char circFill[100];
    char command[20];
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

void getFunctions(tree rectangleTree, tree circleTree, dynamicList listOfTreesShadows, path paths) {  //Leitura do .qry
    FILE* Svg_Modificado = fopen(getPathDoSvgComOQryExecutado(paths), "w+");
    setvbuf(Svg_Modificado, 0, _IONBF, 0);
    FILE* comandos = fopen(getPathArquivoQryAtual(paths), "r");
    setvbuf(comandos, 0, _IONBF, 0);
    FILE* imExist = fopen("imTemp.txt", "r");
    if (imExist) {
        setvbuf(imExist, 0, _IONBF, 0);
        fclose(imExist);
        remove("imTemp.txt");
    }
    FILE* nveExist = fopen("nveTemp.txt", "r");
    if (nveExist) {
        setvbuf(nveExist, 0, _IONBF, 0);
        fclose(nveExist);
        remove("nveTemp.txt");
    }

    FILE* fgExist = fopen("fgTemp.txt", "r");
    if(fgExist){
        setvbuf(fgExist, 0, _IONBF, 0);
        fclose(fgExist);
        remove("fgTemp.txt");
    }
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
            fg(rectangleTree, circleTree, x, y, radius, paths);

        } else if (!strcmp(comando, "im")) {
            fscanf(comandos, "%lf %lf %lf", &x, &y, &radiation);
            im(rectangleTree, circleTree, listOfTreesShadows, x, y, radiation, paths);
        } else if (!strcmp(comando, "t30")) {
            t30(circleTree, paths);
        } else if (!strcmp(comando, "nve")) {
            fscanf(comandos, "%lf %lf", &x, &y);
            nve(listOfTreesShadows, paths, x, y);
        }
    }
    writeOnSvg(Svg_Modificado, rectangleTree, circleTree, paths);
    fclose(comandos);
    fclose(Svg_Modificado);
}