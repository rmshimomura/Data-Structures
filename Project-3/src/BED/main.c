#include "libs.h"
#include "paths.h"
#include "system.h"
#include "DynamicList/dynamicList.h"
#include "Hash/hash.h"



int main(int argc, char** argv){

    path paths = create_general_paths();
    get_arguments(argc, argv, paths);

    freePaths(paths);

}