#include "libs.h"

#ifndef QRY_H
#define QRY_H

void del(tree blocks, hash blocks_hash, hash residents, hash locations, char* cep, path paths);
void m_who(hash residents, hash blocks_hash, char* cep, path paths);
void dm_who(hash residents, char* cpf, path paths);
void mud(hash residents, hash blocks_hash, char* cpf, char* cep, char face, int num, char* compl, path paths);
void oloc(hash locations, hash blocks_hash, char* id, char* cep, char face, int num, char* compl, double ar, double v, path paths);
//Void oloc_who
void loc(hash residents, hash blocks_hash, hash locations, char* id, char* cpf, path paths);
void loc_who(hash locations, char* id, path paths);
void dloc(hash locations, hash blocks_hash, char* id, path paths);
void hom(tree blocks, double x, double y, double w, double h, path paths);
void hom_search(void* blocks_root, double x, double y, double w, double h, FILE* txt_results);
//void mul
//void dmpt
//void catac

#endif