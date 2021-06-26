#include "paths.h"

typedef struct pathsGerais {

    char* DirBaseDeEntrada;           //Diretorio de entrada
    char* DirBaseDeSaida;             //Diretorio de saida
    char* GeoInicial;                 //Arquivo .geo (sem diretorio)
    char* QryConsultas;               //Arquivo .qry (sem diretorio)
    char* NomeQRY;                    //Nome do .qry sem o .qry
    char* NomeGEO;                    //Nome do .geo sem o .geo
    char* NomeArqSVGFinal;            //Nome do .svg final sem o .svg
    char* TituloGrafFinal;            //Titulo do grafico final
    char* PathArquivoGeoInicial;      //Path ate o .geo inicial
    char* PathArquivoQryAtual;        //Path ate o .qry que esta sendo usado
    char* PathDoSvgDoGeoSemMudanca;   //Path ate o svg que sera gerado sem alteracoes
    char* PathDoSvgComOQryExecutado;  //Path ate o svg com as alteracoes do qry
    char* PathDoTXTComOQryExecutado;  //Path ate o txt com as alteracoes do qry
    char* PathSVGFinalGrafico;        //Path ate o .svg final com o grafico
    char* PathTXTFinal;               //Path ate o .txt final

} pathsGerais;

path createPathsGerais() {

    pathsGerais* aux = calloc(1, sizeof(pathsGerais));
    return aux;

}

char* getDirBaseDeEntrada(path paths) {

    pathsGerais* aux = paths;
    return aux->DirBaseDeEntrada;

}

char* getDirBaseDeSaida(path paths) {

    pathsGerais* aux = paths;
    return aux->DirBaseDeSaida;

}

char* getGeoInicial(path paths) {

    pathsGerais* aux = paths;
    return aux->GeoInicial;

}

char* getQryConsultas(path paths) {

    pathsGerais* aux = paths;
    return aux->QryConsultas;

}

char* getNomeQRY(path paths) {

    pathsGerais* aux = paths;
    return aux->NomeQRY;

}

char* getNomeGEO(path paths) {

    pathsGerais* aux = paths;
    return aux->NomeGEO;

}

char* getNomeArqSVGFinal(path paths) {

    pathsGerais* aux = paths;
    return aux->NomeArqSVGFinal;

}

char* getPathArquivoGeoInicial(path paths) {

    pathsGerais* aux = paths;
    return aux->PathArquivoGeoInicial;

}

char* getPathArquivoQryAtual(path paths) {

    pathsGerais* aux = paths;
    return aux->PathArquivoQryAtual;

}

char* getPathDoSvgDoGeoSemMudanca(path paths) {

    pathsGerais* aux = paths;
    return aux->PathDoSvgDoGeoSemMudanca;

}

char* getPathDoSvgComOQryExecutado(path paths) {

    pathsGerais* aux = paths;
    return aux->PathDoSvgComOQryExecutado;

}

char* getPathDoTXTComOQryExecutado(path paths) {

    pathsGerais* aux = paths;
    return aux->PathDoTXTComOQryExecutado;

}

char* getPathSVGFinalGrafico(path paths) {

    pathsGerais* aux = paths;
    return aux->PathSVGFinalGrafico;

}

char* getPathTXTFinal(path paths) {

    pathsGerais* aux = paths;
    return aux->PathTXTFinal;

}

void allocateDirbaseDeEntrada(path paths, int size) {

    pathsGerais* aux = paths;
    aux->DirBaseDeEntrada = calloc(size, sizeof(char));

}

void allocateDirBaseDeSaida(path paths, int size) {

    pathsGerais* aux = paths;
    aux->DirBaseDeSaida = calloc(size, sizeof(char));

}

void allocateGeoInicial(path paths, int size) {

    pathsGerais* aux = paths;
    aux->GeoInicial = calloc(size, sizeof(char));

}

void allocateQryConsultas(path paths, int size) {

    pathsGerais* aux = paths;
    aux->QryConsultas = calloc(size, sizeof(char));

}

