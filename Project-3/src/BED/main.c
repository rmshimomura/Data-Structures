#include "libs.h"
#include "paths.h"
#include "system.h"
#include "DynamicList/dynamicList.h"
#include "Hash/hash.h"



int main(int argc, char** argv){

    path paths = create_general_paths();
    get_arguments(argc, argv, paths);


    // void* HT = hash_table_create_table(10);
    // char* name = calloc(8, 1);
    // strcpy(name, "Rodrigo");
    // char* name1 = calloc(10, 1);
    // strcpy(name1, "Alexandre");

    // hash_table_insert_data(HT, name, name);
    // hash_table_insert_data(HT, name1, name1);

    // hash_table_destroy(HT, free);

    freePaths(paths);

}