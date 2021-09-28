#include "libs.h"

#ifndef QRY_H
#define QRY_H

void del(tree blocks, hash blocks_hash, hash residents, hash locations, char* cep, FILE* txt_results, void* list_of_modifications);
void m_who(hash residents, hash blocks_hash, char* cep, FILE* txt_results);
void dm_who(hash blocks_hash, hash residents, char* cpf, FILE* txt_results, void* list_of_modifications);
void mud(hash residents, hash blocks_hash, char* cpf, char* cep, char face, int num, char* compl, FILE* txt_results, void* list_of_modifications);
void oloc(hash locations, hash blocks_hash, char* id, char* cep, char face, int num, char* compl, double ar, double v, FILE* txt_results);
void oloc_who(tree blocks, hash blocks_hash, double x, double y, double w, double h, FILE* txt_results, void* list_of_modifications);
void oloc_who_search(void* blocks_root, hash block_hash, double x, double y, double w, double h, FILE* txt_results, void* list_of_modifications);
void loc(hash residents, hash blocks_hash, hash locations, char* id, char* cpf, FILE* txt_results, void* list_of_modifications);
void loc_who(hash blocks_hash, hash locations, char* id, FILE* txt_results, void* list_of_modifications);
void dloc(hash locations, hash blocks_hash, char* id, FILE* txt_results, void* list_of_modifications);
void hom(tree blocks, double x, double y, double w, double h, FILE* txt_results, void* list_of_modifications);
void hom_search(void* blocks_root, double x, double y, double w, double h, FILE* txt_results);
void mul(tree blocks, double x, double y, double w, double h, FILE* txt_results, void* list_of_modifications) ;
void mul_search(void* blocks_root, double x, double y, double w, double h, FILE* txt_results);
void dmpt(tree blocks, char* sfx, path paths);
void dmpt_recursive(void* current_node, FILE* dot_file);
void catac(tree blocks, hash residents, hash locations, double x, double y, double w, double h, FILE* txt_results, void* list_of_modifications);
void catac_search(tree blocks, void* blocks_root, hash residents, hash locations, double x, double y, double w, double h, FILE* txt_results, void* list_of_modifications);

#endif