#include "libs.h"

#ifndef QRY_H
#define QRY_H

void dm_who(hash residents, char* cpf, path paths);
void mud(hash residents, hash blocks_hash, char* cpf, char* cep, char face, int num, char* compl, path paths);
void oloc(hash locations, hash blocks_hash, char* id, char* cep, char face, int num, char* compl, double ar, double v, path paths);
void loc(hash residents, hash blocks_hash, hash locations, char* id, char* cpf, path paths);
void loc_who(hash locations, char* id, path paths);
void m_who(hash residents, hash blocks_hash, char* cep, path paths);

#endif