void allocateNomeQRY(path paths, int size) {

    pathsGerais* aux = paths;
    aux->NomeQRY = calloc(size, sizeof(char));

}

void allocateNomeGEO(path paths, int size) {

    pathsGerais* aux = paths;
    aux->NomeGEO = calloc(size, sizeof(char));

}

void allocateNomeArqSVGFinal(path paths, int size) {

    pathsGerais* aux = paths;
    aux->NomeArqSVGFinal = calloc(size, sizeof(char));

}

void allocatePathArquivoGeoInicial(path paths, int size) {

    pathsGerais* aux = paths;
    aux->PathArquivoGeoInicial = calloc(size, sizeof(char));

}

void allocatePathArquivoQryAtual(path paths, int size) {

    pathsGerais* aux = paths;
    aux->PathArquivoQryAtual = calloc(size, sizeof(char));

}

void allocatePathDoSvgDoGeoSemMudanca(path paths, int size) {

    pathsGerais* aux = paths;
    aux->PathDoSvgDoGeoSemMudanca = calloc(size, sizeof(char));

}

void allocatePathDoSvgComOQryExecutado(path paths, int size) {

    pathsGerais* aux = paths;
    aux->PathDoSvgComOQryExecutado = calloc(size, sizeof(char));

}

void allocatePathDoTXTComOQryExecutado(path paths, int size) {

    pathsGerais* aux = paths;
    aux->PathDoTXTComOQryExecutado = calloc(size, sizeof(char));

}

void allocatePathSVGFinalGrafico(path paths, int size) {

    pathsGerais* aux = paths;
    aux->PathSVGFinalGrafico = calloc(size, sizeof(char));

}

void allocatePathTXTFinal(path paths, int size) {

    pathsGerais* aux = paths;
    aux->PathTXTFinal = calloc(size, sizeof(char));

}

void reallocateDirbaseDeEntrada(path paths, int newSize) {

    pathsGerais* aux = paths;
    aux->DirBaseDeEntrada = realloc(aux->DirBaseDeEntrada, newSize);

}

void reallocateDirBaseDeSaida(path paths, int newSize) {

    pathsGerais* aux = paths;
    aux->DirBaseDeSaida = realloc(aux->DirBaseDeSaida, newSize);

}

void reallocateGeoInicial(path paths, int newSize) {

    pathsGerais* aux = paths;
    aux->GeoInicial = realloc(aux->GeoInicial, newSize);

}

void reallocateQryConsultas(path paths, int newSize) {

    pathsGerais* aux = paths;
    aux->QryConsultas = realloc(aux->QryConsultas, newSize);

}

void reallocateNomeQRY(path paths, int newSize) {

    pathsGerais* aux = paths;
    aux->NomeQRY = realloc(aux->NomeQRY, newSize);

}

void reallocateNomeGEO(path paths, int newSize) {

    pathsGerais* aux = paths;
    aux->NomeGEO = realloc(aux->NomeGEO, newSize);

}

void reallocateNomeArqSVGFinal(path paths, int newSize) {

    pathsGerais* aux = paths;
    aux->NomeArqSVGFinal = realloc(aux->NomeArqSVGFinal, newSize);

}

void reallocatePathArquivoGeoInicial(path paths, int newSize) {

    pathsGerais* aux = paths;
    aux->PathArquivoGeoInicial = realloc(aux->PathArquivoGeoInicial, newSize);

}

void reallocatePathArquivoQryAtual(path paths, int newSize) {

    pathsGerais* aux = paths;
    aux->PathArquivoQryAtual = realloc(aux->PathArquivoQryAtual, newSize);

}

void reallocatePathDoSvgDoGeoSemMudanca(path paths, int newSize) {

    pathsGerais* aux = paths;
    aux->PathDoSvgDoGeoSemMudanca = realloc(aux->PathDoSvgDoGeoSemMudanca, newSize);

}

void reallocatePathDoSvgComOQryExecutado(path paths, int newSize) {

    pathsGerais* aux = paths;
    aux->PathDoSvgComOQryExecutado = realloc(aux->PathDoSvgComOQryExecutado, newSize);

}

