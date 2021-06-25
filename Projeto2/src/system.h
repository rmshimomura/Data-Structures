#include "bibliotecas.h"

#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

int nxFind(path paths); //Pegar o nx do geo
void getData(tree rectangleTree, tree circleTree, path paths); //Funcao para ler o .geo
int getArguments(int argc, char** argv, path paths); //Analise do argc's e argv's passados
void getFunctions(tree rectangleTree, tree circleTree, dynamicList listOfTreesShadows, path paths);
void CloseFiles(FILE* geo, FILE* svg_source); //Fecha os arquivos restantes
void createTempFiles(); //Arquivos temporarios usados nas funcoes
void removeTempFiles(); //Remover arquivos temporarios usados nas funcoes


path createPathsGerais(); //Cria a variavel responsavel por guardar os paths a serem usados ao longo do codigo

//Funcoes get retornam os char* que foram modificados no getarguments para serem usados no restante do codigo
char* getDirBaseDeEntrada(path paths);
char* getDirBaseDeSaida(path paths);
char* getGeoInicial(path paths);
char* getQryConsultas(path paths);
char* getNomeQRY(path paths);
char* getNomeGEO(path paths);
char* getNomeArqSVGFinal(path paths);
char* getTituloGrafFinal(path paths);
char* getPathArquivoGeoInicial(path paths);
char* getPathArquivoQryAtual(path paths);
char* getPathDoSvgDoGeoSemMudanca(path paths);
char* getPathDoSvgComOQryExecutado(path paths);
char* getPathDoTXTComOQryExecutado(path paths);
char* getPathSVGFinalGrafico(path paths);
char* getPathTXTFinal(path paths);


#endif