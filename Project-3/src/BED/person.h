#include "libs.h"

void* create_new_person(char* name, char* surname, char* birthDate, char* cpf, char sex);
void update_person(void *HT, char* cpf, char* cep, char side, int num, char* complement);
char* get_cpf(void* person);
void create_people_data(void* HT, FILE* file_people);
int compare_CPF(void* element_node_from_list, void* target_node);
