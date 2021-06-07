#include "bibliotecas.h"
#include "system.h"
#include "qry.h"
#include "elemento.h"
#include "flags.h"
#include "paths.h"
#include "svg.h"


//Evitar sets desnecessarios
void setFlags(flag checkers);
void setBBIDexecutado(flag checkers, bool state);
void setBBIexecutado(flag checkers, bool state);
void setCbExecutado(flag checkers, bool state);
void setConsultafeita(flag checkers, bool state);
void setFail(flag checkers, bool state);
void setFbExecutado(flag checkers, bool state);
void setFileGeo(flag checkers, bool state);
void setIbExecutado(flag checkers, bool state);
void setiidExecutado(flag checkers, bool state);
void setPathSaida(flag checkers, bool state);
void setTPExecutado(flag checkers, bool state);
void setTPRExecutado(flag checkers, bool state);
void setFileQryValido(flag checkers, bool state);
void allocateDirbaseDeEntrada(path paths, int size);
void allocateDirBaseDeSaida(path paths, int size);
void allocateGeoInicial(path paths, int size);
void allocateQryConsultas(path paths, int size);
void allocateNomeQRY(path paths, int size);
void allocateNomeGEO(path paths, int size);
void allocateNomeArqSVGFinal(path paths, int size);
void allocateTituloGrafFinal(path paths, int size);
void allocatePathArquivoGeoInicial(path paths, int size);
void allocatePathArquivoQryAtual(path paths, int size);
void allocatePathDoSvgDoGeoSemMudanca(path paths, int size);
void allocatePathDoSvgComOQryExecutado(path paths, int size);
void allocatePathDoTXTComOQryExecutado(path paths, int size);
void allocatePathSVGFinalGrafico(path paths, int size);
void allocatePathTXTFinal(path paths, int size);
void reallocateDirbaseDeEntrada(path paths, int newSize);
void reallocateDirBaseDeSaida(path paths, int newSize);
void reallocateGeoInicial(path paths, int newSize);
void reallocateQryConsultas(path paths, int newSize);
void reallocateNomeQRY(path paths, int newSize);
void reallocateNomeGEO(path paths, int newSize);
void reallocateNomeArqSVGFinal(path paths, int newSize);
void reallocateTituloGrafFinal(path paths, int newSize);
void reallocatePathArquivoGeoInicial(path paths, int newSize);
void reallocatePathArquivoQryAtual(path paths, int newSize);
void reallocatePathDoSvgDoGeoSemMudanca(path paths, int newSize);
void reallocatePathDoSvgComOQryExecutado(path paths, int newSize);
void reallocatePathDoTXTComOQryExecutado(path paths, int newSize);
void reallocatePathSVGFinalGrafico(path paths, int newSize);
void reallocatePathTXTFinal(path paths, int newSize);
void strcpyDirbaseDeEntrada(path paths, char* assemble);
void strcpyDirBaseDeSaida(path paths, char* assemble);
void strcpyGeoInicial(path paths, char* assemble);
void strcpyQryConsultas(path paths, char* assemble);
void strcpyNomeQRY(path paths, char* assemble);
void strcpyNomeGEO(path paths, char* assemble);
void strcpyNomeArqSVGFinal(path paths, char* assemble);
void strcpyTituloGrafFinal(path paths, char* assemble);
void strcpyPathArquivoGeoInicial(path paths, char* assemble);
void strcpyPathArquivoQryAtual(path paths, char* assemble);
void strcpyPathDoSvgDoGeoSemMudanca(path paths, char* assemble);
void strcpyPathDoSvgComOQryExecutado(path paths, char* assemble);
void strcpyPathDoTXTComOQryExecutado(path paths, char* assemble);
void strcpyPathSVGFinalGrafico(path paths, char* assemble);
void strcpyPathTXTFinal(path paths, char* assemble);
void strcatDirbaseDeEntrada(path paths, char* assemble);
void strcatDirBaseDeSaida(path paths, char* assemble);
void strcatGeoInicial(path paths, char* assemble);
void strcatQryConsultas(path paths, char* assemble);
void strcatNomeQRY(path paths, char* assemble);
void strcatNomeGEO(path paths, char* assemble);
void strcatNomeArqSVGFinal(path paths, char* assemble);
void strcatTituloGrafFinal(path paths, char* assemble);
void strcatPathArquivoGeoInicial(path paths, char* assemble);
void strcatPathArquivoQryAtual(path paths, char* assemble);
void strcatPathDoSvgDoGeoSemMudanca(path paths, char* assemble);
void strcatPathDoSvgComOQryExecutado(path paths, char* assemble);
void strcatPathDoTXTComOQryExecutado(path paths, char* assemble);
void strcatPathSVGFinalGrafico(path paths, char* assemble);
void strcatPathTXTFinal(path paths, char* assemble);

