#include "libs.h"

#ifndef PERSON_H
#define PERSON_H

    void* create_new_person(char* name, char* surname, char* birthDate, char* cpf, char sex);
    void find_and_update_person(void *HT, char* cpf, char* cep, char side, int num, char* complement);
    void update_person(void* person_to_update, char* cep, char face, int num, char* complement);
    char* get_cpf(void* person);
    void create_people_data(void* HT, void* blocks_hash, FILE* file_people);
    int compare_CPF(void* element_node_from_list, void* target_node);
    void debug_print_person_info(void* person_to_analyze);
    void print_person_info(void* person_to_analyze, FILE* txt_qry);
    void free_person(void* person_to_free);
    char* get_person_cep(void* person_data);

#endif