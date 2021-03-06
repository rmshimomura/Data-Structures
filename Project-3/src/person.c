#include "person.h"

#include "DynamicList/dynamicList.h"
#include "Hash/hash.h"
#include "block.h"

enum homeType{
    OWN,
    RENT,
    HOMELESS
};

typedef struct livingPlace {
    char cep[50];
    char face;
    int num;
    char complement[50];

} livingPlace;

typedef struct person {
    char name[50];
    char surname[50];
    char sex;
    char birthDate[20];
    char cpf[50];
    enum homeType houseState;
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

        printf("Couldn't find person with cpf: %s on the hash table.\n", cpf);

    }

}

void update_person(void* person_to_update, char* cep, char face, int num, char* complement) {
    
    person* aux = person_to_update;
    aux->place->face = face;
    aux->place->num = num;
    strcpy(aux->place->cep, cep);
    strcpy(aux->place->complement, complement);

}

char* get_person_cpf(void* person_data) {
    person* aux = person_data;
    return aux->cpf;
}

void create_people_data(void* HT, void* blocks_hash,FILE* file_people) {

    char command[20], cpf[50], name[50], surname[50], sex, birthDate[20];
    char cep[50], face, compl[50];
    int num = 0;
    

    while (fscanf(file_people, "%s", command) != -1) {
        
        if (!strcmp(command, "p")) {

            fscanf(file_people, "%s %s %s %c %s", cpf, name, surname, &sex, birthDate);
            void* person = create_new_person(name, surname, birthDate, cpf, sex);
            hash_table_insert_data(HT, cpf, person);

        } else if (!strcmp(command, "m")) {
            
            fscanf(file_people, "%s %s %c %d %s", cpf, cep, &face, &num, compl);
            find_and_update_person(HT, cpf, cep, face, num, compl);
            void* square = find_item(hash_table_get_register_list(blocks_hash, cep), cep, compare_cep);
            add_resident(square, find_item(hash_table_get_register_list(HT, cpf), cpf, compare_CPF));
        }
    }
}

int compare_CPF(void* element_node_from_list, void* target_node) {
    if (!strcmp(get_person_cpf(element_node_from_list), target_node)) return 1;

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
        fprintf(txt_qry, "\tPerson data found: \n\n\tName: %s\n\tSurname: %s\n\tSex: %c\n\tBirthDate: %s\n\tCPF: %s\n\n", aux->name, aux->surname, aux->sex, aux->birthDate, aux->cpf);
        switch(aux->houseState){
            case 0:
                fprintf(txt_qry, "\tHouseState: OWN\n");
                break; 
            case 1:
                fprintf(txt_qry, "\tHouseState: RENT\n");
                break;
            case 2:
                fprintf(txt_qry, "\tHouseState: HOMELESS\n");
                break;
            default:
                fprintf(txt_qry, "\tHouseState: Quantum? (BUG)\n");
                break;
        }
        
        fprintf(txt_qry, "\tCEP: %s Face: %c Num: %d Complement: %s\n\n", aux->place->cep, aux->place->face, aux->place->num, aux->place->complement);
    }
   

}

void free_person(void* person_to_free){
    person* aux = person_to_free;
    free(aux->place);
    free(aux); 
}

char* get_person_cep(void* person_data){
    
    person* aux = person_data;

    return aux->place->cep;

}

void set_house_state(void* person_data, int state){
    person* aux = person_data;
    aux->houseState = state;
}

char get_person_sex(void* person_to_analyze){
    person* aux = person_to_analyze;
    return aux->sex;
}

char get_person_place_face(void* person_data) {

    person* aux = person_data;
    return aux->place->face;


}

int get_person_place_num(void* person_data) {

    person* aux = person_data;
    return aux->place->num;

}

char* get_person_name(void* person_data) {

    person* aux = person_data;
    return aux->name;

}

char* get_person_surname(void* person_data) {

    person* aux = person_data;
    return aux->surname;

}

char* get_person_full_address(void* person_data) {

    person* aux = person_data;

    char* formatted_string = calloc(strlen(aux->place->cep) + strlen(aux->place->complement) + 50, sizeof(char));
    sprintf(formatted_string, "%s - %s - %c - %d\n", aux->place->cep, aux->place->complement, aux->place->face, aux->place->num);

    return formatted_string;

}