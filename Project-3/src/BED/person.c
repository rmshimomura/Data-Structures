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
    char birthDate[11];
    char cpf[15];
    int houseState;
    livingPlace place;

} person;

void* create_new_person(char* name, char* surname, char* birthDate, char* cpf, char sex) {
    person* new_person = calloc(1, sizeof(person));
    strcpy(new_person->name, name);
    strcpy(new_person->surname, surname);
    strcpy(new_person->birthDate, birthDate);
    strcpy(new_person->cpf, cpf);
    new_person->sex = sex;
    return new_person;
}

void update_person(void* HT, char* cpf, char* cep, char face, int num, char* complement) {
    
    if (hash_table_list_exist(HT, cpf)) {
        if (findItem(hash_table_get_register_list(HT, cpf), cpf, compare_CPF)) {
            person* person_to_update = findItem(hash_table_get_register_list(HT, cpf), cpf, compare_CPF);
            person_to_update->houseState = OWN;
            strcpy(person_to_update->place.cep, cep);
            person_to_update->place.face = face;
            person_to_update->place.num = num;
            strcpy(person_to_update->place.complement, complement);
        }

    } else {
        printf("Couldn't find person with cpf : %s on the hash table.\n", cpf);
    }
}

char* get_cpf(void* person_data) {
    person* aux = person_data;
    return aux->cpf;
}

void create_people_data(void* HT, FILE* file_people) {  //TODO

    char command[20], cpf[15], name[50], surname[50], sex, birthDate[11];
    char cep[20], face, compl [30];
    int num = 0;

    while (fscanf(file_people, "%s", command) != -1) {
        if (!strcmp(command, "p")) {
            fscanf(file_people, "%s %s %s %c %s", cpf, name, surname, sex, birthDate);
            void* person = create_new_person(name, surname, birthDate, cpf, sex);
            hash_table_insert_data(HT, cpf, person);

        } else if (!strcmp(command, "m")) {
            fscanf(file_people, "%s %s %s %c %s", cpf, cep, face, &num, compl );
            update_person(HT, cpf, cep, face, num, compl);
        }
    }
}

int compare_CPF(void* element_node_from_list, void* target_node) {
    if (!strcmp(get_cpf(element_node_from_list), target_node)) return 1;

    return 0;
}
