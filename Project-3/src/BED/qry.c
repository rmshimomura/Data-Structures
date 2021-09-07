#include "qry.h"
#include "person.h"
#include "paths.h"
#include "Hash/hash.h"
#include "DynamicList/dynamicList.h"

void dm_who(hash residents, char* cpf, path paths){

    FILE* file_TXT_with_qry_executed = fopen(get_path_TXT_with_qry(paths), "a+");
    setvbuf(file_TXT_with_qry_executed, 0, _IONBF, 0);

    if(findItem(hash_table_get_register_list(residents, cpf), cpf, compare_CPF)){

        void* person_to_print = findItem(hash_table_get_register_list(residents, cpf), cpf, compare_CPF);
        print_person_info(person_to_print, file_TXT_with_qry_executed);

    }else{
        
        fprintf(file_TXT_with_qry_executed, "====================================================\n\n\n");
        fprintf(file_TXT_with_qry_executed, "dm?(%s):\n\n", cpf);
        fprintf(file_TXT_with_qry_executed, "Sorry, CPF = %s not found...\n\n\n", cpf);
        fprintf(file_TXT_with_qry_executed, "====================================================\n\n\n");

    }

    fclose(file_TXT_with_qry_executed);

}
