#include "person.h"

#include "DynamicList/dynamicList.h"
#include "Hash/hash.h"

enum {
    OWN,
    RENT
};

typedef struct livingPlace {
    char cep[20];
    char face;
    int num;
    char complement[30];

} livingPlace;

typedef struct person {
    char name[50];
    char surname[50];
    char sex;
    char birthDate[12];
    char cpf[15];
    int houseState;
    livingPlace* place;

} person;

void* create_new_person(char* name, char* surname, char* birthDate, char* cpf, char sex) {
    
    person* new_person = calloc(1, sizeof(person));
    new_person->place = calloc(1, sizeof(livingPlace));
    strcpy(new_person->name, name);
    strcpy(new_person->surname, surname);
    strcpy(new_person->birthDate, birthDate);
    strcpy(new_person->cpf, cpf);
    new_person->sex = sex;
    return new_person;

}

void find_and_update_person(void* HT, char* cpf, char* cep, char face, int num, char* complement) {

    if (hash_table_list_exist(HT, cpf)) {

        person* person_to_update = find_item(hash_table_get_register_list(HT, cpf), cpf, compare_CPF);

        if (person_to_update) {

            update_person(person_to_update, cep, face, num , complement);
            person_to_update->houseState = OWN;
            
        }

    } else {

        printf("Couldn't find person with cpf : %s on the hash table.\n", cpf);

    }

}

void update_person(void* person_to_update, char* cep, char face, int num, char* complement) {
    
    person* aux = person_to_update;
    aux->place->face = face;
    aux->place->num = num;
    strcpy(aux->place->cep, cep);
    strcpy(aux->place->complement, complement);

}

char* get_cpf(void* person_data) {
    person* aux = person_data;
    return aux->cpf;
}

void create_people_data(void* HT, FILE* file_people) {

    char command[20], cpf[15], name[50], surname[50], sex, birthDate[11];
    char cep[20], face, compl [30];
    int num = 0;

    while (fscanf(file_people, "%s", command) != -1) {
        if (!strcmp(command, "p")) {
            fscanf(file_people, "%s %s %s %c %s", cpf, name, surname, &sex, birthDate);
            void* person = create_new_person(name, surname, birthDate, cpf, sex);
            hash_table_insert_data(HT, cpf, person);

        } else if (!strcmp(command, "m")) {
            fscanf(file_people, "%s %s %c %d %s", cpf, cep, &face, &num, compl);
            find_and_update_person(HT, cpf, cep, face, num, compl);
        }
    }
}

int compare_CPF(void* element_node_from_list, void* target_node) {
    if (!strcmp(get_cpf(element_node_from_list), target_node)) return 1;

    return 0;
}

void debug_print_person_info(void* person_to_analyze){
    person* aux = person_to_analyze;
    printf("====================================================\n\n\n");
    printf("DEBUG with CPF = %s:\n\n", aux->cpf);
    printf("Data found: \nName: %s\nSurname: %s\nSex: %c\nBirthDate: %s\nCPF: %s\n\nHouseState: %s\n", aux->name, aux->surname, aux->sex, aux->birthDate, aux->cpf, aux->houseState == OWN ? "Own" : "Rent");
    printf("CEP: %s Face: %c Num: %d Complement: %s\n\n\n", aux->place->cep, aux->place->face, aux->place->num, aux->place->complement);
    printf("====================================================\n");

}

void print_person_info(void* person_to_analyze, FILE* txt_qry){
    
    person* aux = person_to_analyze;
    if(aux){
        fprintf(txt_qry, "\tPerson data found: \n\n\tName: %s\n\tSurname: %s\n\tSex: %c\n\tBirthDate: %s\n\tCPF: %s\n\n\tHouseState: %s\n", aux->name, aux->surname, aux->sex, aux->birthDate, aux->cpf, aux->houseState == OWN ? "Own" : "Rent");
        fprintf(txt_qry, "\tCEP: %s Face: %c Num: %d Complement: %s\n\n", aux->place->cep, aux->place->face, aux->place->num, aux->place->complement);
    }
   

}

void free_person(void* person_to_free){
    person* aux = person_to_free;
    free(aux->place);
    free(aux); 
}