void reallocatePathDoTXTComOQryExecutado(path paths, int newSize) {

    pathsGerais* aux = paths;
    aux->PathDoTXTComOQryExecutado = realloc(aux->PathDoTXTComOQryExecutado, newSize);

}

void reallocatePathSVGFinalGrafico(path paths, int newSize) {

    pathsGerais* aux = paths;
    aux->PathSVGFinalGrafico = realloc(aux->PathSVGFinalGrafico, newSize);

}

void reallocatePathTXTFinal(path paths, int newSize) {

    pathsGerais* aux = paths;
    aux->PathTXTFinal = realloc(aux->PathTXTFinal, newSize);

}

void strcpyDirbaseDeEntrada(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcpy(aux->DirBaseDeEntrada, assemble);

}

void strcpyDirBaseDeSaida(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcpy(aux->DirBaseDeSaida, assemble);

}

void strcpyGeoInicial(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcpy(aux->GeoInicial, assemble);

}

void strcpyQryConsultas(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcpy(aux->QryConsultas, assemble);

}

void strcpyNomeQRY(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcpy(aux->NomeQRY, assemble);

}

void strcpyNomeGEO(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcpy(aux->NomeGEO, assemble);

}

void strcpyNomeArqSVGFinal(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcpy(aux->NomeArqSVGFinal, assemble);

}

void strcpyPathArquivoGeoInicial(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcpy(aux->PathArquivoGeoInicial, assemble);

}

void strcpyPathArquivoQryAtual(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcpy(aux->PathArquivoQryAtual, assemble);

}

void strcpyPathDoSvgDoGeoSemMudanca(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcpy(aux->PathDoSvgDoGeoSemMudanca, assemble);

}

void strcpyPathDoSvgComOQryExecutado(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcpy(aux->PathDoSvgComOQryExecutado, assemble);

}

void strcpyPathDoTXTComOQryExecutado(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcpy(aux->PathDoTXTComOQryExecutado, assemble);

}

void strcpyPathSVGFinalGrafico(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcpy(aux->PathSVGFinalGrafico, assemble);

}

void strcpyPathTXTFinal(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcpy(aux->PathTXTFinal, assemble);

}

void strcatDirbaseDeEntrada(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcat(aux->DirBaseDeEntrada, assemble);

}

void strcatDirBaseDeSaida(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcat(aux->DirBaseDeSaida, assemble);

}

void strcatGeoInicial(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcat(aux->GeoInicial, assemble);

}

void strcatQryConsultas(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcat(aux->QryConsultas, assemble);

}

void strcatNomeQRY(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcat(aux->NomeQRY, assemble);

}

void strcatNomeGEO(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcat(aux->NomeGEO, assemble);

}

void strcatNomeArqSVGFinal(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcat(aux->NomeArqSVGFinal, assemble);

}

void strcatPathArquivoGeoInicial(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcat(aux->PathArquivoGeoInicial, assemble);

}

void strcatPathArquivoQryAtual(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcat(aux->PathArquivoQryAtual, assemble);

}

void strcatPathDoSvgDoGeoSemMudanca(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcat(aux->PathDoSvgDoGeoSemMudanca, assemble);

}

void strcatPathDoSvgComOQryExecutado(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcat(aux->PathDoSvgComOQryExecutado, assemble);

}

void strcatPathDoTXTComOQryExecutado(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcat(aux->PathDoTXTComOQryExecutado, assemble);

}

void strcatPathSVGFinalGrafico(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcat(aux->PathSVGFinalGrafico, assemble);

}

void strcatPathTXTFinal(path paths, char* assemble) {

    pathsGerais* aux = paths;
    strcat(aux->PathTXTFinal, assemble);

}

