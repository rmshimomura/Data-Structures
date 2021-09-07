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
    path paths = create_general_paths();
    flag flags = create_checkers();
    get_arguments(argc, argv, paths, flags);
    // =======================================================//
    tree blocks = create_tree();
    hash residents = hash_table_create_table(find_nx(paths));
    hash locations = hash_table_create_table(find_nx(paths));
    get_data(blocks, residents, paths, flags);

        
    if(get_qry_inserted(flags)){
        FILE* txt_results = fopen(get_path_TXT_with_qry(paths), "w+");
        setvbuf(txt_results, 0, _IONBF, 0);
        fprintf(txt_results, "Rodrigo Mimura Shimomura\n");
        fprintf(txt_results, "FUNCTIONS EXECUTED:\n\n====================================================\n");
        get_functions(blocks, residents, locations, paths, flags);
        fclose(txt_results);
    }

    freePaths(paths);
    hash_table_destroy(residents, free_person);
    free(blocks);
    hash_table_destroy(locations, free);
    free(flags);

}