#include "person.h"
#include "DynamicList/dynamicList.h"
#include "Hash/hash.h"

enum {
    OWN,
    RENT
};

typedef struct livingPlace{
    
    char cep[20];
    char face;
    int num;
    char complement[30];

}livingPlace;

typedef struct people{
    
    char name[50];
    char surname[50];
    char sex;
    char birthDate[11];
    char cpf[15];
    int houseState;
    livingPlace place;

    
}people;

void* create_new_person(char* name, char* surname, char* birthDate, char* cpf, char sex){

    people* new_person = calloc(1, sizeof(people));
    strcpy(new_person->name, name);
    strcpy(new_person->surname, surname);
    strcpy(new_person->birthDate, birthDate);
    strcpy(new_person->cpf, cpf);
    new_person->sex = sex;
    return new_person;

}

void update_people(void *HT, char* cpf, char* cep, char side, int num, char* complement){
    
    
    

}

void create_people_data(void* HT, FILE* file_people){

    char command[20], cpf[15], name[50], surname[50], sex, birthDate[11];

    while(fscanf(file_people, "%s", command) != -1){

        if(!strcmp(command, "p")){

            fscanf(file_people, "%s %s %s %c %s", cpf, name, surname, sex, birthDate);
            void* person = create_new_person(name, surname, birthDate, cpf, sex);
            hash_table_insert_data(HT, cpf, person);

        } else if(!strcmp(command, "m")){

        }
        
    }

}