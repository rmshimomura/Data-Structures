#include "bibliotecas.h"

#ifndef PATHS_H
#define PATHS_H

path createPathsGerais();
//Funcoes do tipo get servem para revelar os dados passados nos argumentos
//que serao usados nas funcoes da qry, svg... (nomes autoexplicativos do que elas retornam)//
char* getDirBaseDeEntrada(path paths);
char* getDirBaseDeSaida(path paths);
char* getGeoInicial(path paths);
char* getQryConsultas(path paths);
char* getNomeQRY(path paths);
char* getNomeGEO(path paths);
char* getNomeArqSVGFinal(path paths);
char* getPathArquivoGeoInicial(path paths);
char* getPathArquivoQryAtual(path paths);
char* getPathDoSvgDoGeoSemMudanca(path paths);
char* getPathDoSvgComOQryExecutado(path paths);
char* getPathDoTXTComOQryExecutado(path paths);
char* getPathTXTFinal(path paths);

//Debug
void showPaths(path paths);

//Liberar os espacos alocados da struct dos paths
void freePaths(path paths);

#endif