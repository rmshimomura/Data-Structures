#include "bibliotecas.h"
#ifndef FLAGS_H
#define FLAGS_H

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
bool getFileQryValido(flag checkers);

#endif