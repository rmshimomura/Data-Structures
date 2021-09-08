#include "qry.h"
#include "person.h"
#include "location.h"
#include "paths.h"
#include "Hash/hash.h"
#include "DynamicList/dynamicList.h"

void dm_who(hash residents, char* cpf, path paths){

    FILE* file_TXT_with_qry_executed = fopen(get_path_TXT_with_qry(paths), "a+");
    setvbuf(file_TXT_with_qry_executed, 0, _IONBF, 0);

    if(find_item(hash_table_get_register_list(residents, cpf), cpf, compare_CPF)){

        void* person_to_print = find_item(hash_table_get_register_list(residents, cpf), cpf, compare_CPF);
        
        fprintf(file_TXT_with_qry_executed, "dm?:\n\n");
        print_person_info(person_to_print, file_TXT_with_qry_executed);
        fprintf(file_TXT_with_qry_executed, "====================================================\n");

    }else{
        
        fprintf(file_TXT_with_qry_executed, "dm?:\n\n");
        fprintf(file_TXT_with_qry_executed, "\tSorry, CPF = %s not found...\n\n", cpf);
        fprintf(file_TXT_with_qry_executed, "====================================================\n");

    }

    fclose(file_TXT_with_qry_executed);

}

void mud(hash residents, char* cpf, char* cep, char face, int num, char* compl, path paths) {

    FILE* file_TXT_with_qry_executed = fopen(get_path_TXT_with_qry(paths), "a+");
    setvbuf(file_TXT_with_qry_executed, 0, _IONBF, 0);

    if (hash_table_list_exist(residents, cpf)) {

        void* person_to_update = find_item(hash_table_get_register_list(residents, cpf), cpf, compare_CPF);

        if (person_to_update) {

            fprintf(file_TXT_with_qry_executed, "mud:\n\n");
            fprintf(file_TXT_with_qry_executed, "BEFORE::\n\n");
            print_person_info(person_to_update, file_TXT_with_qry_executed);
            fprintf(file_TXT_with_qry_executed, "AFTER::\n\n");
            update_person(person_to_update, cep, face, num, compl);
            print_person_info(person_to_update, file_TXT_with_qry_executed);
            fprintf(file_TXT_with_qry_executed, "====================================================\n");
            
        }

    } else {
        fprintf(file_TXT_with_qry_executed ,"mud:\n\n\tCouldn't find person with cpf : %s on the hash table.\n\n", cpf);
        fprintf(file_TXT_with_qry_executed, "====================================================\n");
    }

    fclose(file_TXT_with_qry_executed);

}

void oloc(hash locations, char* id, char* cep, char face, int num, char* compl, double ar, double v, path paths){
   
    void* new_location = create_location();
    set_location_properties(new_location, id, cep, face, num, compl, ar, v);
    hash_table_insert_data(locations, cep, new_location);

}

void loc(hash residents, hash locations, char* id, char* cpf, path paths){

    FILE* file_TXT_with_qry_executed = fopen(get_path_TXT_with_qry(paths), "a+");
    setvbuf(file_TXT_with_qry_executed, 0, _IONBF, 0);

    void* person = find_item(hash_table_get_register_list(residents, cpf), cpf, compare_CPF);
    
    void* location = NULL;

    for(int i = 0; i < hash_table_size(locations); i++){
        location = find_item(hash_table_get_list_by_index(locations, i), id, compare_id);
        if(location) break;
    }

    fprintf(file_TXT_with_qry_executed, "loc:\n\n");

    if(person && location){


        update_person(person, location_get_cep(location), location_get_face(location), location_get_num(location), location_get_complement(location));
        location_set_available(location, false);
        location_info(location, file_TXT_with_qry_executed);
        print_person_info(person, file_TXT_with_qry_executed);
        set_person_living_here(location, person);

        fprintf(file_TXT_with_qry_executed, "====================================================\n");
    }

    fclose(file_TXT_with_qry_executed);

}

void loc_who(hash locations, char* id, path paths){

    FILE* file_TXT_with_qry_executed = fopen(get_path_TXT_with_qry(paths), "a+");
    setvbuf(file_TXT_with_qry_executed, 0, _IONBF, 0);

    void* location = NULL;

    for(int i = 0; i < hash_table_size(locations); i++){

        location = find_item(hash_table_get_list_by_index(locations, i), id, compare_id);

        if(location) break;

    }

    fprintf(file_TXT_with_qry_executed, "loc?:\n\n");

    if(location){
        if(location_get_available(location)){

            location_info(location, file_TXT_with_qry_executed);
            fprintf(file_TXT_with_qry_executed, "====================================================\n");
        }else{
            location_info(location, file_TXT_with_qry_executed);
            print_person_info(get_person_living_here(location), file_TXT_with_qry_executed);
            fprintf(file_TXT_with_qry_executed, "====================================================\n");
        }
    } else {
        fprintf(file_TXT_with_qry_executed, "\tSorry, id = %s not found on hash table...\n\n", id);
        fprintf(file_TXT_with_qry_executed, "====================================================\n");
    }

    fclose(file_TXT_with_qry_executed);

}