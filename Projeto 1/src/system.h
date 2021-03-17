#include "bibliotecas.h"
#include "lista.h"
#include "qry.h"

#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

int nxFind(path paths); //Pegar o nx do geo
void getData(lista sequence, path paths); //Funcao para ler o .geo
void getFunctions(lista sequence, char* ArquivoQry, flag checkers, path paths); //Leitura do .qry
void getArguments(int argc, char** argv, flag checkers, path paths); //Analise do argc's e argv's passados
void CloseFiles(FILE* geo, FILE* svg_source); //Fecha os arquivos restantes
void showlist(lista sequence); //Mostrar os dados da lista
void checarColetas(lista sequence, flag checkers, path paths); //Checar por chamada de -ib, -cb OU -fb
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

//Criacao da variavel que ira guardar informacoes das flags que serao usadas ao longo do codigo
flag createFlags();

// Funcoes do tipo get servem para revelarem as flags que foram ativas durante a execucao do codigo (nomes autoexplicativos do que elas retornam)//
bool getBBIDexecutado(flag checkers);
bool getBBIexecutado(flag checkers);
bool getCbExecutado(flag checkers);
bool getConsultafeita(flag checkers);
bool getFail(flag checkers);
bool getFileGeo(flag checkers);
bool getFbExecutado(flag checkers);
bool getIbExecutado(flag checkers);
bool getiidExecutado(flag checkers);
bool getPathSaida(flag checkers);
bool getTPExecutado(flag checkers);
bool getTPRExecutado(flag checkers);


#endif