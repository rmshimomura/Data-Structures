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
void setDirBaseDeEntrada(path paths, char* newSet);
void setDirBaseDeSaida(path paths, char* newSet);
void setGeoInicial(path paths, char* newSet);
void setQryConsultas(path paths, char* newSet);
void setNomeQRY(path paths, char* newSet);
void setNomeGEO(path paths, char* newSet);
void setNomeArqSVGFinal(path paths, char* newSet);
void setPathArquivoGeoInicial(path paths, char* newSet);
void setPathArquivoQryAtual(path paths, char* newSet);
void setPathDoSvgDoGeoSemMudanca(path paths, char* newSet);
void setPathDoSvgComOQryExecutado(path paths, char* newSet);
void setPathDoTXTComOQryExecutado(path paths, char* newSet);
void setPathSVGFinalGrafico(path paths, char* newSet);
void setPathTXTFinal(path paths, char* newSet);

int getArguments(int argc, char** argv, path paths) {
    
    if (argc < 2) return -1;

    bool pathEntrada = false;
    bool consultaFeita = false;

    for (int i = 1; i < argc; i++) {

        if (!strcmp(argv[i], "-e")) {  //Diretório-base de entrada (BED)

            char* baseDeEntrada = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            strcpy(baseDeEntrada, argv[i + 1]);
            
            if(baseDeEntrada[strlen(baseDeEntrada) - 1] != '/'){
            
                baseDeEntrada = realloc(baseDeEntrada, strlen(baseDeEntrada) + 2);
                strcat(baseDeEntrada, "/");
            
            }

            pathEntrada = true;
            setDirBaseDeEntrada(paths, baseDeEntrada);

        } else if (!strcmp(argv[i], "-f")) {  //Arquivo .geo inicial. Este arquivo deve estar sob o diretório BED.
            
            char* geoInicial = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            char* nomeGeo = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            int index = 0;
            int posNome = 0;
            bool found = false;
            strcpy(geoInicial, argv[i + 1]);
            setGeoInicial(paths, geoInicial);

            for (int i = 0; i < strlen(geoInicial); i++) {  //Se for passado um caminho relativo na localizacao do .geo inicial
                
                if (geoInicial[i] == '/') {
                    index = i;
                    found = true;
                }

            }

            if (found) {

                for (int i = index + 1; i < strlen(geoInicial); i++) {

                    if (geoInicial[i] == '.') {

                        nomeGeo[posNome] = '\0';
                        break;

                    } else {

                        nomeGeo[posNome] = geoInicial[i];
                        posNome++;

                    }

                }

                setNomeGEO(paths, nomeGeo);

            } else {

                strcpy(nomeGeo, argv[i + 1]);

                for (int i = 0; i < strlen(nomeGeo); i++) {
                
                    if (nomeGeo[i] == '.') {
                        nomeGeo[i] = '\0';
                    }

                }

                setNomeGEO(paths, nomeGeo);
            }

        } else if (!strcmp(argv[i], "-o")) {  //Diretório-base de saída (BSD)

            char* baseDeSaida = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            strcpy(baseDeSaida, argv[i+1]);
            
            if(baseDeSaida[strlen(baseDeSaida) - 1] != '/'){

                baseDeSaida = realloc(baseDeSaida, strlen(baseDeSaida) + 2);
                strcat(baseDeSaida, "/");
            
            }

            setDirBaseDeSaida(paths, baseDeSaida);

        } else if (!strcmp(argv[i], "-q")) {  //Arquivo com consultas. Este arquivo deve estar sob o diretório BED.
            
            char* qryConsultas = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            char* nomeQry = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            strcpy(qryConsultas, argv[i + 1]);
            setQryConsultas(paths, qryConsultas);
            int index = 0;
            int posNome = 0;
            bool found = false;

            for (int i = 0; i < strlen(qryConsultas); i++) {  //Se for passado um caminho relativo na localizacao do .geo inicial
            
                if (qryConsultas[i] == '/') {
            
                    index = i;
                    found = true;
            
                }
            
            }
            
            if (found) {
                for (int i = index + 1; i < strlen(qryConsultas); i++) {
                    if (qryConsultas[i] == '.') {
                        nomeQry[posNome] = '\0';
                        break;
                    } else {
                        nomeQry[posNome] = qryConsultas[i];
                        posNome++;
                    }
                }
                
                setNomeQRY(paths, nomeQry);
            } else {
                strcpy(nomeQry, argv[i + 1]);
                for (int i = 0; i < strlen(nomeQry); i++) {
                    if (nomeQry[i] == '.') {
                        nomeQry[i] = '\0';
                    }
                }
                
                setNomeQRY(paths, nomeQry);
            }
            consultaFeita = true;
        }
    }

    //Apos coletar todas as informacoes, esta na hora de arrumar e organizar todos os dados reunidos, nomes autoexplicativos
    char* pathDoSvgDoGeoSemMudanca = calloc(strlen(getDirBaseDeSaida(paths)) + strlen(getNomeGEO(paths)) + 10, sizeof(char));
    sprintf(pathDoSvgDoGeoSemMudanca, "%s%s.svg", getDirBaseDeSaida(paths), getNomeGEO(paths));
    setPathDoSvgDoGeoSemMudanca(paths, pathDoSvgDoGeoSemMudanca);

    if (pathEntrada) {

        char* pathArquivoGeoInicial = calloc(strlen(getDirBaseDeEntrada(paths)) + strlen(getGeoInicial(paths)) + 2, sizeof(char));
        strcpy(pathArquivoGeoInicial, getDirBaseDeEntrada(paths));
        strcat(pathArquivoGeoInicial, getGeoInicial(paths));
        setPathArquivoGeoInicial(paths, pathArquivoGeoInicial);

    } else {

        char* baseDeEntrada = calloc(3, sizeof(char));
        strcpy(baseDeEntrada, "./");
        setDirBaseDeEntrada(paths,baseDeEntrada);
        char* pathArquivoGeoInicial = calloc(strlen(getDirBaseDeEntrada(paths)) + strlen(getGeoInicial(paths)) + 2, sizeof(char));
        strcpy(pathArquivoGeoInicial, getDirBaseDeEntrada(paths));
        strcat(pathArquivoGeoInicial, getGeoInicial(paths));
        setPathArquivoGeoInicial(paths, pathArquivoGeoInicial);

    }

    if (consultaFeita) {

        char* pathArquivoQryAtual = calloc(strlen(getDirBaseDeEntrada(paths)) + strlen(getQryConsultas(paths)) + 10, sizeof(char));
        sprintf(pathArquivoQryAtual, "%s%s", getDirBaseDeEntrada(paths), getQryConsultas(paths));
        setPathArquivoQryAtual(paths, pathArquivoQryAtual);
        char* pathDoTXTComOQryExecutado = calloc(strlen(getDirBaseDeSaida(paths)) + strlen(getNomeGEO(paths)) + strlen(getNomeQRY(paths)) + 10, sizeof(char));
        char* pathDoSvgComOQryExecutado = calloc(strlen(getDirBaseDeSaida(paths)) + strlen(getNomeGEO(paths)) + strlen(getNomeQRY(paths)) + 10, sizeof(char));
        sprintf(pathDoTXTComOQryExecutado, "%s%s-%s.txt", getDirBaseDeSaida(paths), getNomeGEO(paths), getNomeQRY(paths));
        setPathDoTXTComOQryExecutado(paths, pathDoTXTComOQryExecutado);
        sprintf(pathDoSvgComOQryExecutado, "%s%s-%s.svg", getDirBaseDeSaida(paths), getNomeGEO(paths), getNomeQRY(paths));
        setPathDoSvgComOQryExecutado(paths, pathDoSvgComOQryExecutado);
        return 1;

    }

    return 0;

}

void getData(tree rectangleTree, tree circleTree, path paths) {
    FILE* arq = fopen(getPathArquivoGeoInicial(paths), "r");
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

void getFunctions(tree rectangleTree, tree circleTree, dynamicList listOfTreesShadows, path paths) {  //Leitura do .qry
    FILE* Svg_Modificado = fopen(getPathDoSvgComOQryExecutado(paths), "w+");
    setvbuf(Svg_Modificado, 0, _IONBF, 0);
    FILE* comandos = fopen(getPathArquivoQryAtual(paths), "r");
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
    new_writeOnSvg(Svg_Modificado, rectangleTree, circleTree, paths, fgData, imData, nveData);
    freeList(fgData);
    freeList(imData);
    freeList(nveData);
    fclose(comandos);
    fclose(Svg_Modificado);
}