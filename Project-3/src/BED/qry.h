#include "libs.h"

#ifndef QRY_H
#define QRY_H

void dm_who(hash residents, char* cpf, path paths);
void mud(hash residents, char* cpf, char* cep, char face, int num, char* compl, path paths);
void oloc(hash locations, char* id, char* cep, char face, int num, char* compl, double ar, double v, path paths);
void loc(hash residents, hash locations, char* id, char* cpf, path paths);

#endif