void showPaths(path paths) {

    pathsGerais* aux = paths;
    if (aux->DirBaseDeEntrada) {

        puts("DirBaseDeEntrada :");
        puts(aux->DirBaseDeEntrada);
        puts("====================");
    
    }
    if (aux->DirBaseDeSaida) {

        puts("DirBaseDeSaida : ");
        puts(aux->DirBaseDeSaida);
        puts("====================");
    
    }
    if (aux->GeoInicial) {

        puts("GeoInicial : ");
        puts(aux->GeoInicial);
        puts("====================");
    
    }
    if (aux->NomeArqSVGFinal) {

        puts("NomeArqSVGFinal : ");
        puts(aux->NomeArqSVGFinal);
        puts("====================");
    
    }
    if (aux->NomeGEO) {

        puts("NomeGEO : ");
        puts(aux->NomeGEO);
        puts("====================");
    
    }
    if (aux->NomeQRY) {

        puts("NomeQRY : ");
        puts(aux->NomeQRY);
        puts("====================");
    
    }
    if (aux->PathArquivoGeoInicial) {

        puts("PathArquivoGeoInicial : ");
        puts(aux->PathArquivoGeoInicial);
        puts("====================");
    
    }
    if (aux->PathArquivoQryAtual) {

        puts("PathArquivoQryAtual : ");
        puts(aux->PathArquivoQryAtual);
        puts("====================");
    
    }
    if (aux->PathDoSvgComOQryExecutado) {

        puts("PathDoSvgComOQryExecutado : ");
        puts(aux->PathDoSvgComOQryExecutado);
        puts("====================");
    
    }
    if (aux->PathDoSvgDoGeoSemMudanca) {

        puts("PathDoSvgDoGeoSemMudanca : ");
        puts(aux->PathDoSvgDoGeoSemMudanca);
        puts("====================");
    
    }
    if (aux->PathDoTXTComOQryExecutado) {

        puts("PathDoTXTComOQryExecutado : ");
        puts(aux->PathDoTXTComOQryExecutado);
        puts("====================");
    
    }
    if (aux->PathSVGFinalGrafico) {

        puts("PathSVGFinalGrafico : ");
        puts(aux->PathSVGFinalGrafico);
        puts("====================");
    
    }
    if (aux->PathTXTFinal) {

        puts("PathTXTFinal : ");
        puts(aux->PathTXTFinal);
        puts("====================");
    
    }
    if (aux->QryConsultas) {

        puts("QryConsultas : ");
        puts(aux->QryConsultas);
        puts("====================");
    
    }
    if (aux->TituloGrafFinal) {

        puts("TituloGrafFinal : ");
        puts(aux->TituloGrafFinal);
        puts("====================");
    
    }

}

void freePaths(path paths) {

    pathsGerais* aux = paths;
    if (aux->DirBaseDeEntrada) {

        free(aux->DirBaseDeEntrada);
    
    }
    if (aux->DirBaseDeSaida) {

        free(aux->DirBaseDeSaida);
    
    }
    if (aux->GeoInicial) {

        free(aux->GeoInicial);
    
    }
    if (aux->NomeArqSVGFinal) {

        free(aux->NomeArqSVGFinal);
    
    }
    if (aux->NomeGEO) {

        free(aux->NomeGEO);
    
    }
    if (aux->NomeQRY) {

        free(aux->NomeQRY);
    
    }
    if (aux->PathArquivoGeoInicial) {

        free(aux->PathArquivoGeoInicial);
    
    }
    if (aux->PathArquivoQryAtual) {

        free(aux->PathArquivoQryAtual);
    
    }
    if (aux->PathDoSvgComOQryExecutado) {

        free(aux->PathDoSvgComOQryExecutado);
    
    }
    if (aux->PathDoSvgDoGeoSemMudanca) {

        free(aux->PathDoSvgDoGeoSemMudanca);
    
    }
    if (aux->PathDoTXTComOQryExecutado) {

        free(aux->PathDoTXTComOQryExecutado);
    
    }
    if (aux->PathSVGFinalGrafico) {

        free(aux->PathSVGFinalGrafico);
    
    }
    if (aux->PathTXTFinal) {

        free(aux->PathTXTFinal);
    
    }
    if (aux->QryConsultas) {

        free(aux->QryConsultas);
    
    }
    if (aux->TituloGrafFinal) {

        free(aux->TituloGrafFinal);
    
    }
    free(paths);

}