#include "AVL_Tree/AVL.h"
#include "Dynamic_list/dynamic_list.h"
#include "Graph/graph.h"
#include "Hash/hash.h"
#include "checks.h"
#include "dijkstra.h"
#include "edge.h"
#include "kruskal.h"
#include "libs.h"
#include "paths.h"
#include "system.h"
#include "vertex.h"
#include "viewbox.h"
#include "svg.h"

int main(int argc, char** argv) {

    void* paths = create_general_paths();
    void* flags = create_checkers();
    void* view_box = create_view_box();

    get_arguments(argc, argv, paths, flags);
    int size = structures_size(paths);
    if(size == -1) { 
        puts("Size not inserted!");
        free_paths(paths);
        free(flags);
        free(view_box);
        return -1;
    }

    void* blocks = create_tree();
    void* blocks_hash = hash_table_create_table(size);
    void* connections = create_graph(size);
    get_data(connections, blocks, blocks_hash, paths, flags, view_box);
    print_on_SVG(connections, blocks, view_box, paths);

    if(get_qry_inserted(flags))
        format_qry_results(connections, blocks, blocks_hash, paths, flags, view_box);
        

    free_graph(connections);
    hash_table_destroy(blocks_hash, free, false);
    destroy_AVL_tree(blocks, get_root(blocks), free_block_list);
    free(blocks);
    free(flags);
    free(view_box);
    free_paths(paths);
}