void showlist(lista sequence) {
    int tamanho = getSize(sequence);
    if(tamanho == 0){
        puts("Nao ha elementos na lista!");
        return;
    }
    celula celulaAux = getHead(sequence);
    item aux;
    puts("=================");
    for (int i = 0; i < getSize(sequence); i++) {
        aux = getItem(sequence, celulaAux);
        printf("Pos na lista = %d - id = %s x = %.2lf y = %.2lf largura = %.2lf altura = %.2lf preenchimento = %s contorno = %s\n", i, getId(aux), getX(aux), getY(aux), getLargura(aux), getAltura(aux), getContorno(aux), getPreenchimento(aux));
        celulaAux = getNext(sequence, celulaAux);
    }
    puts("=================");
}

void getData(lista sequence, path paths) {
    item aux;
    FILE* arq = fopen(getPathArquivoGeoInicial(paths), "r");
    double x;
    double y;
    double largura;
    double altura;
    char id[100];
    char contorno[100];
    char preenchimento[100];
    char comando[20];
    int i = 0;
    while (fscanf(arq, "%s", comando) != -1) {
        if (!strcmp(comando, "cc")) {
            fscanf(arq, "%s", contorno);
        } else if (!strcmp(comando, "cp")) {
            fscanf(arq, "%s", preenchimento);
        } else if (!strcmp(comando, "r")) {
            aux = createElemento();
            setContorno(aux, contorno);
            setPreenchimento(aux, preenchimento);
            fscanf(arq, "%s %lf %lf %lf %lf", id, &x, &y, &largura, &altura);
            setId(aux, id);
            setX(aux, x);
            setY(aux, y);
            setLargura(aux, largura);
            setAltura(aux, altura);
            insert(sequence, aux);
        }
    }
    fclose(arq);
}

