#include "libs.h"
#include "paths.h"
#include "checks.h"
#include "system.h"
#include "person.h"
#include "DynamicList/dynamicList.h"
#include "Hash/hash.h"
#include "AVL_Tree/AVL.h"


int main(int argc, char** argv){

    //=======================================================//
    // path paths = create_general_paths();
    // flag flags = create_checkers();
    // get_arguments(argc, argv, paths, flags);
    //=======================================================//
    // tree blocks = create_tree();
    hash residents = hash_table_create_table(10);

    void* teste = create_new_person("rodrigo", "shimomura", "18/08/2002", "6546", 'M');
    hash_table_insert_data(residents, get_cpf(teste), teste);
    update_person(residents, get_cpf(teste), "6123", 'N', 3214, "APTO");
    print_person_info(teste);
    // hash locations = hash_table_create_table(find_nx(paths));
    //=======================================================//
    // get_data(blocks, residents, paths, flags);
    

    // freePaths(paths);
    // hash_table_destroy(residents);

}