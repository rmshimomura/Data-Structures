#include "qry.h"
#include "person.h"
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