void getArguments(int argc, char** argv, flag checkers, path paths) {
    if (argc < 2) {
        puts("Argumentos faltando.");
        return;
    }
    printf("dentro %p\n", paths);
    bool pathEntrada = false;
    bool qryvalido = true;
    setIbExecutado(checkers, false);
    setFbExecutado(checkers, false);
    setFileGeo(checkers, false);
    setPathSaida(checkers, false);
    setFileQryValido(checkers, true);

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-e")) {  //Diretório-base de entrada (BED)
            allocateDirbaseDeEntrada(paths, strlen(argv[i + 1]) + 1);
            strcpyDirbaseDeEntrada(paths, argv[i+1]);
            if(getDirBaseDeEntrada(paths)[strlen(getDirBaseDeEntrada(paths)) - 1] != '/'){
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
                strcpy(tempNomeGEO, argv[i+1]);
                for (int i = 0; i < strlen(tempNomeGEO); i++) {
                    if (tempNomeGEO[i] == '.') {
                        tempNomeGEO[i] = '\0';
                    }
                }
                strcpyNomeGEO(paths, tempNomeGEO);
            }
            setFileGeo(checkers, true);
            free(temp);
            free(tempNomeGEO);
        } else if (!strcmp(argv[i], "-o")) {  //Diretório-base de saída (BSD)
            allocateDirBaseDeSaida(paths, strlen(argv[i+1]) + 1);
            strcpyDirBaseDeSaida(paths, argv[i+1]);
            if(getDirBaseDeSaida(paths)[strlen(getDirBaseDeSaida(paths)) - 1] != '/'){
                reallocateDirBaseDeSaida(paths, strlen(getDirBaseDeSaida(paths)) + 2);
                strcatDirBaseDeSaida(paths, "/");
            }
            setPathSaida(checkers, true);

        } else if (!strcmp(argv[i], "-q")) {  //Arquivo com consultas. Este arquivo deve estar sob o diretório BED.
            char* temp = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            char* tempNomeQRY = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            allocateQryConsultas(paths, strlen(argv[i + 1]) + 1);
            allocateNomeQRY(paths, strlen(argv[i + 1]) + 1);
            strcpyQryConsultas(paths, argv[i+1]);
            strcpy(temp, argv[i + 1]);
            int index;
            int posNome = 0;
            bool found = false;
            setFileQryValido(checkers, true);
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
            setConsultafeita(checkers, true);
            free(temp);
            free(tempNomeQRY);
        } else if (!strcmp(argv[i], "-ib")) {  //Inicia coleta de dados de desempenho
            setIbExecutado(checkers, true);
        } else if (!strcmp(argv[i], "-cb")) {  //Continua a coletar dados
            setCbExecutado(checkers, true);
            //Dar append depois de um -ib executado
        } else if (!strcmp(argv[i], "-fb")) {  //Finaliza a coleta, produz no diretório BED o arquivo arq.svg contendo o gráfico com o título especificado
            FILE* hasStart = fopen("visitasDoQryAtual.txt", "r");
            if (!hasStart) {  //Checar se a coleta foi inicializada
                setFail(checkers, true);
                continue;
            }
            allocateNomeArqSVGFinal(paths, strlen(argv[i + 1]) + 1);
            allocateTituloGrafFinal(paths, strlen(argv[i + 2]) + 1);
            strcpyNomeArqSVGFinal(paths, argv[i+1]);
            strcpyTituloGrafFinal(paths, argv[i+2]);
            setFbExecutado(checkers, true);
            fclose(hasStart);
        } else if (!strcmp(argv[i], "-lse")) {  
            //[sample-text]//
        } else if (!strcmp(argv[i], "-ldd")) {  
            //[sample-text]//
        }
    }

    //Apos coletar todas as informacoes, esta na hora de arrumar e organizar todos os dados reunidos, nomes autoexplicativos
    char* tempPathDoSvgDoGeoSemMudanca = calloc(strlen(getDirBaseDeSaida(paths)) + strlen(getNomeGEO(paths)) + 100, sizeof(char));
    sprintf(tempPathDoSvgDoGeoSemMudanca, "%s%s.svg", getDirBaseDeSaida(paths), getNomeGEO(paths));
    allocatePathDoSvgDoGeoSemMudanca(paths, strlen(tempPathDoSvgDoGeoSemMudanca)+ 1);
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
    
    if (getConsultafeita(checkers)) {
        char* tempp = calloc(strlen(getDirBaseDeEntrada(paths)) + strlen(getQryConsultas(paths)) + 100, sizeof(char));
        allocatePathArquivoQryAtual(paths, strlen(getDirBaseDeEntrada(paths)) + strlen(getQryConsultas(paths)) + 2);

        sprintf(tempp, "%s%s", getDirBaseDeEntrada(paths), getQryConsultas(paths));
        strcpyPathArquivoQryAtual(paths, tempp);
        allocatePathDoSvgComOQryExecutado(paths, strlen(getDirBaseDeSaida(paths)) + strlen(getNomeGEO(paths)) + strlen(getNomeQRY(paths)) + 9);
        allocatePathDoTXTComOQryExecutado(paths, strlen(getDirBaseDeSaida(paths)) + strlen(getNomeGEO(paths)) + strlen(getNomeQRY(paths)) + 9);
        char* temp1 = calloc(strlen(getDirBaseDeSaida(paths)) + strlen(getNomeGEO(paths)) + strlen(getNomeQRY(paths)) + 100, sizeof(char));
        char* temp2 = calloc(strlen(getDirBaseDeSaida(paths)) + strlen(getNomeGEO(paths)) + strlen(getNomeQRY(paths)) + 100, sizeof(char));
        sprintf(temp1, "%s%s-%s.txt", getDirBaseDeSaida(paths), getNomeGEO(paths), getNomeQRY(paths));
        strcpyPathDoTXTComOQryExecutado(paths, temp1);
        sprintf(temp2, "%s%s-%s.svg", getDirBaseDeSaida(paths), getNomeGEO(paths), getNomeQRY(paths));
        strcpyPathDoSvgComOQryExecutado(paths, temp2);
        free(tempp);
        free(temp1);
        free(temp2);
    }
    if (getFbExecutado(checkers)) {
        char* temporario = calloc(strlen(getDirBaseDeSaida(paths)) + strlen(getNomeArqSVGFinal(paths)) + 100, sizeof(char));
        allocatePathSVGFinalGrafico(paths, strlen(getDirBaseDeSaida(paths)) + strlen(getNomeArqSVGFinal(paths)) + 10);
        sprintf(temporario, "%s%s.svg", getDirBaseDeSaida(paths), getNomeArqSVGFinal(paths));
        strcpyPathSVGFinalGrafico(paths, temporario);
        free(temporario);
    }
    free(tempPathDoSvgDoGeoSemMudanca);
}

