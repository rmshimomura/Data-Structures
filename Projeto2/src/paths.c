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

void setDirBaseDeEntrada(path paths, char* newSet) {
    
    pathsGerais* aux = paths;
    aux->DirBaseDeEntrada = newSet;
    
}

void setDirBaseDeSaida(path paths, char* newSet) {
    
    pathsGerais* aux = paths;
    aux->DirBaseDeSaida = newSet;

}

void setGeoInicial(path paths, char* newSet) {
   
    pathsGerais* aux = paths;
    aux->GeoInicial = newSet;
    
}

void setQryConsultas(path paths, char* newSet) {
   
    pathsGerais* aux = paths;
    aux->QryConsultas = newSet;
    
}

void setNomeQRY(path paths, char* newSet) {
   
    pathsGerais* aux = paths;
    aux->NomeQRY = newSet;
    
}

void setNomeGEO(path paths, char* newSet) {
   
    pathsGerais* aux = paths;
    aux->NomeGEO = newSet;
    
}

void setNomeArqSVGFinal(path paths, char* newSet) {
   
    pathsGerais* aux = paths;
    aux->NomeArqSVGFinal = newSet;
    
}

void setPathArquivoGeoInicial(path paths, char* newSet) {
   
    pathsGerais* aux = paths;
    aux->PathArquivoGeoInicial = newSet;

    
}

void setPathArquivoQryAtual(path paths, char* newSet) {
   
    pathsGerais* aux = paths;
    aux->PathArquivoQryAtual = newSet;
    
}

void setPathDoSvgDoGeoSemMudanca(path paths, char* newSet) {
   
    pathsGerais* aux = paths;
    aux->PathDoSvgDoGeoSemMudanca = newSet;

}

void setPathDoSvgComOQryExecutado(path paths, char* newSet) {
   
    pathsGerais* aux = paths;
    aux->PathDoSvgComOQryExecutado = newSet;
    
}

void setPathDoTXTComOQryExecutado(path paths, char* newSet) {
   
    pathsGerais* aux = paths;
    aux->PathDoTXTComOQryExecutado = newSet;
    
}

void setPathSVGFinalGrafico(path paths, char* newSet) {
   
    pathsGerais* aux = paths;
    aux->PathSVGFinalGrafico = newSet;

}

void setPathTXTFinal(path paths, char* newSet) {
   
    pathsGerais* aux = paths;
    aux->PathTXTFinal = newSet;
    
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