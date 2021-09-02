#include "libs.h"
#include "paths.h"
#include "system.h"


int main(int argc, char** argv){

    path paths = create_general_paths();
    get_arguments(argc, argv, paths);

}