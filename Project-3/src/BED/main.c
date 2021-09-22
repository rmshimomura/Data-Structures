#include "libs.h"
#include "paths.h"
#include "checks.h"
#include "system.h"
#include "location.h"
#include "person.h"
#include "DynamicList/dynamicList.h"
#include "Hash/hash.h"
#include "AVL_Tree/AVL.h"


int main(int argc, char** argv){

    path paths = create_general_paths();
    flag flags = create_checkers();
    get_arguments(argc, argv, paths, flags);
    int nx = find_nx(paths);
    tree blocks = create_tree();
    hash residents = hash_table_create_table(nx);
    hash blocks_hash = hash_table_create_table(nx);
    hash locations = hash_table_create_table(nx);

    get_data(blocks, blocks_hash, residents, paths, flags);
        
    if(get_qry_inserted(flags))
        format_qry_results(blocks, blocks_hash, residents, locations, paths, flags);
        
    freePaths(paths);

    
    hash_table_destroy(residents, free_person);
    hash_table_destroy_blocks(blocks_hash);
    hash_table_destroy(locations, location_free);

    destroy_AVL_tree(blocks, get_root(blocks), free_block_list);
    free(blocks);
    free(flags);
    

}