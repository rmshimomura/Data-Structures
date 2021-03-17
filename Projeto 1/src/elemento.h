#ifndef ELEMENTO_H
#define ELEMENTO_H
#include "bibliotecas.h"

//createElemento faz a criacao da variavel que ira guardar informacoes provenientes do .geo que serao usadas ao longo do codigo
info createElemento();

//Funcoes do tipo get servem para comparacoes nas funcoes da qry (nomes autoexplicativos do que elas retornam), desde que a celula exista//
double getX(celula current);
double getY(celula current);
double getLargura(celula current);
double getAltura(celula current);
char* getId(celula current);
char* getPreenchimento(celula current);
char* getContorno(celula current);
bool getMarcadoTP(celula current);
bool getMarcadoTPR(celula current);


//Funcoes do tipo set servem para setar valores que serao comparacoes nas funcoes da qry (nomes autoexplicativos do que elas modificam)//
void setX(celula current, double xValue);
void setY(celula current, double yValue);
void setLargura(celula current, double larguraValue);
void setAltura(celula current, double alturaValue);
void setId(celula current, char* idValue);
void setPreenchimento(celula current, char* preenchimentoValue);
void setContorno(celula current, char* contornoValue);
void setMarcadoTP(celula current, bool marcadoTPValue);
void setMarcadoTPR(celula current, bool marcadoTPRValue);


#endif