void getFunctions(lista sequence, char* ArquivoQry, flag checkers, path paths) {  //Leitura do .qry
    FILE* resultstxt = fopen(getPathDoTXTComOQryExecutado(paths), "w+");
    FILE* Svg_Modificado = fopen(getPathDoSvgComOQryExecutado(paths), "w+");
    FILE* comandos = fopen(getPathArquivoQryAtual(paths), "r");
    double x;
    double y;
    double largura;
    double altura;
    char id[100];
    int k;
    char comando[5];
    int cont = 0;
    bool naoPrintar = false;
    while (fscanf(comandos, "%s", comando) != -1) {
        if (!strcmp(comando, "tp")) {
            tp(sequence, resultstxt, checkers);
            cont++;
        }else if (!strcmp(comando, "tpr")) {
            fscanf(comandos, "%lf %lf %lf %lf", &x, &y, &largura, &altura);
            tpr(x, y, largura, altura, sequence, resultstxt, checkers);
            cont++;
        }else if (!strcmp(comando, "dpi")) {
            fscanf(comandos, "%lf %lf", &x, &y);
            dpi(x, y, sequence, resultstxt, checkers);
            cont++;
        }else if (!strcmp(comando, "dr")) {
            fscanf(comandos, "%s", id);
            dr(id, sequence, resultstxt, checkers);
            cont++;
        }else if (!strcmp(comando, "bbi")) {
            fscanf(comandos, "%lf %lf", &x, &y);
            bbi(x, y, sequence, resultstxt, checkers);
            cont++;
        }else if (!strcmp(comando, "bbid")) {
            fscanf(comandos, "%s", id);
            bbid(id, sequence, resultstxt, checkers);
            cont++;
        }else if (!strcmp(comando, "iid")) {
            fscanf(comandos, "%s %d", id, &k);
            iid(id, k, sequence, resultstxt, checkers);
            cont++;
        }else if (!strcmp(comando, "diid")) {
            fscanf(comandos, "%s %d", id, &k);
            diid(id, k, sequence, resultstxt, checkers);
            cont++;
        }
    }
    if (cont == 1 && getiidExecutado(checkers)) {
        fclose(Svg_Modificado);
        fclose(comandos);
        fclose(resultstxt);
        remove(getPathDoSvgComOQryExecutado(paths));
    } else {
        writeOnSvg(Svg_Modificado, sequence, checkers);
        fclose(comandos);
        fclose(resultstxt);
        fclose(Svg_Modificado);
    }
}

void CloseFiles(FILE* geo, FILE* svg_source) {
    fclose(svg_source);
    fclose(geo);
}

void checarColetas(lista sequence, flag checkers, path paths) {
    if (getIbExecutado(checkers)) {
        FILE* visitasDoQryAtual = fopen("visitasDoQryAtual.txt", "w+");
        fprintf(visitasDoQryAtual, "%ld %ld\n", getVisitas(sequence), getOriginalSize(sequence));
        fclose(visitasDoQryAtual);
    } else if (getCbExecutado(checkers)) {
        FILE* visitasDoQryAtual = fopen("visitasDoQryAtual.txt", "a+");
        fprintf(visitasDoQryAtual, "%ld %ld\n", getVisitas(sequence), getOriginalSize(sequence));
        fclose(visitasDoQryAtual);
    } else if (getFbExecutado(checkers)) {
        FILE* visitasDoQryAtual = fopen("visitasDoQryAtual.txt", "a+");
        fprintf(visitasDoQryAtual, "%ld %ld\n", getVisitas(sequence), getOriginalSize(sequence));
        fclose(visitasDoQryAtual);
        buildGraphic(sequence, paths);
    }
}

void createTempFiles() {
    FILE* tempTPWrite = fopen("testeTP.txt", "w+");
    FILE* tempTPR = fopen("tempTPR.txt", "w+");
    FILE* tempDPI = fopen("tempDPI.txt", "w+");
    FILE* tempDR = fopen("tempDR.txt", "w+");
    FILE* tempBBICoordenadas = fopen("tempBBICoordinates.txt", "w+");
    FILE* tempBBIPontos = fopen("tempBBIPoints.txt", "w+");
    FILE* tempBBIDCoordenadas = fopen("tempBBIDCoordinates.txt", "w+");
    FILE* tempDIID = fopen("tempDIID.txt", "w+");
    FILE* tempDIIDRemove = fopen("tempDIIDRemove.txt", "w+");

    fclose(tempTPWrite);
    fclose(tempTPR);
    fclose(tempDPI);
    fclose(tempDR);
    fclose(tempBBICoordenadas);
    fclose(tempBBIPontos);
    fclose(tempBBIDCoordenadas);
    fclose(tempDIID);
    fclose(tempDIIDRemove);
}

void removeTempFiles() {
    remove("testeTP.txt");
    remove("tempTPR.txt");
    remove("tempDPI.txt");
    remove("tempDR.txt");
    remove("tempBBICoordinates.txt");
    remove("tempBBIPoints.txt");
    remove("tempBBIDCoordinates.txt");
    remove("tempDIID.txt");
    remove("tempDIIDRemove.txt");
}

int nxFind(path paths){
    FILE* a = fopen(getPathArquivoGeoInicial(paths), "r");
    int nx;
    fscanf(a, "nx %d", &nx);
    fclose(a);
    return nx;
}